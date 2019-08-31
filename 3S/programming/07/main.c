#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

int main(){
  int n, i, val;
  int* A;
  scanf("%d", &n);
  for (i = 0; i < n; i++){scanf("%d", &val); A[i] = val;}
  heap_sort(n, A);
  for (i = 0; i < n; i++){val = A[i]; printf("%d\n", val);}
  return 0;
}