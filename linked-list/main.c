#include <stdio.h>
#include "./include/list.h"
#include "./include/dlist.h"
#include "./include/clist.h"

int main()
{
    List *list = malloc(sizeof(List));
    list_init(list, free);

    DList *dlist = malloc(sizeof(DList));
    dlist_init(dlist, free);

    CList *clist = malloc(sizeof(CList));
    clist_init(clist, free);

    for (int i = 0; i < 10; ++i)
    {
        int *data1 = malloc(sizeof(int));
        *data1 = i;
        list_ins_next(list, NULL, (void *)data1);

        int *data2 = malloc(sizeof(int));
        *data2 = i;
        dlist_ins_next(dlist, dlist_tail(dlist), (void *)data2);

        int *data3 = malloc(sizeof(int));
        *data3 = i;
        clist_ins_next(clist, clist_head(clist), (void *)data3);
    }

    for (ListElmt *cur = list_head(list); cur != NULL; cur = list_next(list_next(cur)))
    {
        int *data = malloc(sizeof(int));
        *data = 5;
        list_ins_next(list, cur, data);
    }

    for (int i = 1; i < 10; ++i)
    {
        int *data = malloc(sizeof(int));
        *data = i;
        dlist_ins_prev(dlist, dlist_head(dlist), (void *)data);
    }

    printf("Elements in linked list: \n");
    for (ListElmt *cur = list_head(list); cur != NULL; cur = list_next(cur))
    {
        printf("%d ", *(int *)list_data(cur));
    }
    printf("\n");
    list_destroy(list);

    printf("Elements in doubly linked list: \n");
    for (DListElmt *cur = dlist_head(dlist); cur != NULL; cur = dlist_next(cur))
    {
        printf("%d ", *(int *)dlist_data(cur));
    }
    printf("\n");

    printf("Elements in doubly linked list backwards: \n");
    for (DListElmt *cur = dlist_tail(dlist); cur != NULL; cur = dlist_prev(cur))
    {
        printf("%d ", *(int *)dlist_data(cur));
    }
    printf("\n");
    dlist_destroy(dlist);

    printf("Elements in ciruclar linked list: \n");
    CListElmt *cur = clist_head(clist);
    for (int i = 0; i < clist_size(clist); ++i)
    {
        printf("%d ", *(int *)clist_data(cur));
        cur = cur->next;
    }
    printf("\n");
    clist_destroy(clist);

    return 0;
}