#include <stdio.h>
#include <stdlib.h>

int main(){
  int* A;
  A[0] = 0;
  A[1] = 1;
  A[2] = 2;
  free(A[1]);
  printf("%d", A[2]);
  return 0;
}