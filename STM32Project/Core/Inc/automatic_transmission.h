#ifndef AUTOMATIC_TRANSMISSION_H_
#define AUTOMATIC_TRANSMISSION_H_

#include "traction_control.h"
#include "projectConstants.h"

void transmission_shift();
void driver();

// Flags to track toggles
static int traction_toggle_lock = 0;
static int land_toggle_lock = 0;

#endif
