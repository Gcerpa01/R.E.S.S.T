#ifndef CONTROLLER_CONVERSION_H_
#define CONTROLLER_CONVERSION_H_

#include <stdint.h>
#include "projectConstants.h"
#include "basic_helpers.h"

int land_accel_map(int controllerInput);
int land_steer_map(int controllerInput);
int land_brake_map(int controllerInput);
void determine_land_steering_direction(float calculatedValue);
#endif
