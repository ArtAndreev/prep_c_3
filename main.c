#include <stdio.h>

#include "stack.h"

enum {
    SUCCESS = STACK_SUCCESS,
    INITIALISING_ERROR = STACK_WRONG_ARGUMENT,
    CHECK_INTERRUPTED = 3,
};

int open_file_for_checking(int argc, char** argv);
int check_brackets(FILE* file);
int is_bracket(char symbol);
int bracket_step(Stack* brackets_stack, char symbol);
int is_opening_bracket(char symbol);
int is_one_brackets_type(char first, char second);

//
// Program receives one file name. In this file there is one text string.
// Text contains any symbols, among which there are opening and closing brackets in random order: () {} [].
//

int main(int argc, char** argv) {
    int error_num = SUCCESS;

    if ((error_num = open_file_for_checking(argc, argv)))
        return error_num;

    return SUCCESS;
}

int open_file_for_checking(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "One file name must be entered.");
        return INITIALISING_ERROR;
    }
    FILE* file = fopen(argv[1], "r");
    if (!file) {
        fprintf(stderr, "Cannot open the file.");
        return INITIALISING_ERROR;
    }

    int error_num = SUCCESS;

    if ((error_num = check_brackets(file))) {
        fclose(file);
        return error_num;
    }

    fclose(file);

    return SUCCESS;
};

int check_brackets(FILE* file) {
    Stack* brackets_stack = create_stack();

    int error_num = SUCCESS;
    char symbol = 0;

    while (!feof(file)) {
        symbol = (char)fgetc(file);
        if (is_bracket(symbol))
            error_num = bracket_step(brackets_stack, symbol);
        if (error_num == CHECK_INTERRUPTED)
            break;
        if (error_num) {
            free_stack(brackets_stack);
            return error_num;
        }
    }

    if (stack_is_empty(brackets_stack) && !error_num)
        printf("Brackets in file are located in CORRECT order.");
    else
        printf("Brackets in file are located in INCORRECT order.");

    free_stack(brackets_stack);

    return SUCCESS;
}

int is_bracket(char symbol) {
    return symbol == '(' || symbol == '{' || symbol == '[' ||
           symbol == ')' || symbol == '}' || symbol == ']';
}

int bracket_step(Stack* brackets_stack, char symbol) {
    int error_num = SUCCESS;
    char last_bracket = 0;
    if (is_opening_bracket(symbol)) {
        if ((error_num = stack_push(brackets_stack, symbol)))
            return error_num;
    }
    else {
        if (stack_is_empty(brackets_stack))
            return CHECK_INTERRUPTED;
        last_bracket = stack_top(brackets_stack);
        if (is_one_brackets_type(last_bracket, symbol)) {
            stack_pop(brackets_stack);
        }
        else
            return CHECK_INTERRUPTED;
    }

    return SUCCESS;
}

int is_opening_bracket(char symbol) {
    return symbol == '(' || symbol == '{' || symbol == '[';
}

int is_one_brackets_type(char first, char second) {
    if ((first == '(' || first == ')') && (second == '(' || second == ')'))
        return 1;
    if ((first == '{' || first == '}') && (second == '{' || second == '}'))
        return 1;
    if ((first == '[' || first == ']') && (second == '[' || second == ']'))
        return 1;
    return 0;
}
