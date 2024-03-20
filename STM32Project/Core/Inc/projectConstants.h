#ifndef PROJECT_CONSTANTS_H_
#define PROJECT_CONSTANTS_H_

#include <main.h>
#include <stdio.h>
#include "basic_helpers.h"
#include <math.h>

//Values needed for controlling steering 
#define JOYSTICK_MIN -255
#define JOYSTICK_MAX 255
#define CCR_FOR_STEERING_MIN 1
#define CCR_FOR_STEERING_MAX 90
#define STEERING_THRESHOLD 0.01
#define WHEEL_BASE 7 //defined in inches (0.583ft)
#define SERVO_ANGLE_MAX 180
#define SERVO_ANGLE_MIN 0

//Values needed for accellerating motors
#define ACCEL_TRIGGER_MIN 0
#define ACCEL_TRIGGER_MAX 255
#define ACCEL_CCR_FOR_DUTY_CYCLE_MIN 108
#define ACCEL_CCR_FOR_DUTY_CYCLE_MAX 144
#define BRAKE_TRIGGER_MIN 0
#define BRAKE_TRIGGER_MAX 255
#define BRAKING_CCR_FOR_DUTY_CYCLE_MIN 72
#define BRAKING_CCR_FOR_DUTY_CYCLE_MAX 108

//Values needed for tracking RPM
#define POLES 2
#define LINEAR_TRACTION_THRESHOLD 0.05
#define TURNING_TRACITON_THRESHOLD 0.02
extern int HALL_EFFECT_SENSORS[4];
extern float RPM_VALUES[4];

//Values needed for controlling the vehicle
#define ACC_THROTTLE CONTROLLER_VALUES[0]
#define BRAKE_THROTTLE CONTROLLER_VALUES[1]
#define JOYSTICK CONTROLLER_VALUES[2]
#define CROSS CONTROLLER_VALUES[3]
#define CIRCLE CONTROLLER_VALUES[4]
#define SQUARE CONTROLLER_VALUES[5]
#define TRIANGLE CONTROLLER_VALUES[6]
#define L1 CONTROLLER_VALUES[7]
extern int CONTROLLER_VALUES[8];
extern bool TRACTION_CONTROL;
extern bool ON_LAND;
extern int JOYSTICK_INPUT;
extern int THROTTLE_INPUT;

//Tracking Steering
enum STEER {
    LEFT,
    RIGHT,
    NEUTRAL
};
extern enum STEER CURRENT_STEERING;

//Tracking Slippage and Traction
enum MOTORS {
    FRONT_RIGHT,
    FRONT_LEFT,
    BACK_RIGHT,
    BACK_LEFT,
    NONE
};
extern enum MOTORS WHEEL;

//MISC
#define MAX_RPM_VALUE 1000000
#define MIN_RPM_VALUE -1000000

extern tuple INSIDE_WHEELS;
extern tuple OUTSIDE_WHEELS;

extern Stack *WHEELS_WITH_TRACTION;
extern Stack *WHEELS_WITHOUT_TRACTION;

#endif
