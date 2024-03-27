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
 * @abstract: Calculates the RPM for each wheel and save it in memory
 * 
 * 
 */
void calculateRPM(){
    for(size_t i = 0; i < sizeof(HALL_EFFECT_SENSORS)/sizeof(HALL_EFFECT_SENSORS[0]); i++){
        RPM_VALUES[i] = (HALL_EFFECT_SENSORS[i] / POLES) * 60;
    }
}


/**
 * @abstract: Calculates the Average RPM of the remaining 3 wheels
 * @param current: the wheel to not include in the RPM average 
 * 
 */
float calculateAverageRPM(size_t current){
    float temp = 0;
    for(size_t j = 0; j < sizeof(RPM_VALUES)/sizeof(RPM_VALUES[0]); j++){
        if(current == j) continue;
        temp+= RPM_VALUES[j];
    }
    return temp/(sizeof(RPM_VALUES)/sizeof(RPM_VALUES[0]) - 1);
}

/*
finds the CCR and maps the value to a value from 0 to 180
*/
float calcTurnAngle(int controllerInput){
    int vehicle_input = steer_map(controllerInput);
    int angle = ((CCR_FOR_STEERING_MAX - CCR_FOR_STEERING_MIN) * (SERVO_ANGLE_MAX - SERVO_ANGLE_MIN) /
                (CCR_FOR_STEERING_MAX + CCR_FOR_STEERING_MIN)) + SERVO_ANGLE_MIN;
    float turnAngle = (tan(angle) * 180) / 3.14;
    
    return turnAngle;
}
/**
 * @abstract: Determines which wheels are slipping and which wheels have traction
 * 
 * 
 */
void determineSlippage(){
    float maxVal = MIN_RPM_VALUE;
    if(CURRENT_STEERING == NEUTRAL){
        //Compare each wheels RPM to the average of all the others
        for(size_t i = 0; i < sizeof(RPM_VALUES)/sizeof(RPM_VALUES[0]); i++){
            float averageRPM = calculateAverageRPM(i);
//            printf("The averageRPM for all other wheels is: %.2f, Wheel[i] RPM is: %.2f\r\n",averageRPM, RPM_VALUES[i]);
            float threshMax = averageRPM * (1 + LINEAR_TRACTION_THRESHOLD);
//            printf("The threshold max is: %.2f\r\n", threshMax);
            //Check if its above or below the threshold
            if(RPM_VALUES[i] >= threshMax){
                //Track the wheel with the worst traction
                if(RPM_VALUES[i] > maxVal){
                    maxVal = RPM_VALUES[i];
                    WHEEL = i;
                }
                // printf("Slippage Detected: Wheel %d\r\n", i);
                push(WHEELS_WITHOUT_TRACTION,i);
            }
            else{ push(WHEELS_WITH_TRACTION,i); }
        }
        // printf("Wheel with the worst slippage is: %d\r\n", WHEEL);
        linearTraction(THROTTLE_INPUT);
    }   
    else if(CURRENT_STEERING == RIGHT){
        int inside_rpmA = RPM_VALUES[1];    //front left
        int inside_rpmB = RPM_VALUES[4];    //back right

        int outisde_rpmA = RPM_VALUES[2];   //front right
        int outside_rpmB = RPM_VALUES[3];   //back left

        float turn = WHEELBASE /calcTurnAngle(JOYSTICK);
        float outterRadius = turn + WHEELBASE/2;
        float innerRadius = turn - WHEELBASE/2;

        float threshMax = (outterRadius/innerRadius) * (1 + STEERING_THRESHOLD);
        float threshMin = (outterRadius/innerRadius) * (1 - STEERING_THRESHOLD);
        for(int i = 0; i < sizeof(RPM_VALUES)/sizeof(RPM_VALUES[0]); i++){
            if(RPM_VALUES[i] > threshMax){
                if(RPM_VALUES[i] > maxVal){
                    maxVal = RPM_VALUES[i];
                    WHEEL = i;
                }
                // printf("Slippage Detected: Wheel %d\r\n", i);
                push(WHEELS_WITHOUT_TRACTION,i);
            }
            else{ push(WHEELS_WITH_TRACTION,i); }
        }
    linearTraction(THROTTLE_INPUT);
    }
    else if(CURRENT_STEERING == LEFT){
        int inside_rpmA = RPM_VALUES[2];    //front right
        int inside_rpmB = RPM_VALUES[3];    //back left

        int outisde_rpmA = RPM_VALUES[1];   //front left
        int outside_rpmB = RPM_VALUES[4];   //back right
        
        float turn = WHEELBASE /calcTurnAngle(JOYSTICK);
        float outterRadius = turn + WHEELBASE/2;
        float innerRadius = turn - WHEELBASE/2;

        float threshMax = (outterRadius/innerRadius) * (1 + STEERING_THRESHOLD);
        float threshMin = (outterRadius/innerRadius) * (1 - STEERING_THRESHOLD);
        
        for(int i = 0; i < sizeof(RPM_VALUES)/sizeof(RPM_VALUES[0]); i++){
            if(RPM_VALUES[i] > threshMax ){
                if(RPM_VALUES[i] > threshMax){
                if(RPM_VALUES[i] > maxVal){
                    maxVal = RPM_VALUES[i];
                    WHEEL = i;
                }
                // printf("Slippage Detected: Wheel %d\r\n", i);
                push(WHEELS_WITHOUT_TRACTION,i);
            }
            else{ push(WHEELS_WITH_TRACTION,i); }
        }
    linearTraction(THROTTLE_INPUT);
        }
    }
}



/**
 * @abstract: Calculates and sends a new duty cycle to the wheel slipping
 * @param currCCR: the current CCR value being sent to the motor
 * 
 */
void linearTraction(int currCCR){
	//get average rpm of the wheels with traction
	int pop_val = 0;
	float average = 0;
	int og_size = get_size(WHEELS_WITH_TRACTION);
	while (!is_empty(WHEELS_WITH_TRACTION)){
		pop(WHEELS_WITH_TRACTION, &pop_val);
		float rpm = RPM_VALUES[pop_val];
		average += rpm;
	}
	average /= og_size;

    //Calculate new CCR
	while(!is_empty(WHEELS_WITHOUT_TRACTION)){
		pop(WHEELS_WITHOUT_TRACTION, &pop_val);
        //Calculate difference in rpm 
		float reduction = RPM_VALUES[pop_val] - average;
        //Calculate target based on current input 
		int target = currCCR - (reduction/RPM_VALUES[pop_val]) * (ACCEL_CCR_FOR_DUTY_CYCLE_MAX - ACCEL_CCR_FOR_DUTY_CYCLE_MIN);
        //Stay within boundaries
        target = (target < ACCEL_CCR_FOR_DUTY_CYCLE_MIN) ? ACCEL_CCR_FOR_DUTY_CYCLE_MIN : target;
        target = (target > ACCEL_CCR_FOR_DUTY_CYCLE_MAX) ? ACCEL_CCR_FOR_DUTY_CYCLE_MAX : target;

        // printf("The current CCR for Wheel %d is: %d, changing it to: %d\r\n", pop_val, currCCR, target);
        // printf("The current Duty Cycle for Wheel %d is: %.2f, changing it to: %.2f\r\n", pop_val, get_duty_cycle(currCCR), get_duty_cycle(target));
		send_to_motor(pop_val,target);
	}
}
