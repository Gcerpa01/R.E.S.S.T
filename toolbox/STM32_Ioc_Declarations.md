# Current STM32 Declarations needed to be made within ioc file if new additions are to be made

## Order of declaration in ioc(seems to matter for some reason)
    1. UART1
    2. UART2
    3. TIM1

## UART 1
    - Mode = Asynchronous
    - NVIC Tab -> Enable global interrupt
    - Rx Pin = PA10 -> D2
    - Tx Pin = PA9 -> D8

## UART 2
    - Default
    - NVIC Tab -> Enable global interrupt

## TIM1
    - Clock Source = Internal CLOCK
    - Channel1 = PWM Gen CH1 = Front Right Wheel -> PC0 -> A5
    - Channel2 = PWM Gen CH2 = Front Left Wheel -> PC1 -> A4
    - Channel3 = PWM Gen CH3 = Back Right Wheel -> PC2 -> Header on Left edge across A4
    - Channel4 = PWM Gen CH4 = Back Left Wheel -> PC3 -> Header on Left edge across A5

## EXTIS(Used for HALL EFFECT)
    - PB10  = Front Right Wheel -> D6
    - PB11 = Front Left Wheel -> Header on Right edge across D10
    - PB0 = Back Right Wheel -> A3
    - PA5 = Back Left Wheel -> D13

## TIM3
    - Prescaler = 7200 - 1
    - period = 10000 - 1;