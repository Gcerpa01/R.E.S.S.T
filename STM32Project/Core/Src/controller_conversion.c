#include "controller_conversion.h"


float accel_map(uint8_t controllerInput){
    float newCCR = (float)(controllerInput - ACCEL_TRIGGER_MIN) * 
                    ((ACCEL_CCR_FOR_DUTY_CYCLE_MAX - ACCEL_CCR_FOR_DUTY_CYCLE_MIN) / 
                    (ACCEL_TRIGGER_MAX - ACCEL_TRIGGER_MIN)) + ACCEL_CCR_FOR_DUTY_CYCLE_MIN;
    return newCCR;
}


float steer_map(uint8_t controllerInput){
    float newCCR = (float)(controllerInput - JOYSTICK_MIN)*
                    ((CCR_FOR_STEERING_MAX - CCR_FOR_STEERING_MIN) / 
                    (JOYSTICK_MAX - JOYSTICK_MIN)) + CCR_FOR_STEERING_MIN;
    return newCCR;
}

float brake_map(uint8_t controllerInput){
    float newCCR = BRAKING_CCR_FOR_DUTY_CYCLE_MAX - (float)(controllerInput - BRAKE_TRIGGER_MIN) * 
                    ((BRAKING_CCR_FOR_DUTY_CYCLE_MAX - BRAKING_CCR_FOR_DUTY_CYCLE_MIN) / 
                    (BRAKE_TRIGGER_MAX - BRAKE_TRIGGER_MIN));
    return newCCR;
}


void determine_steering_direction(float calculatedValue){
    float baseline = (ACCEL_CCR_FOR_DUTY_CYCLE_MAX - ACCEL_CCR_FOR_DUTY_CYCLE_MIN) / 2;
    if (calculatedValue < baseline - baseline*STEERING_THRESHOLD){
        CURRENT_STEERING = LEFT;
        INSIDE_WHEELS = {FRONT_LEFT,REAR_RIGHT};
        OUTSIDE_WHEELS = {FRONT_RIGHT,REAR_LEFT};
    }
    else if (calculatedValue > (baseline + baseline*STEERING_THRESHOLD)){
        CURRENT_STEERING = RIGHT;
        INSIDE_WHEELS = {FRONT_RIGHT,REAR_LEFT};
        OUTSIDE_WHEELS= {FRONT_LEFT,REAR_RIGHT};
    }
    else CURRENT_STEERING = NEUTRAL;
}
