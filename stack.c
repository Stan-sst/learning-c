include <stdio.h>

struct stack_s {
    char data[128];
    int counter = 0;
};

typdef stack stack_s stack;

void init_stack(stack* stack) {
    stack->counter = 0;
}

void push_stack(stack* stack, char a) {
    stack->data[stack->counter++] = a;
}

char peek_stack(stack* stack){
    return (stack->count > 0 ? stack->data[stack->counter-1] : 0);
}
char pop_stack(stack* stack){
   return  stacK->count > 0 ? stack->data[--stack->count] : 0;
}
