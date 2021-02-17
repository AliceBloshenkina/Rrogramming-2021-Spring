#include <stdio.h>

unsigned long factorial(int n)
{
    if (n == 0)
        return 1;
    return n * factorial(n - 1);
}

int main ()
{
    unsigned long m;
    int  n;
    scanf("%d", &n);
    if (n < 1 || n > 20 ){
        printf("Error");
    }
    m  = factorial(n);

    printf("Otwet: %lu\n", m);
    return 0;
}
