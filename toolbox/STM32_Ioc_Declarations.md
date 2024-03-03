# Current STM32 Declarations needed to be made within ioc file if new additions are to be made

## Order of declaration in ioc(seems to matter for some reason)
    1. UART1
    2. UART2
    3. TIM1

## UART 1
    - Mode = Asynchronous
    - NVIC Tab -> Enable global interrupt
    - Rx Pin = PA10
    - Tx Pin = PA9

## UART 2
    - Default
    - NVIC Tab -> Enable global interrupt

## TIM1
    - Clock Source = Internal CLOCK
    - Channel1 = PWM Gen CH1 -> PC0
    - Channel2 = PWM Gen CH2 -> PC1
    - Channel3 = PWM Gen CH3 -> PC2
    - Channel4 = PWM Gen CH4 -> PC3

