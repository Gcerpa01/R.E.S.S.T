#include "traction_control.h"

// Define the global variables
Stack *WHEELS_WITH_TRACTION;
Stack *WHEELS_WITHOUT_TRACTION;

/**
 * @abstract: Determines the Duty Cycle based on CCR value
 * @returns: the Duty Cycle being sent
 *  
 */
float get_duty_cycle(int passedCCR){
    return passedCCR * 100.0 / 1440.0;
}

/**
 * @abstract: Creates the global variables necessary
 * 
 * 
 */
void initialize_traction_control() {
    WHEELS_WITH_TRACTION = create_stack(4);
    WHEELS_WITHOUT_TRACTION = create_stack(4);
}

/**
 * @abstract: Calculates the RPM for each wheel and save it in memory.
 *            Also resets Hall Effect Count for future calculation.
 * 
 */
void calculateRPM(){
    for(size_t i = 0; i < sizeof(LAND_CONTROLLERS)/sizeof(LAND_CONTROLLERS[0]); i++){
        LAND_CONTROLLERS[i].rpm = (LAND_CONTROLLERS[i].hall_effect_count * POLES) * 60;
        LAND_CONTROLLERS[i].hall_effect_count = 0;
    }
    // printf("\r-----RPM Values-----\r\n");
	// printf("Front Left Wheel: %f \r\n", RPM_VALUES[0]);
	// printf("Front Right Wheel: %f \r\n", RPM_VALUES[1]);
	// printf("Back Left Wheel: %f \r\n", RPM_VALUES[2]);
	// printf("Back Right Wheel: %f \r\n", RPM_VALUES[3]);
	// printf("-----RPM Values----- \r\n");
}


/**
 * @abstract: Calculates the Average RPM of the remaining 3 wheels
 * @param current: the wheel to not include in the RPM average 
 * 
 */
float calculateAverageRPM(size_t current){
    float temp = 0;
    for(size_t j = 0; j < sizeof(LAND_CONTROLLERS)/sizeof(LAND_CONTROLLERS[0]); j++){
        if(current == j) continue;
        temp+= LAND_CONTROLLERS[j].rpm;
    }
    return temp/(sizeof(LAND_CONTROLLERS)/sizeof(LAND_CONTROLLERS[0]) - 1);
}


/**
 * @abstract: Determines which wheels are slipping and which wheels have traction
 * 
 * 
 */
void determineSlippage(){
//	printf("Determine Slippage\r\n");
    if(CURRENT_STEERING == NEUTRAL){
        float maxVal = MIN_RPM_VALUE;
        //Compare each wheels RPM to the average of all the others
        for(size_t i = 0; i < sizeof(LAND_CONTROLLERS)/sizeof(LAND_CONTROLLERS[0]); i++){
            float averageRPM = calculateAverageRPM(i);
//            printf("The averageRPM for all other wheels is: %.2f, Wheel[i] RPM is: %.2f\r\n",averageRPM, RPM_VALUES[i]);
            float threshMax = averageRPM * (1 + LINEAR_TRACTION_THRESHOLD);
//            printf("The threshold max is: %.2f\r\n", threshMax);
            //Check if its above or below the threshold
            if(LAND_CONTROLLERS[i].rpm >= threshMax){
                //Track the wheel with the worst traction
                if(LAND_CONTROLLERS[i].rpm > maxVal){
                    maxVal = LAND_CONTROLLERS[i].rpm;
                    WHEEL = i;
                }
                // printf("Slippage Detected: Wheel %d\r\n", i);
                push(WHEELS_WITHOUT_TRACTION,LAND_CONTROLLERS[i]);
            }
            else{ push(WHEELS_WITH_TRACTION,LAND_CONTROLLERS[i]); }
        }
        // printf("Wheel with the worst slippage is: %d\r\n", WHEEL);
        linearTraction(THROTTLE_INPUT);
    }   
}



/**
 * @abstract: Calculates and sends a new duty cycle to the wheel slipping
 * @param currCCR: the current CCR value being sent to the motor
 * 
 */
void linearTraction(int currCCR){
//	printf("Doing Linear Traction\r\n");
	//get average rpm of the wheels with traction
	PID_controller pop_val;
	float average = 0;
	int og_size = get_size(WHEELS_WITH_TRACTION);
	while (!is_empty(WHEELS_WITH_TRACTION)){
		pop(WHEELS_WITH_TRACTION, &pop_val);
		float rpm = pop_val.rpm;
		average += rpm;
	}
	average /= og_size;

    //Calculate new CCR
	while(!is_empty(WHEELS_WITHOUT_TRACTION)){
		pop(WHEELS_WITHOUT_TRACTION, &pop_val);
        
        float controlCCR = performPID(pop_val, average);
        
        int targetCCR =  currCCR + controlCCR;

        // Ensure duty cycle is within bounds
        targetCCR = (targetCCR < ACCEL_CCR_FOR_DUTY_CYCLE_MIN) ? ACCEL_CCR_FOR_DUTY_CYCLE_MIN : targetCCR;
        targetCCR = (targetCCR > ACCEL_CCR_FOR_DUTY_CYCLE_MAX) ? ACCEL_CCR_FOR_DUTY_CYCLE_MAX : targetCCR;

//        printf("The current CCR for Wheel %d is: %d, changing it to: %d\r\n", pop_val.wheel_position, currCCR, targetCCR);
//         printf("The current Duty Cycle for Wheel %d is: %.2f, changing it to: %.2f\r\n", pop_val.wheel_position, get_duty_cycle(currCCR), get_duty_cycle(targetCCR));
		send_to_motor(pop_val.wheel_position,targetCCR);
	}
}


float performPID(PID_controller targetMotor, float targetRPM){
//	printf("Performing PID \r\n");
    //Calculate difference in rpm 
    float error = targetMotor.rpm - targetRPM;
    
    //calculate Present error (Proportional)
    float proportional_term = targetMotor.Kp * error;

    //calculate past error (Integral)
    targetMotor.error_sum += error; //keep run of error
    float integral_term = targetMotor.Ki * targetMotor.error_sum;

    //calculate future error (Derivative)
    float derivative_term = targetMotor.Kd * (error - targetMotor.prev_error);
    targetMotor.prev_error = error;

    return proportional_term + integral_term + derivative_term;
}
