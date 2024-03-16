#ifndef BASIC_HELPERS_H_
#define BASIC_HELPERS_H_

#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int a;
    int b;
} tuple;

typedef struct
{
    int *collection;
    int capacity;
    int size;
} Stack;

Stack *create_stack(int capacity);
void destroy_stack(Stack *stack);
bool is_full(Stack *stack);
bool is_empty(Stack *stack);
bool push(Stack *stack, int item);
bool peek(Stack *stack, int *item);
bool pop(Stack *stack, int *item);
int get_size(Stack *stack);
tuple make_tuple(int key, int value);
void delete_tuple(tuple *tuple);

#endif
