#include <stdio.h>
#include <stdlib.h>

#define NEW(p,n) {p = malloc((n)*sizeof(p[0])); if ((p)==NULL) {printf("not enough memory\n"); exit(1);};}

typedef char* String;
typedef int* row_vector;
typedef row_vector* matrix;

row_vector create_row_vector(int n)
{
    int i;
    row_vector V;
    NEW(V, n);
    for (i=0; i<n; i++) V[i] = 0;
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

int string_len(String str)
{
  int len=0;
  while (str[len] != 0) {
    len++;
  }
  return len;
}

String string_input(void)
{
  int i, len;
  char buf[1000000];
  String str;
  scanf("%s", buf);

  len = string_len(buf);
  
  NEW(str, len+1);
  for (i=0; i<len; i++) {
    str[i] = buf[i];
  }
  str[len] = 0;
  return str;
}

int leibenstein_dist(String A, String B)
{
  int n_A, n_B;
  matrix cost;
  int i, j; int l1, l2, l3, l;
  n_A = string_len(A); n_B = string_len(B);
  cost = create_matrix(n_A+1, n_B+1);
  for (i = 0; i <= n_A; i++) {cost[i][0] = i;}
  for (j = 0; j <= n_B; j++) {cost[0][j] = j;}
  for (i = 1; i <= n_A; i++) {
    for (j = 1; j <= n_B; j++) {
      if (A[i-1] == B[j-1]) {l1 = cost[i-1][j-1];}
      else {l1 = cost[i-1][j-1] + 1;} // ななめ移動
      l2 = cost[i-1][j] + 1; 
      l3 = cost[i][j-1] + 1;
      l = l1;
      if (l > l2) {l = l2;}
      if (l > l3) {l = l3;}
      cost[i][j] = l;
    }
  }
  return cost[n_A][n_B];
}

int main(void)
{
  int ans;
  String A, B;
  A = string_input(); B = string_input();
  ans = leibenstein_dist(A, B);
  printf("%d\n", ans);
  return 0;
}
