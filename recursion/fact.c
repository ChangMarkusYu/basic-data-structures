#include <stdio.h>
#include "./include/fact.h"

/* A naive program for computing n's factorial */

int main()
{
    int n = 0;

    printf("Enter an integer: \n");
    scanf("%d", &n);

    int ans = fact(n);
    printf("%d's factorial = %d\n", n, ans);
    return 0;
}

int fact(int n)
{
    if (n == 0 || n == 1)
    {
        return 1;
    }
    else if (n < 0)
    {
        return -1;
    }

    return n * fact(n - 1);
}