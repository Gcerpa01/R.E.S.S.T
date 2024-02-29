#include "motor_control.h"

void send_input_to_all_motors(float dutyCycle){
    TIM1->CCR1 = dutyCycle;
    TIM1->CCR2 = dutyCycle;
    TIM1->CCR3 = dutyCycle;
    TIM1->CCR4 = dutyCycle;
}
