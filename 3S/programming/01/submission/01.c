/* assignment01.c */

#include<stdio.h>
#include<math.h>

int main()
{
    int i, n, x;
    scanf("%d", &n);
    if(n<1){
        printf("0");
    return 0;
    }
    x = 0;
    for(i=1; i<=n; i++){
        x += i * i;
    }
    printf("%d", x);
    return 0;
}
