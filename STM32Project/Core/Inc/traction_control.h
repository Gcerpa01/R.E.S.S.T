#ifndef TRACTION_CONTROL_H_
#define TRACTION_CONTROL_H_

#include "projectConstants.h"
#include "motor_control.h"

void calculateRPM();
void determineSlippage();
float calculateAverage(size_t current);
void linearTraction(float currDutyCycle);
#endif
