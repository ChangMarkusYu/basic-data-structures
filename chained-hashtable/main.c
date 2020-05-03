#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "./include/chtbl.h"

#define A 0.618
#define m 2000

int hash(const void *key);
int match(const void *key1, const void *key2);

int main()
{
    CHTbl tbl;
    chtbl_init(&tbl, m, hash, match, free);

    for (int i = 0; i < 1000; ++i)
    {
        int *data = malloc(sizeof(int));
        *data = i;
        chtbl_insert(&tbl, (void *)data);
    }

    for (int i = 100; i < 500; ++i)
    {
        int *data = malloc(sizeof(int));
        *data = i;
        chtbl_insert(&tbl, (void *)data);
    }

    printf("Hashtable size: %d\n", chtbl_size(&tbl));
    int i = 20;
    int *ptr = &i;
    if (chtbl_lookup(&tbl, (void **)&ptr) == 0)
        printf("%d\n", i);

    for (i = 0; i < 1000; ++i)
    {
        ptr = &i;
        if (chtbl_lookup(&tbl, (void **)&ptr) != 0)
        {
            printf("insert failed\n");
            break;
        }
    }

    for (i = 200; i < 700; ++i)
    {
        int *data = &i;
        chtbl_remove(&tbl, (void **)&data);
        free(data);
    }

    for (i = 200; i < 700; ++i)
    {
        ptr = &i;
        if (chtbl_lookup(&tbl, (void **)&ptr) == 0)
        {
            printf("removal failed.\n");
            break;
        }
    }
    printf("Hashtable size after removal: %d\n", chtbl_size(&tbl));
    chtbl_destroy(&tbl);
    return 0;
}

int hash(const void *key)
{
    int *temp = (int *)key;
    int res = (int)floor(m * fmod((*temp) * A, 1.0));
    return res;
}

int match(const void *key1, const void *key2)
{
    return *(const int *)key1 == *(const int *)key2;
}