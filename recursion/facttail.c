#include <stdio.h>
#include "./include/facttail.h"

int main()
{
    int n = 0;
    printf("Enter an integer: \n");
    scanf("%d", &n);

    int ans = facttail(n, 1);
    printf("%d's factorial is: %d\n", n, ans);
    return 0;
}

int facttail(int n, int na)
{
    if (n < 0)
    {
        return -1;
    }
    else if (n == 0)
    {
        return 1;
    }
    else if (n == 1)
    {
        return na;
    }

    return facttail(n - 1, n * na);
}