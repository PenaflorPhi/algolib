#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

S_Stack s_stack_init(size_t size) {
    S_Stack stack;
    stack.nmemb    = 0;
    stack.size     = size;
    stack.elements = calloc(size, sizeof(char *));

    return stack;
}

void s_stack_delete(S_Stack *stack) {
    for (size_t i = 0; i < stack->nmemb; ++i) {
        free(stack->elements[i]);
    }
    free(stack->elements);
}

void s_stack_pop(S_Stack *stack) {
    if (stack->nmemb > 0) {
        stack->nmemb -= 1;
        free(stack->elements[stack->nmemb]);
        stack->elements[stack->nmemb] = NULL;
    } else {
        fprintf(stderr, "Cannot pop element from stack, stack is empty.\n");
    }
}

void s_stack_push(S_Stack *stack, char *s) {
    if (s == NULL)
        return;
    if (stack->nmemb < stack->size) {
        stack->elements[stack->nmemb]  = s;
        stack->nmemb                  += 1;
    } else {
        fprintf(stderr, "Cannot push element to stack, stack is full.\n");
    }
}

void print_s_stack(S_Stack *stack) {
    printf("[");
    for (size_t i = 0; i < stack->nmemb; ++i) {
        printf("%s", stack->elements[i]);
        if (i != stack->nmemb - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void) {
    S_Stack stack = s_stack_init(10);

    char line[256];
    while (fgets(line, sizeof(line), stdin)) {
        char cmd[16]  = {0};
        char arg[128] = {0};

        int n = sscanf(line, "%15s %127[^\n]", cmd, arg);

        if (strcmp(cmd, "push") == 0 && n == 2) {
            s_stack_push(&stack, strdup(arg));
        } else if (strcmp(cmd, "pop") == 0) {
            s_stack_pop(&stack);
        } else {
            fprintf(stderr, "Unknown command\n");
        }

        print_s_stack(&stack);
    }

    s_stack_delete(&stack);
    return EXIT_SUCCESS;
}
