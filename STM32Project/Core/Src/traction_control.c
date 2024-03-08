#include "traction_control.h"
#include "motor_control.h"

//Calculate the RPM for each wheel and save it in memory
/// - Parameters:
///   
///   
void calculateRPM(){
    for(size_t i = 0; i < sizeof(HALL_EFFECT_SENSORS)/sizeof(HALL_EFFECT_SENSORS[0]); i++){
        RPM_VALUES[i] = (HALL_EFFECT_SENSORS[i] / POLES) * 60;
    }
}

/// Calculates the Average RPM of the remaining 3 wheels
/// - Parameters:
///   - current: the wheel to not include in the average
///   
float calculateAverageRPM(size_t current){
    float temp = 0;
    for(size_t j = 0; j < sizeof(RPM_VALUES)/sizeof(RPM_VALUES[0]); j++){
        if(current == j) continue;
        temp+= RPM_VALUES[j];
    }
    return temp/(sizeof(RPM_VALUES)/sizeof(RPM_VALUES[0]) - 1);
}


/// Determines which wheels are slipping and which wheels have traction
/// - Parameters:
///   
///   
void determineSlippage(){
    if(CURRENT_STEERING == NEUTRAL){
        float maxVal = MIN_RPM_VALUE;
        //Calculate each wheels RPM to the avergae of all the others
        for(size_t i = 0; i < sizeof(RPM_VALUES)/sizeof(RPM_VALUES[0]); i++){
            float averageRPM = calculateAverageRPM(i);
            float threshMin = averageRPM * (1 - LINEAR_TRACTION_THRESHOLD);
            float threshMax = averageRPM * (1 + LINEAR_TRACTION_THRESHOLD);

            //Check if its above or below the threshold
            if(RPM_VALUES[i] >= threshMax){
                //Prioritize the wheel with the worst traction
                if(RPM_VALUES[i] > maxVal){
                    maxVal = RPM_VALUES[i];
                    WHEEL = i;
                }
                printf("Slippage Detected: Wheel %d\r\n", i);
                push(WHEELS_WITHOUT_TRACTION,i);
            }
            else{ push(WHEELS_WITH_TRACTION,i); }
        }
        printf("Wheel with the worst slippage is: %d\r\n", WHEEL);
    }   
}


/// Calculates and sends a new duty cycle to the wheel slipping
/// - Parameters:
///   - currDutyCycle: the current CCR value being sent to the motor
///   
void linearTraction(float currDutyCycle){
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
		float target = currDutyCycle - (reduction/RPM_VALUES[pop_val]) * (ACCEL_CCR_FOR_DUTY_CYCLE_MAX - ACCEL_CCR_FOR_DUTY_CYCLE_MIN);
        //Stay within boundaries
		if(target < ACCEL_CCR_FOR_DUTY_CYCLE_MIN){
			target = ACCEL_CCR_FOR_DUTY_CYCLE_MIN;
		} else if (target > ACCEL_CCR_FOR_DUTY_CYCLE_MAX){
			target = ACCEL_CCR_FOR_DUTY_CYCLE_MAX;
		}
        target = (target/100) * 144;
        printf("The current CCR for Wheel %d is: %f, changing it to: %f\r\n", pop_val, currDutyCycle, target);
		send_to_motor(pop_val,target);
	}
}
