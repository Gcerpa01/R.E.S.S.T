#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H_

#include "projectConstants.h"
#include <stdint.h>

void send_input_to_all_motors(float dutyCycle);

#endif