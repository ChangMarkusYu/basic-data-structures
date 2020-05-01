#include <stdio.h>
#include "./include/queue.h"

int main()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    for (int i = 0; i < 10; ++i)
    {
        int *data = malloc(sizeof(int));
        *data = i;
        queue_enqueue(queue, data);
    }

    while (queue_size(queue) > 0)
    {
        int *data = NULL;
        queue_dequeue(queue, (void **)&data);
        printf("%d ", *data);
        free(data);
    }
    printf("\n");

    queue_destroy(queue);
    return 0;
}