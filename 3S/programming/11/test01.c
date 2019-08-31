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
    for (i=0; i<n; i++) V[i] = -1;
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

int string_len(String str)
{
  int len=0;
  while (str[len] != 0) {
    len++;
  }
  return len;
}

int string_compare(String p, String q)
{
  int c1, c2;
  int i = 0;
  while (1) {
    c1 = p[i];  c2 = q[i];
    if (c1 < c2) return -1;
    if (c1 > c2) return  1;
    if (c1 == 0) break;
    i++;
  }
  return 0;
}

String string_input(void)
{
  int i, len;
  char buf[1000];
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

String string_head_delete(String A)
{
  String res;
  int i, l;
  l = string_len(A);
  NEW(res, l);
  for (i = 1; i < l; i++) {res[i - 1] = A[i];}
  res[l - 1] = 0;
  return res;
}

int leibenstein_dist(String A, String B, matrix cache)
{
  int ld, l1, l2, l3, n_A, n_B;
  String A_hd, B_hd;
  n_A = string_len(A); n_B = string_len(B);
  A_hd = string_head_delete(A); B_hd = string_head_delete(B);
  if (n_A == 0) {return n_B;}
  else if (n_B == 0) {return n_A;}
  else if (A[0] == B[0]) {
    if (cache[n_A - 1][n_B - 1] == -1) {
      cache[n_A - 1][n_B - 1] = leibenstein_dist(A_hd, B_hd, cache);}
    return cache[n_A - 1][n_B - 1];
  }
  else {
    if (cache[n_A][n_B - 1] == -1) {
      cache[n_A][n_B - 1] = leibenstein_dist(A, B_hd, cache);}
    l1 = cache[n_A][n_B - 1];
    if (cache[n_A - 1][n_B] == -1) {
      cache[n_A - 1][n_B] = leibenstein_dist(A_hd, B, cache);}
    l2 = cache[n_A - 1][n_B];
    if (cache[n_A - 1][n_B - 1] == -1) {
      cache[n_A - 1][n_B - 1] = leibenstein_dist(A_hd, B_hd, cache);}
    l3 = cache[n_A - 1][n_B - 1];
  ld = l1;
  if (ld > l2) {ld = l2;}
  if (ld > l3) {ld = l3;}
  return 1 + ld;
  }
}

int main(void)
{
  int ans;
  String A, B;
  int i, n_A, n_B;
  matrix cache;
  A = string_input(); B = string_input();
  n_A = string_len(A); n_B = string_len(B);
  cache = create_matrix(n_A + 1, n_B + 1);
  ans = leibenstein_dist(A, B, cache);
  printf("%d", ans);
  return 0;
}