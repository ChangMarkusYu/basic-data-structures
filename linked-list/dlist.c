#include <stdlib.h>
#include <string.h>

#include "./include/dlist.h"

void dlist_init(DList *list, void (*destroy)(void *data))
{
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void dlist_destroy(DList *list)
{
    void *data;
    while (dlist_size(list) > 0)
    {
        if (list->destroy != NULL && dlist_remove(list, dlist_head(list), (void **)&data) == 0)
            list->destroy(data);
    }
    memset(list, 0, sizeof(DList));
    return;
}

int dlist_ins_next(DList *list, DListElmt *element, const void *data)
{
    DListElmt *new_element;
    if (element == NULL && dlist_size(list) != 0)
        return -1;

    if ((new_element = (DListElmt *)malloc(sizeof(DListElmt))) == NULL)
        return -1;
    new_element->data = (void *)data;

    if (dlist_size(list) == 0)
    {
        list->head = new_element;
        list->tail = new_element;
        new_element->next = NULL;
        new_element->prev = NULL;
    }
    else
    {
        if (element->next == NULL)
            list->tail = new_element;
        else
            element->next->prev = new_element;

        new_element->next = element->next;
        new_element->prev = element;
        element->next = new_element;
    }

    list->size++;
    return 0;
}

int dlist_ins_prev(DList *list, DListElmt *element, const void *data)
{
    DListElmt *new_element;
    if (element == NULL && dlist_size(list) != 0)
        return -1;

    if ((new_element = malloc(sizeof(DListElmt))) == NULL)
        return -1;
    new_element->data = (void *)data;

    if (dlist_size(list) == 0)
    {
        list->head = new_element;
        list->tail = new_element;
        new_element->next = NULL;
        new_element->prev = NULL;
    }
    else
    {
        if (element->prev == NULL)
            list->head = new_element;
        else
            element->prev->next = new_element;

        new_element->next = element;
        new_element->prev = element->prev;
        element->prev = new_element;
    }

    list->size++;
    return 0;
}

int dlist_remove(DList *list, DListElmt *element, void **data)
{
    DListElmt *old_element;
    if (dlist_size(list) == 0 || element == NULL)
        return -1;

    if (element->prev == NULL)
        list->head = element->next;
    else
        element->prev->next = element->next;

    if (element->next == NULL)
        list->tail = element->prev;
    else
        element->next->prev = element->prev;

    *data = element->data;
    free(element);
    list->size--;
    return 0;
}
