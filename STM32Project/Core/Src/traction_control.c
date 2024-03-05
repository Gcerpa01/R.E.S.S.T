#include "traction_control.h"
//Calculate the RPM for each wheel and save it in memory
void calculateRPM(){
    for(size_t i = 0; i < sizeof(HALL_EFFECT_SENSORS)/sizeof(HALL_EFFECT_SENSORS[0]); i++){
        RPM_VALUES[i] = (HALL_EFFECT_SENSORS[i] / POLES) * 60;
    }
}

float calculateAverageRPM(size_t current){
    float temp = 0;
    for(size_t j = 0; j < sizeof(RPM_VALUES)/sizeof(RPM_VALUES[0]); j++){
        if(current == j) continue;
        temp+= RPM_VALUES[j];
    }
    return temp/(sizeof(RPM_VALUES)/sizeof(RPM_VALUES[0]) - 1);
}

void determineSlippage(){
    if(CURRENT_STEERING == NEUTRAL){
        float maxVal = MIN_RPM_VALUE;
        //Calculate each wheels RPM to the avergae of all the others
        for(size_t i = 0; i < sizeof(RPM_VALUES)/sizeof(RPM_VALUES[0]); i++){
            float averageRPM = calculateAverageRPM(i);
            float threshMin = averageRPM * (1 - LINEAR_TRACTION_THRESHOLD);
            float threshMax = averageRPM * (1 + LINEAR_TRACTION_THRESHOLD);

            //Check if its above or below the threshold
            if((RPM_VALUES[i] > threshMax || RPM_VALUES[i] < threshMin)){
                //Prioritize the wheel with the worst traction
                if(RPM_VALUES[i] > maxVal){
                    maxVal = RPM_VALUES[i];
                    WHEEL = i;
                }
                printf("Slippage Detected: Wheel %d", i);
            }
        }
    }
}


