#ifndef CONTROLLER_CONVERSION_H_
#define CONTROLLER_CONVERSION_H_

#include "projectConstants.h"
#include <stdint.h>

int accel_map(int controllerInput);
int steer_map(int controllerInput);
int brake_map(int controllerInput);
void determine_steering_direction(float calculatedValue);
#endif
