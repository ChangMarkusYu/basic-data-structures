#include <stdio.h>
#include "./include/set.h"

int match(const void *key1, const void *key2);
void print_set(const Set *set);

int main()
{
    Set *set1 = malloc(sizeof(Set));
    Set *set2 = malloc(sizeof(Set));
    Set *set_res = malloc(sizeof(Set));
    set_init(set1, match, free);
    set_init(set2, match, free);

    for (int i = 0; i < 5; ++i)
    {
        int *data = malloc(sizeof(int));
        *data = i;
        set_insert(set1, (void *)data);
    }

    for (int i = 2; i < 7; ++i)
    {
        int *data = malloc(sizeof(int));
        *data = i;
        set_insert(set2, (void *)data);
    }
    printf("Set1: \n");
    print_set(set1);
    printf("Set2:\n");
    print_set(set2);

    printf("Union of set1 and set2: \n");
    set_union(set_res, set1, set2);
    print_set(set_res);

    printf("Intersection of set1 and set2: \n");
    set_intersection(set_res, set1, set2);
    print_set(set_res);

    printf("Difference of set1 and set2: \n");
    set_difference(set_res, set1, set2);
    print_set(set_res);

    set_destroy(set1);
    set_destroy(set2);
    set_destroy(set_res);
    return 0;
}

int match(const void *key1, const void *key2)
{
    return *(const int *)key1 == *(const int *)key2;
}

void print_set(const Set *set)
{
    for (ListElmt *cur = list_head(set); cur != NULL; cur = list_next(cur))
        printf("%d ", *(int *)list_data(cur));
    printf("\n\n");
}
