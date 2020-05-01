#include <stdio.h>
#include "./include/stack.h"

int main()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack_init(stack, free);
    for (int i = 0; i < 10; ++i)
    {
        int *data = malloc(sizeof(int));
        *data = i;
        stack_push(stack, data);
    }

    while (stack_size(stack) > 0)
    {
        int *data = NULL;
        stack_pop(stack, (void **)&data);
        printf("%d\n", *data);
        free(data);
    }

    stack_destroy(stack);
    return 0;
}