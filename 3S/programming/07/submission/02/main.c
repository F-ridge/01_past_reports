#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

#define NEW(p,n) {p = malloc((n)*sizeof(p[0])); if ((p)==NULL) {printf("not enough memory\n"); exit(1);};}

int main(){
  int n, i, val;
  int* A;
  scanf("%d", &n);
  NEW(A, n);
  for (i = 0; i < n; i++){scanf("%d", &val); A[i] = val;}
  heap_sort(n, A);
  for (i = n - 1; i >= 0; i--){val = A[i]; printf("%d\n", val);}
  return 0;
}