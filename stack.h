#ifndef C_TASK3_STACK_H
#define C_TASK3_STACK_H

#include <stdio.h>

enum {
    STACK_SUCCESS = 0,
    STACK_WRONG_ARGUMENT,
    STACK_MEMORY_ERROR,
};

typedef struct Stack {
    char* buffer;
    size_t count;
    size_t buffer_size;
} Stack;

Stack* create_stack();
int stack_push(Stack* stack, char symbol);
char stack_top(const Stack* stack);
int stack_pop(Stack* stack);
size_t stack_get_size(const Stack* stack);
int stack_is_empty(const Stack* stack);
int free_stack(Stack* stack);

#endif //C_TASK3_STACK_H
