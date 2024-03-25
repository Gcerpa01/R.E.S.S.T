#include "motor_control.h"


/**
 * @abstract: Sends a given value to all motors
 * @param passedCCR:  the value being sent to simulate a duty cycle
 * 
 */
void send_input_to_all_land_motors(int passedCCR){
	//  printf("The following Duty Cycle is being sent to all channels: %.2f\r\n", get_duty_cycle(passedCCR));
	// printf("The following CCR is being sent to all channels: %d\r\n", passedCCR);
    TIM1->CCR1 = passedCCR;
    TIM1->CCR2 = passedCCR;
    TIM1->CCR3 = passedCCR;
    TIM1->CCR4 = passedCCR;
}

/**
 * @abstract: Sends a given value to all motors
 * @param passedCCR: the value being sent to simulate a duty cycle
 * @param motor: the motor who's duty cycle is being changed
 *  
 */
void send_to_land_motor(int passedCCR, int motor){
	switch(motor){
		case 0:
			TIM1->CCR1 = passedCCR;
			// printf("Duty Cycle of: %.2f is being sent to channel: %d\n", get_duty_cycle(passedCCR,LAND_MOTOR_PERIOD), (motor+1));
			break;
		case 1:
			TIM1->CCR2 = passedCCR;
			// printf("Duty Cycle of: %.2f is being sent to channel: %d\n", get_duty_cycle(passedCCR,LAND_MOTOR_PERIOD), (motor+1));
			break;
		case 2:
			TIM1->CCR3 = passedCCR;
			// printf("Duty Cycle of: %.2f is being sent to channel: %d\n", get_duty_cycle(passedCCR,LAND_MOTOR_PERIOD), (motor+1));
			break;
		case 3:
			TIM1->CCR4 = passedCCR;
			// printf("Duty Cycle of: %.2f is being sent to channel: %d\n", get_duty_cycle(passedCCR,LAND_MOTOR_PERIOD), (motor+1));
			break;
		default:
			// printf("Invalid wheel number or no wheel is slipping\n");
			break;
	}
}
