#ifndef CONTROLLER_CONVERSION_H_
#define CONTROLLER_CONVERSION_H_

#include "projectConstants.h"
#include <stdint.h>

float accel_map(uint8_t controllerInput);
float steer_map(uint8_t controllerInput);
float brake_map(uint8_t controllerInput);
void determine_steering_direction(float calculatedValue);
#endif
