#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H_

#include "projectConstants.h"
#include <stdint.h>

void send_input_to_all_motors(float dutyCycle);
void send_to_motor(float dutyCycle, int motor);

#endif
