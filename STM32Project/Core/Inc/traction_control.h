#ifndef TRACTION_CONTROL_H_
#define TRACTION_CONTROL_H_

#include "projectConstants.h"
#include "motor_control.h"
#include "controller_conversion.h"

extern Stack *WHEELS_WITH_TRACTION;
extern Stack *WHEELS_WITHOUT_TRACTION;

void initialize_traction_control();
void calculateRPM();
void determineSlippage();
float calculateAverage(size_t current);
void linearTraction(int currCCR);
float get_duty_cycle(int passedCCR, int period);
float performPID(PID_controller targetMotor, float targetRPM);

#endif
