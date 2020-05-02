#include <stdlib.h>
#include "./include/set.h"
#include "./include/list.h"

void set_init(Set *set, int (*match)(const void *key1, const void *key2), void (*destroy)(void *data))
{
    list_init(set, destroy);
    set->match = match;
}

int set_insert(Set *set, const void *data)
{
    if (set_is_memeber(set, data))
        return 1;

    return list_ins_next(set, list_tail(set), data);
}

int set_remove(Set *set, void **data)
{
    ListElmt *prev = NULL;
    ListElmt *cur = NULL;

    for (cur = list_head(set); cur != NULL; cur = list_next(cur))
    {
        if (set->match(list_data(cur), *data))
            break;
        prev = cur;
    }

    if (cur == NULL)
        return -1;

    return list_rem_next(set, prev, data);
}

int set_union(Set *setu, const Set *set1, const Set *set2)
{
    set_init(setu, set1->match, NULL);

    for (ListElmt *cur = list_head(set1); cur != NULL; cur = list_next(cur))
    {
        if (list_ins_next(setu, list_tail(setu), list_data(cur)) != 0)
        {
            set_destroy(setu);
            return -1;
        }
    }

    for (ListElmt *cur = list_head(set2); cur != NULL; cur = list_next(cur))
    {
        if (set_is_memeber(setu, list_data(cur)))
        {
            continue;
        }
        else
        {
            if (list_ins_next(setu, list_tail(setu), list_data(cur)) != 0)
            {
                set_destroy(setu);
                return -1;
            }
        }
    }
    return 0;
}

int set_intersection(Set *seti, const Set *set1, const Set *set2)
{
    set_init(seti, set1->match, NULL);

    for (ListElmt *cur = list_head(set1); cur != NULL; cur = list_next(cur))
    {
        if (set_is_memeber(set2, list_data(cur)))
        {
            if (list_ins_next(seti, list_tail(seti), list_data(cur)) != 0)
            {
                set_destroy(seti);
                return -1;
            }
        }
    }

    return 0;
}

int set_difference(Set *setd, const Set *set1, const Set *set2)
{
    set_init(setd, set1->match, NULL);

    for (ListElmt *cur = list_head(set1); cur != NULL; cur = list_next(cur))
    {
        if (!set_is_memeber(set2, list_data(cur)))
        {
            if (list_ins_next(setd, list_head(setd), list_data(cur)) != 0)
            {
                set_destroy(setd);
                return -1;
            }
        }
    }

    return 0;
}

int set_is_memeber(const Set *set, const void *data)
{
    for (ListElmt *cur = list_head(set); cur != NULL; cur = list_next(cur))
    {
        if (set->match(list_data(cur), data))
            return 1;
    }

    return 0;
}

int set_is_subset(const Set *set1, const Set *set2)
{
    if (set_size(set1) > set_size(set2))
        return 0;

    for (ListElmt *cur = list_head(set1); cur != NULL; cur = list_next(cur))
    {
        if (!set_is_memeber(set2, list_data(cur)))
            return 0;
    }
    return 1;
}

int set_is_equal(const Set *set1, const Set *set2)
{
    if (set_size(set1) != set_size(set2))
        return 0;

    return set_is_subset(set1, set2);
}