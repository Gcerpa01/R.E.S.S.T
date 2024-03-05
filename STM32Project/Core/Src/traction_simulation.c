#include "traction_control.h"

int main(void){
    for(int i = 0; i <sizeof(RPM_VALUES)/sizeof(RPM_VALUES[0]); i++){
        printf("Enter value of Wheel %d\n", i);
        scanf("%d", &RPM_VALUES[i]);
    }

    printf("Enter Steering Position (NEUTRAL, LEFT, or RIGHT):\n");
    scanf("%s", &CURRENT_STEERING);
    printf("Steering %s", CURRENT_STEERING);
    determineSlippage();   

    return (0);
}