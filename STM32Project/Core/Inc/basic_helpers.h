#ifndef BASIC_HELPERS_H_
#define BASIC_HELPERS_H_

#include <stdlib.h>
#include <stdbool.h>
#include "projectConstants.h"

typedef struct {
    float Kp; // Proportional
    float Ki; // Integral
    float Kd; // Derivative

    //error tracking
    float error_sum; 
    float prev_error;
    
    int wheel_position;
    int hall_effect_count;
    float rpm;
} PID_controller;

void init_PID_controllers(float Kps[], float Kis[], float Kds[], int wheel_positions[], PID_controller LAND_CONTROLLERS[], int size);
void create_PID_controller(PID_controller *controller, float Kp, float Ki, float Kd, int wheel_position, int hall_effect_count, float rpm);
void reset_PID_controllers(PID_controller controllers[], int size);
void clear_PID_controller(PID_controller *controller);
extern int CONTROLLER_POSITIONS[4];
extern float KP_VALUES[4];
extern float KI_VALUES[4];
extern float KD_VALUES[4];
extern PID_controller LAND_CONTROLLERS[4];

typedef struct
{
    PID_controller a;
    PID_controller b;
} tuple;

tuple make_tuple(PID_controller key, PID_controller value);

extern tuple INSIDE_WHEELS;
extern tuple OUTSIDE_WHEELS;

typedef struct
{
    PID_controller *collection;
    int capacity;
    int size;
} Stack;

Stack *create_stack(int capacity);
void destroy_stack(Stack *stack);
bool is_full(Stack *stack);
bool is_empty(Stack *stack);
bool push(Stack *stack, PID_controller item);
bool peek(Stack *stack, PID_controller *item);
bool pop(Stack *stack, PID_controller *item);
int get_size(Stack *stack);

extern Stack *WHEELS_WITH_TRACTION;
extern Stack *WHEELS_WITHOUT_TRACTION;


#endif
