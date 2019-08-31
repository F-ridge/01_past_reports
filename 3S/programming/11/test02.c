#include <stdio.h>
#include <stdlib.h>

#define NEW(p,n) {p = malloc((n)*sizeof(p[0])); if ((p)==NULL) {printf("not enough memory\n"); exit(1);};}


typedef int* row_vector;
typedef row_vector* matrix;

row_vector create_row_vector(int n)
{
    int i;
    row_vector V;
    NEW(V, n);
    for (i=0; i<n; i++) V[i] = -1;
    return V;
}

matrix create_matrix(int n, int m)
{
    int i;
    matrix V;
    NEW(V, n);
    for (i=0; i<n; i++) V[i] = (row_vector)create_row_vector(m);
    return V;
}

int main()
{
  int n, b, i, d, v;
  int* weight; int* value;
  matrix dp;
  scanf("%d %d", &n, &b);
  NEW(weight, n); NEW(value, n);
  for (i = 0; i < n; i++) {scanf("%d ", &weight[i]);}
  for (i = 0; i < n; i++) {scanf("%d ", &value[i]);}
  dp = create_matrix(n+1, b+1);
  for (i = 0; i <= b; i++) {dp[0][i] = 0;}
  
  for (i = 0; i < n; i++)
  {
    for (d = 0; d <= b; d++)
    {
      if (weight[i] <= d)
      {
        v = dp[i][d-weight[i]] + value[i];
        if (v < dp[i][d]){v = dp[i][d];}
        dp[i+1][d] = v;
      } else {
        dp[i+1][d] = dp[i][d];
      }
    }
  }
  printf("%d", dp[n][b]);
  return 0;
}