#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H_

#include "projectConstants.h"
#include <stdint.h>

void send_input_to_all_motors(float dutyCycle);
<<<<<<< HEAD

#endif
=======
void send_to_motor(float dutyCycle, int motor);

#endif
>>>>>>> 78eba411743ede4e7625d965d6f28b9df964bafe
