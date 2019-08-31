/* test5.c */

#include<stdio.h>

int main()
{
    int i, n, x;
    scanf("%d", &n);
    x = 0;
    for(i=1; i<=n; i++){
        x += i;
    }
    printf("x = %d\n", x);
    return 0;
}
