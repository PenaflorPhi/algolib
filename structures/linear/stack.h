#ifndef STACK_H
#define STACK_H

#include <stddef.h>

typedef struct s_stack {
    size_t nmemb;
    size_t size;
    char **elements;
} S_Stack;

S_Stack s_stack_init(size_t size);
void    s_stack_delete(S_Stack *stack);
void    s_stack_pop(S_Stack *stack);
void    s_stack_push(S_Stack *stack, char *s);
void    print_s_stack(S_Stack *stack);

#endif // !STACK_H
