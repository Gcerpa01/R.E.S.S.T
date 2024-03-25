#include "basic_helpers.h"


/**
 * @abstract: Creates a stack with enough memory for the desired
 *            capacity
 * @param capcity: the max amount of elements the stack can hold
 *
 */
Stack *create_stack(int capacity){
    if (capacity <= 0) return NULL;

    Stack *stack = malloc(sizeof(Stack));
    if (stack == NULL) return NULL;
    //make enough space for capacity
    stack->collection = malloc(sizeof(PID_controller) * capacity);
    if (stack->collection == NULL) {
        free(stack);
        return NULL;
    }
    stack->capacity = capacity;
    stack->size = 0;

    return stack;
}


/**
 * @abstract: Destroys the stack and used up space
 * @param stack: the stack itself
 *
 */
void destroy_stack(Stack *stack){
    free(stack->collection);
    free(stack);
};


/**
 * @abstract: Checks if the stack is full
 * @param stack: the stack itself
 *
 */
bool is_full(Stack *stack){
    return stack->capacity == stack->size;
};


/**
 * @abstract: Checks if the stack is empty
 * @param stack: the stack itself
 *
 */
bool is_empty(Stack *stack){
    return stack->size == 0;
};


/**
 * @abstract: Pushes to the top of the stack
 * @param stack: the stack to push to
 * @param item: the value to push to the stack
 *
 */
bool push(Stack *stack, PID_controller item){
    if (is_full(stack)) return false;
    stack->collection[stack->size] = item;
    stack->size++;
    return true;
};


/**
 * @abstract: Pops the last element of the stack to a variable
 * @param stack: the stack to pop from
 * @param item: the reference/address location to save the popped value to
 *
 */
bool pop(Stack *stack, PID_controller *item){
    if(is_empty(stack)) return false;
    stack->size--;
    *item = stack->collection[stack->size];
    return true;
}


/**
 * @abstract: Gets the size of a stack
 * @param stack: the stack itself to get the size of
 *
 */
int get_size(Stack *stack){
    return stack->size;
}


/**
 * @abstract: Makes a tuple
 * @param key: the intial value to be paired with the second value
 * @param value: the second value to be paired wit the intiial value 
 *
 */
tuple make_tuple(PID_controller key, PID_controller value){
    tuple newTuple;
    newTuple.a = key;
    newTuple.b = value;
    return newTuple;
}

// Function to initialize a 
/**
 * @abstract: Creates a PID_controller instance with specific values
 * @param Kp: the proprotinal error to be assigned to the controller
 * @param Ki: the integral errror to be assigned to the controller
 * @param Kd: the derivative error to be assigned to the controller
 * @param wheel_position: the controllers position in reference to the motor
 * @param hall_effect_count: the count of times the hall effect sensor has been read by the motor
 * @param rpm: the calculated rpm of the motor
 *
 */
void create_PID_controller(PID_controller *controller, float Kp, float Ki, float Kd, int wheel_position, int hall_effect_count, float rpm){
    controller->Kp = Kp;
    controller->Ki = Ki;
    controller->Kd = Kd;
    controller->error_sum = 0.0f;
    controller->prev_error = 0.0f;
    controller->wheel_position = wheel_position;
    controller->hall_effect_count = hall_effect_count;
    controller->rpm = rpm;
}


/**
 * @abstract: Creates an array of PID controllers
 * @param Kps: the array containing the KP to be assigned to each controller
 * @param Kis: the array containing the KI to be assigned to each controller
 * @param Kds: the array containing the KD to be assigned to each controller
 * @param wheel_positions: the array containing the controllers position in reference to the motor
 * @param LAND_CONTROLLERS: the array holding the created PID controllers
 * @param size: the size of the array to hold the controllers
 *
 */
void init_PID_controllers(float Kps[], float Kis[], float Kds[], int wheel_positions[], PID_controller LAND_CONTROLLERS[], int size) {
    for (int i = 0; i < size; i++) {
    	create_PID_controller(&LAND_CONTROLLERS[i], Kps[i], Kis[i], Kds[i], wheel_positions[i], 0, 0.0f);
    }
}

/**
 * @abstract: Clears the data inside a PID Controller
 * @param controller: the controller who's data will be cleared
 *  
 */
void clear_PID_controller(PID_controller *controller){
    // controller->error_sum = 0.0f; //may want to leave this
    // controller->prev_error = 0.0f;
    controller->hall_effect_count = 0;
    controller->rpm = 0.0f;
}

/**
 * @abstract: Resets all the PID controllers in an array
 * @param controllers: the array containing the controllers to be reset
 * @param sie: the size of the array
 */
void reset_PID_controllers(PID_controller controllers[], int size){
    for (int i = 0; i < size; i++) {
        clear_PID_controller(&controllers[i]);
    }
}
