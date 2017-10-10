#include <stdlib.h>

#include "stack.h"

#define INITIAL_BUFFER_SIZE 8

int _realloc_buffer(Stack* stack);

Stack* create_stack() {
    Stack* stack = malloc(sizeof(Stack));
    if (!stack) {
        fprintf(stderr, "Memory allocation error while creating stack.");
        return NULL;
    }
    stack->buffer = malloc(INITIAL_BUFFER_SIZE);
    if (!stack->buffer) {
        fprintf(stderr, "Memory allocation error while creating buffer of stack.");
        free(stack);
        stack = NULL;
        return NULL;
    }
    stack->buffer_size = INITIAL_BUFFER_SIZE;
    stack->count = 0;

    return stack;
}

int stack_push(Stack* stack, char symbol) {
    if (!stack) {
        fprintf(stderr, "Stack is not allocated.");
        return STACK_WRONG_ARGUMENT;
    }

    if (stack->count + 1 == stack->buffer_size) {
        if (_realloc_buffer(stack))
            free_stack(stack);
            return STACK_MEMORY_ERROR;
    }

    stack->buffer[stack->count] = symbol;
    stack->count++;

    return STACK_SUCCESS;
}

char stack_top(const Stack* stack) {
    if (!stack) {
        fprintf(stderr, "Stack is not allocated.");
        return 0;
    }

    return stack->buffer[stack->count - 1];
}

int stack_pop(Stack* stack) {
    if (!stack) {
        fprintf(stderr, "Stack is not allocated.");
        return STACK_WRONG_ARGUMENT;
    }

    stack->count--;

    return STACK_SUCCESS;
}

size_t stack_get_size(const Stack* stack) {
    if (!stack) {
        fprintf(stderr, "Stack is not allocated.");
        return 0;
    }

    return stack->count;
}

int stack_is_empty(const Stack* stack) {
    if (!stack) {
        fprintf(stderr, "Stack is not allocated.");
        return 0;
    }

    return stack->count == 0;
}

int free_stack(Stack* stack) {
    if (!stack) {
        fprintf(stderr, "Stack is not allocated.");
        return STACK_WRONG_ARGUMENT;
    }

    free(stack->buffer);
    stack->buffer = NULL;
    free(stack);
    stack = NULL;

    return STACK_SUCCESS;
}

int _realloc_buffer(Stack* stack) {
    char* tmp = realloc(stack->buffer, sizeof(stack->buffer) * stack->buffer_size * 2);
    if (!tmp) {
        fprintf(stderr, "Memory reallocation error while expanding the buffer.");
        free_stack(stack);
        return STACK_MEMORY_ERROR;
    }
    stack->buffer = tmp;

    return STACK_SUCCESS;
}
