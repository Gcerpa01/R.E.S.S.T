#ifndef TRACTION_CONTROL_H_
#define TRACTION_CONTROL_H_

#include "projectConstants.h"
<<<<<<< HEAD
=======
#include "motor_control.h"
>>>>>>> 78eba411743ede4e7625d965d6f28b9df964bafe

void calculateRPM();
void determineSlippage();
float calculateAverage(size_t current);
<<<<<<< HEAD
#endif
=======
void linearTraction(float currDutyCycle);
#endif
>>>>>>> 78eba411743ede4e7625d965d6f28b9df964bafe
