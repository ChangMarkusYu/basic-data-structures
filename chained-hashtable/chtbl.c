#include "./include/chtbl.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int chtbl_init(CHTbl *htbl, int buckets, int (*h)(const void *key), int (*match)(const void *key1, const void *key2), void (*destroy)(void *data))
{
    if ((htbl->table = (List *)malloc(sizeof(List) * buckets)) == NULL)
        return -1;

    htbl->buckets = buckets;
    for (int i = 0; i < buckets; ++i)
        list_init(&htbl->table[i], destroy);

    htbl->h = h;
    htbl->match = match;
    htbl->destroy = destroy;
    htbl->size = 0;
    return 0;
}

void chtbl_destroy(CHTbl *htbl)
{
    for (int i = 0; i < htbl->buckets; ++i)
        list_destroy(&htbl->table[i]);

    free(htbl->table);
    memset(htbl, 0, sizeof(CHTbl));
    return;
}

int chtbl_insert(CHTbl *htbl, const void *data)
{
    void *temp = (void *)data;
    int retval;

    if (chtbl_lookup(htbl, &temp) == 0)
        return 1;

    int bucket = htbl->h(data) % htbl->buckets;
    if ((retval = list_ins_next(&(htbl->table[bucket]), NULL, data)) == 0)
        htbl->size++;

    return retval;
}

int chtbl_remove(CHTbl *htbl, void **data)
{
    int bucket = htbl->h(*data) % htbl->buckets;
    ListElmt *prev = NULL;

    for (ListElmt *cur = list_head(&(htbl->table[bucket])); cur != NULL; cur = list_next(cur))
    {
        if (htbl->match(*data, list_data(cur)))
        {
            if (list_rem_next(&(htbl->table[bucket]), prev, data) == 0)
            {
                htbl->size--;
                return 0;
            }
            else
            {
                return -1;
            }
        }
        prev = cur;
    }
    return -1;
}

int chtbl_lookup(const CHTbl *htbl, void **data)
{
    int bucket = htbl->h(*data) % htbl->buckets;
    for (ListElmt *cur = list_head(&(htbl->table[bucket])); cur != NULL; cur = list_next(cur))
    {
        if (htbl->match(*data, list_data(cur)))
        {
            *data = list_data(cur);
            return 0;
        }
    }
    return -1;
}