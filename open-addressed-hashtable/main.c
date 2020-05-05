#include <stdio.h>
#include <string.h>
#include "./include/ohtbl.h"

#define m 1699 // m has to be a prime number

int hash1(const void *key);
int hash2(const void *key);
int match(const void *key1, const void *key2);

int main()
{
    OHTbl *htbl = malloc(sizeof(OHTbl));
    ohtbl_init(htbl, m, hash1, hash2, match, free);
    int i;

    for (i = 0; i < 500; ++i)
    {
        int *data = malloc(sizeof(int));
        *data = i;
        ohtbl_insert(htbl, (void *)data);
    }
    printf("Hashtable size: %d\n", ohtbl_size(htbl));

    for (i = 150; i < 250; ++i)
    {
        int *data = malloc(sizeof(int));
        *data = i;
        if (ohtbl_insert(htbl, (void *)data) != 1)
            printf("insert failed\n");
    }

    printf("Hashtable size: %d\n", ohtbl_size(htbl));

    int *ptr;
    for (i = 0; i < 500; ++i)
    {
        ptr = &i;
        if (ohtbl_lookup(htbl, (void **)&ptr) != 0)
        {
            printf("insert failed.\n");
            break;
        }
    }

    for (i = 200; i < 300; ++i)
    {
        ptr = &i;
        if (ohtbl_remove(htbl, (void **)&ptr) != 0)
            printf("remove failed\n");
        free(ptr);
    }

    for (i = 200; i < 300; ++i)
    {
        ptr = &i;
        if (ohtbl_lookup(htbl, (void **)&ptr) != -1)
        {
            printf("remove failed.\n");
            break;
        }
    }
    printf("Hashtable size after removal: %d\n", ohtbl_size(htbl));
    ohtbl_destroy(htbl);
    return 0;
}

int hash1(const void *key)
{
    return *(int *)key % m;
}

int hash2(const void *key)
{
    return 1 + (*(int *)key % (m - 2));
}

int match(const void *key1, const void *key2)
{
    return *(const int *)key1 == *(const int *)key2;
}