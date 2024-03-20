#include "controller_conversion.h"


/**
 * @abstract: Maps the values given from the controller to be within a given boundary for
 *            proper Duty Cycle calibration
 * @param controllerInput: the value received from the controller
 * @returns: A float value to be used as to control the motors
 *  
 */
int accel_map(int controllerInput) {
    int newCCR = (int)(((float)(controllerInput - ACCEL_TRIGGER_MIN) / 
                    (float)(ACCEL_TRIGGER_MAX - ACCEL_TRIGGER_MIN)) * 
                    (ACCEL_CCR_FOR_DUTY_CYCLE_MAX - ACCEL_CCR_FOR_DUTY_CYCLE_MIN)) + ACCEL_CCR_FOR_DUTY_CYCLE_MIN;
    return newCCR;
}

/**
 * @abstract: Maps the values given from the controller to be within a given boundary for
 *            proper Duty Cycle calibration
 * @param controllerInput: the value received from the controller
 * @returns: A float value to be used as to control the servo motors
 *  
 */
int steer_map(int controllerInput){
    int newCCR = (int)(((float)(controllerInput - JOYSTICK_MIN) /
                    (float)(CCR_FOR_STEERING_MAX - CCR_FOR_STEERING_MIN))*
                    (JOYSTICK_MAX - JOYSTICK_MIN)) + CCR_FOR_STEERING_MIN;
    return newCCR;
}

/**
 * @abstract: Maps the values given from the controller to be within a given boundary for
 *            proper Duty Cycle calibration
 * @param controllerInput: the value received from the controller
 * @returns: A float value to be used as to control the motors
 *  
 */
int brake_map(int controllerInput) {
    float newCCR = (float)(BRAKING_CCR_FOR_DUTY_CYCLE_MAX - BRAKING_CCR_FOR_DUTY_CYCLE_MIN) * 
                   ((float)(BRAKE_TRIGGER_MAX - controllerInput) / 
                   (float)(BRAKE_TRIGGER_MAX - BRAKE_TRIGGER_MIN)) + BRAKING_CCR_FOR_DUTY_CYCLE_MIN;

    return (int)newCCR;
}

/**
 * @abstract: Determines which way the user is steering the vehicle
 * @param calculatedValue: the value received from the controller
 *  
 */
void determine_steering_direction(float calculatedValue){
    float baseline = (ACCEL_CCR_FOR_DUTY_CYCLE_MAX - ACCEL_CCR_FOR_DUTY_CYCLE_MIN) / 2;
    if (calculatedValue < baseline - baseline*STEERING_THRESHOLD){
        CURRENT_STEERING = LEFT;
        INSIDE_WHEELS = make_tuple(LAND_CONTROLLERS[1], LAND_CONTROLLERS[2]);
        OUTSIDE_WHEELS = make_tuple(LAND_CONTROLLERS[0], LAND_CONTROLLERS[3]);
    }
    else if (calculatedValue > (baseline + baseline*STEERING_THRESHOLD)){
        CURRENT_STEERING = RIGHT;
        INSIDE_WHEELS = make_tuple(LAND_CONTROLLERS[0], LAND_CONTROLLERS[3]);
        OUTSIDE_WHEELS= make_tuple(LAND_CONTROLLERS[1], LAND_CONTROLLERS[2]);
    }
    else CURRENT_STEERING = NEUTRAL;
}
