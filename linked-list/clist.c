#include "./include/clist.h"

void clist_init(CList *list, void (*destroy)(void *data))
{
    list->head = NULL;
    list->size = 0;
    list->destroy = destroy;
    return;
}

void clist_destroy(CList *list)
{
    void *data;
    while (clist_size(list) > 0)
    {
        if (list->destroy != NULL && clist_rem_next(list, clist_head(list), (void **)&data) == 0)
            list->destroy(data);
    }
    memset(list, 0, sizeof(CList));
    return;
}

int clist_ins_next(CList *list, CListElmt *element, const void *data)
{
    CListElmt *new_element;
    if (clist_size(list) > 0 && element == NULL)
        return -1;

    if ((new_element = (CListElmt *)malloc(sizeof(CListElmt))) == NULL)
        return -1;
    new_element->data = (void *)data;

    if (clist_size(list) == 0)
    {
        list->head = new_element;
        new_element->next = new_element;
    }
    else
    {
        new_element->next = element->next;
        element->next = new_element;
    }
    list->size++;
    return 0;
}

int clist_rem_next(CList *list, CListElmt *element, void **data)
{
    if (element == NULL || list->size == 0)
        return -1;

    CListElmt *old_element = element->next;
    *data = old_element->data;

    if (clist_size(list) == 1)
    {
        list->head = NULL;
    }
    else
    {
        element->next = old_element->next;
        if (old_element == clist_head(list))
            list->head = old_element->next;
    }

    free(old_element);
    list->size--;
    return 0;
}