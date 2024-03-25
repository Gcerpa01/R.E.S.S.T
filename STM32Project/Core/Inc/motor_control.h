#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H_

#include "projectConstants.h"
#include <stdint.h>
#include "traction_control.h"

void send_input_to_all_land_motors(int passedCCR);
void send_to_land_motor(int passedCCR, int motor);

#endif
