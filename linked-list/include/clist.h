#ifndef CLIST_H
#define CLIST_H

#include <stdlib.h>
#include <string.h>

struct CListElmt_
{
    void *data;
    struct CListElmt_ *next;
};
typedef struct CListElmt_ CListElmt;

struct CList_
{
    int size;

    int (*match)(const void *key1, const void *key2); /* match will be used later for other data structures */
    void (*destroy)(void *data);

    CListElmt *head;
};
typedef struct CList_ CList;

void clist_init(CList *list, void (*destroy)(void *data));

void clist_destroy(CList *list);

int clist_ins_next(CList *list, CListElmt *element, const void *data);

int clist_rem_next(CList *list, CListElmt *element, void **data);

#define clist_size(list) ((list)->size)

#define clist_head(list) ((list)->head)

#define clist_data(element) ((element)->data)

#define clist_next(element) ((element)->next)

#endif
