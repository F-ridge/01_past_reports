/* test42.c */

#include<stdio.h>

int main()
{
    int i, n, x;
    n = 10;
    x = 0;
    i = 1;
    while(1){
        if(i>n){
            break;
        }
        x += i;
        i++;
    }
    printf("x = %d\n", x);
    return 0;
}
