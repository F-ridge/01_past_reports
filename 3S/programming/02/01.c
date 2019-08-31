#include<stdio.h>
#include<stdlib.h>

#define NEW(p,n) {p = malloc((n)*sizeof(p[0]));} 

typedef double* row_vector;

row_vector create_row_vector(int n)
{
  int i;
  row_vector V;
  NEW(V, n);
  for (i=0; i<n; i++) V[i] = 0.0;
  return V;
}


int main()
{
  row_vector A;
  int i, n;
  scanf("%d", &n);
  
  A = create_row_vector(n);
  
  for (i=0; i<n; i++) A[i] = (double)i;
    printf("%lf\n", A[i]);
  free(A); // 使わなくなった領域を開放する
  return 0;
}