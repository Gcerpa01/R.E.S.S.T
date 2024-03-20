#include "automatic_transmission.h"

/**
 * @abstract: Controls the transmission of the vehicle dependent on two
 *              factors: if traction control is on and is the vehicle on land
 *  
 */
void transmission_shift() {

    // printf("The following Throttle is being read: %d, while Traction Control is: %s\r\n", ACC_THROTTLE,TRACTION_CONTROL ? "ON" : "OFF");
    //Send received value to all motors when no traction control or on water
    if (!TRACTION_CONTROL || !ON_LAND){
        if (BRAKE_THROTTLE) {
          THROTTLE_INPUT = brake_map(BRAKE_THROTTLE);
          send_input_to_all_motors(THROTTLE_INPUT);
        }
        else if (!SQUARE) {
          THROTTLE_INPUT = BRAKING_CCR_FOR_DUTY_CYCLE_MIN;
          send_input_to_all_motors(BRAKING_CCR_FOR_DUTY_CYCLE_MIN);
        }
        else if (!TRIANGLE) {
          THROTTLE_INPUT = 110;
          send_input_to_all_motors(110);
        }
        else if (!CIRCLE) {
        	THROTTLE_INPUT = ACCEL_CCR_FOR_DUTY_CYCLE_MAX;
        	send_input_to_all_motors(ACCEL_CCR_FOR_DUTY_CYCLE_MAX);
        }
        else {
          THROTTLE_INPUT = accel_map(ACC_THROTTLE);
          send_input_to_all_motors(THROTTLE_INPUT);
        }
    }
    else if (TRACTION_CONTROL && ON_LAND){
        if(BRAKE_THROTTLE) { //Kill throttle and traction control for braking
          THROTTLE_INPUT = brake_map(BRAKE_THROTTLE);
          send_input_to_all_motors(THROTTLE_INPUT);
        }
        else if (THROTTLE_INPUT) { //take user input and modify it as necessary
          THROTTLE_INPUT = accel_map(ACC_THROTTLE);
          send_input_to_all_motors(THROTTLE_INPUT);
        }
    }
}

/**
 * @abstract: Simulates the driver by controlling the steering and throttle
 *            Also allows for turning off and on the traction control with the addidion
 *             of land or no land setting
 *  
 */
void driver() {
    // Toggle Traction Control on press
    if (!L1 && !traction_toggle_lock) {
        TRACTION_CONTROL = !TRACTION_CONTROL;
        printf("Traction control switched from %s to %s\n", TRACTION_CONTROL ? "false" : "true", TRACTION_CONTROL ? "true" : "false");
        traction_toggle_lock = 1;
    }
    if (L1) {
        traction_toggle_lock = 0;
        reset_PID_controllers(LAND_CONTROLLERS,4);
    }

    // Toggle if the vehicle is on land or not
    if (!CROSS && !land_toggle_lock) {
        ON_LAND = !ON_LAND;
        printf("Land toggle switched from %s to %s\n", ON_LAND ? "false" : "true", ON_LAND ? "true" : "false");
        land_toggle_lock = 1;
        reset_PID_controllers(LAND_CONTROLLERS,4);
    }
    if (CROSS) {
        land_toggle_lock = 0;
    }

    //add steering detection function
    transmission_shift();
}

