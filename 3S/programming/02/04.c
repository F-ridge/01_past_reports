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
    //for (i=0; i<n; i++) V[i] = (double)i;
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
    printf("%d %d \n", n, m);
    for (i=0; i<n; i++) {
        for (j=0; j<m; j++) {
            printf("%lf ", A[i][j]);
        }
        printf("\n");
    }
}

void print_matrix_T(int n, int m, matrix A)
{
    int i, j;
    printf("%d %d \n", m, n);
    for (j=0; j<m; j++) {
        for (i=0; i<n; i++) {
            printf("%lf ", A[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int n, m;
    n = 3; m = 4;
    matrix A = create_matrix(n, m);
    print_matrix(n, m, A);
    return 0;
}