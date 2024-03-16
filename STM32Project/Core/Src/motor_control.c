#include "motor_control.h"

/// Sends a given value to all motors
/// - Parameters:
///   - dutyCycle: the value being sent to simulate a duty cycle
void send_input_to_all_motors(float dutyCycle){
    TIM1->CCR1 = dutyCycle;
    TIM1->CCR2 = dutyCycle;
    TIM1->CCR3 = dutyCycle;
    TIM1->CCR4 = dutyCycle;
}

/// Sends a given value to a specific motor
/// Duty Cycle calibration
/// - Parameters:
///   - dutyCycle: the value being sent to simulate a duty cycle
///   - motor: the motor who's duty cycle is being changed
void send_to_motor(float dutyCycle, int motor){
	switch(motor){
		case 0:
			TIM1->CCR1 = dutyCycle;
			break;
		case 1:
			TIM1->CCR2 = dutyCycle;
			break;
		case 2:
			TIM1->CCR3 = dutyCycle;
			break;
		case 3:
			TIM1->CCR4 = dutyCycle;
			break;
	}
}
