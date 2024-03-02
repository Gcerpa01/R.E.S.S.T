#ifndef PROJECT_CONSTANTS_H_
#define PROJECT_CONSTANTS_H_

#include <main.h>

//Values needed for controlling steering 
#define JOYSTICK_MIN -255
#define JOYSTICK_MAX 255

#define CCR_FOR_STEERING_MIN 1
#define CCR_FOR_STEERING_MAX 90

#define STEERING_THRESHOLD 0.01

//Values needed for accellerating motors
#define ACCEL_TRIGGER_MIN 1
#define ACCEL_TRIGGER_MAX 255

#define ACCEL_CCR_FOR_DUTY_CYCLE_MIN 10.8
#define ACCEL_CCR_FOR_DUTY_CYCLE_MAX 14.4

#define BRAKE_TRIGGER_MIN 1
#define BRAKE_TRIGGER_MAX 255

#define BRAKING_CCR_FOR_DUTY_CYCLE_MIN 7.2
#define BRAKING_CCR_FOR_DUTY_CYCLE_MAX 10.8

//Tracking RPM
#define POLES 2
#define LINEAR_TRACTION_THRESHOLD 0.05
#define TURNING_TRACITON_THRESHOLD 0.02

extern int HALL_EFFECT_SENSORS[4];
extern float RPM_VALUES[4];

//Tracking Steering
enum STEER {
    LEFT,
    RIGHT,
    NEUTRAL
};

extern enum STEER CURRENT_STEERING;

//Tracking Slippage
enum SLIPPAGE {
    FRONT_RIGHT,
    FRONT_LEFT,
    BACK_RIGHT,
    BACK_LEFT
};
extern enum SLIPPAGE WHEEL;

//MISC
#define MAX_RPM_VALUE 1000000
#define MIN_RPM_VALUE -1000000

typedef struct 
{
    int a;
    int b;
} tuple;

extern tuple INSIDE_WHEELS;
extern tuple OUTSIDE_WHEELS;

#endif
