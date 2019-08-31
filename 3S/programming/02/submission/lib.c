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

void read_matrix(int n, int m, matrix A)
{
    int i, j;
    double v;
    for (i=0; i<n; i++) {
        for (j=0; j<m; j++) {
            scanf("%lf", &v);
            A[i][j] = v;
        }
    }
    
}

int main()
{
    int n, m;
    matrix A;
    scanf("%d %d", &n, &m);
    A = create_matrix(n, m);
    read_matrix(n, m, A);
    print_matrix_T(n, m, A);
    return 0;
}