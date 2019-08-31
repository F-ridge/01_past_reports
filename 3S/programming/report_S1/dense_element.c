#include<stdio.h>
#include<stdlib.h>

#define NEW(p,n) {p = malloc((n)*sizeof(p[0]));} 

typedef double* row_vector;
typedef row_vector* matrix;

row_vector create_row_vector(int n)
{
    int i;
    row_vector V;
    NEW(V, n);
    for (i=0; i<n; i++) V[i] = 0.0;
    return V;
}

matrix create_matrix(int n, int m)
{
    int i;
    matrix V;
    NEW(V, m);
    for (i=0; i<n; i++) V[i] = (row_vector)create_row_vector(m);
    return V;
}

void print_matrix(int n, int m, matrix A)
{
  int i, j;
  double val;
  printf("%d %d\n", n, m);
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      val = A[i][j];
      if (val != 0.0) {printf("%d %lf ", j+1, val);}
    }
    printf("-1\n");
  }
}

void read_matrix(int n, int m, matrix A)
{
    int i, j;
    double val;
    for (i = 0; i < n; i++) {
    while(1) {
      scanf("%d", &j);
      if (j == -1) break;
      scanf("%lf", &val);
      A[i][j-1] = val;
    }
  }
}

matrix matrix_product(
  int n_A, int m_A, int n_B, int m_B, matrix A, matrix B)
{
  int i, j, k;
  double val;
  matrix S;
  S = create_matrix(n_A, m_B);
  for (i = 0; i < n_A; i++) {
    for (j = 0; j < m_B; j++) {
      for (k = 0; k < m_A; k++) {S[i][j] += A[i][k] * B[k][j];}
    }
  }
  return S;
}

int main()
{
    int n, m;
    matrix A, B;
    scanf("%d %d", &n, &m);
    A = create_matrix(n, m);
    read_matrix(n, m, A);
    B = matrix_product(n, m, n, m, A, A);
    print_matrix(n, m, B);
    return 0;
}