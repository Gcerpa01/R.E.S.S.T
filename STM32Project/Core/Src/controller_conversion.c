#include "controller_conversion.h"


float accel_map(uint8_t controllerInput){
    float newCCR = (float)(controllerInput - TRIGGER_MIN)*
                    (CCR_FOR_DUTY_CYCLE_MAX - CCR_FOR_DUTY_CYCLE_MIN) / 
                    (CCR_FOR_DUTY_CYCLE_MAX - CCR_FOR_DUTY_CYCLE_MIN) + TRIGGER_MAX;
    return newCCR;
}

float steer_map(uint8_t controllerInput){
    float newCCR = (float)(controllerInput - JOYSTICK_MIN)*
                    (CCR_FOR_STEERING_MAX - CCR_FOR_STEERING_MIN) / 
                    (CCR_FOR_STEERING_MAX - CCR_FOR_STEERING_MIN) + JOYSTICK_MIN;
    return newCCR;
}

