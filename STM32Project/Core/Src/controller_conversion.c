#include "controller_conversion.h"
#include "basic_helpers.h"

/// Maps the values given from the controller to be within a given boundary for proper
/// Duty Cycle calibration
/// - Parameters:
///   - controllerInput: the value received from the controller
///   - returns: A float value to be used as to control the motors
float accel_map(uint8_t controllerInput){
    float newCCR = (float)(controllerInput - ACCEL_TRIGGER_MIN) * 
                    ((ACCEL_CCR_FOR_DUTY_CYCLE_MAX - ACCEL_CCR_FOR_DUTY_CYCLE_MIN) / 
                    (ACCEL_TRIGGER_MAX - ACCEL_TRIGGER_MIN)) + ACCEL_CCR_FOR_DUTY_CYCLE_MIN;
    return newCCR;
}

/// Maps the values given from the controller to be within a given boundary for proper
/// Duty Cycle calibration
/// - Parameters:
///   - controllerInput: the value received from the controller
///   - returns: A float value to be used as to control the motors
float steer_map(uint8_t controllerInput){
    float newCCR = (float)(controllerInput - JOYSTICK_MIN)*
                    ((CCR_FOR_STEERING_MAX - CCR_FOR_STEERING_MIN) / 
                    (JOYSTICK_MAX - JOYSTICK_MIN)) + CCR_FOR_STEERING_MIN;
    return newCCR;
}

/// Maps the values given from the controller to be within a given boundary for proper
/// Duty Cycle calibration
/// - Parameters:
///   - controllerInput: the value received from the controller
///   - returns: A float value to be used as to control the motors
float brake_map(uint8_t controllerInput){
    float newCCR = BRAKING_CCR_FOR_DUTY_CYCLE_MAX - (float)(controllerInput - BRAKE_TRIGGER_MIN) * 
                    ((BRAKING_CCR_FOR_DUTY_CYCLE_MAX - BRAKING_CCR_FOR_DUTY_CYCLE_MIN) / 
                    (BRAKE_TRIGGER_MAX - BRAKE_TRIGGER_MIN));
    return newCCR;
}


/// Determines which way the user is steering the vehicle
/// - Parameters:
///   - calculatedValue: the value received from the controller
void determine_steering_direction(float calculatedValue){
    float baseline = (ACCEL_CCR_FOR_DUTY_CYCLE_MAX - ACCEL_CCR_FOR_DUTY_CYCLE_MIN) / 2;
    if (calculatedValue < baseline - baseline*STEERING_THRESHOLD){
        CURRENT_STEERING = LEFT;
        INSIDE_WHEELS = make_tuple(FRONT_LEFT, BACK_RIGHT);
        OUTSIDE_WHEELS = make_tuple(FRONT_RIGHT, BACK_LEFT);
    }
    else if (calculatedValue > (baseline + baseline*STEERING_THRESHOLD)){
        CURRENT_STEERING = RIGHT;
        INSIDE_WHEELS = make_tuple(FRONT_RIGHT, BACK_LEFT);
        OUTSIDE_WHEELS= make_tuple(FRONT_LEFT, BACK_RIGHT);
    }
    else CURRENT_STEERING = NEUTRAL;
}

float get_duty_cycle(float ccrVal){
    return (ccrVal/144) * 100;
}
