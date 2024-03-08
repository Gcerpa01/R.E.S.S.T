#include "basic_helpers.h"

Stack *create_stack(int capacity){
    if (capacity <= 0) return NULL;

    Stack *stack = malloc(sizeof(Stack));
    if (stack == NULL) return NULL;
    //make enough space for capacity
    stack->collection = malloc(sizeof(int) * capacity);
    if (stack->collection == NULL) {
        free(stack);
        return NULL;
    }
    stack->capacity = capacity;
    stack->size = 0;

    return stack;
}

/// Destroys the stack and used up space
/// - Parameters:
///   - stack: the stack itself
void destroy_stack(Stack *stack){
    free(stack->collection);
    free(stack);
};

/// Checks if the stack is full
/// - Parameters:
///   - stack: the stack itself
bool is_full(Stack *stack){
    return stack->capacity == stack->size;
};

/// Checks if the stack is empty
/// - Parameters:
///   - stack: the stack itself
bool is_empty(Stack *stack){
    return stack->size == 0;
};


/// Pushes to the top of the stack 
/// - Parameters:
///   - stack: the stack to push to
///   - item: the value to push to the stack
bool push(Stack *stack, int item){
    if (is_full(stack)) return false;
    stack->collection[stack->size] = item;
    stack->size++;
    return true;
};


/// Pops the last element of the stack to a variable
/// - Parameters:
///   - stack: the stack to pop from
///   - item: the reference/address location to save the popped value to
bool pop(Stack *stack, int *item){
    if(is_empty(stack)) return false;
    stack->size--;
    *item = stack->collection[stack->size];
    return true;
}

/// Finds the size of the stack 
/// - Parameters:
///   - stack: the stack itself to get the size of
int get_size(Stack *stack){
    return stack->size;
}

/// Makes a tuple
/// - Parameters:
///   - key: the intial value to be paired with the second value
///   - value: the second value to be paired wit the intiial value 
tuple make_tuple(int key, int value){
    tuple newTuple;
    newTuple.a = key;
    newTuple.b = value;
    return newTuple;
}


/// Resets the tuple to 0 for both values
/// - Parameters:
///   - tuple: the tuple to reset 
void delete_tuple(tuple *tuple){
    tuple->a = 0;
    tuple->b = 0;
}
