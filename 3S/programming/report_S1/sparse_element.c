#include <stdio.h>
#include <stdlib.h>

#define NEW(p,n) {p = malloc((n)*sizeof(p[0])); if ((p)==NULL) {printf("not enough memory\n"); exit(1);};}

typedef struct slobj_ {
  struct slobj_* next;
  int j;
  double v;
}* slobj;

typedef slobj* smatrix_row;

typedef struct {
  slobj head;
  slobj tail;
}* slist;

typedef struct {
  int n, m;
  slist* R;
}* smatrix;

slobj slobj_new(int j_, double v_)
  {
    slobj p;
    NEW(p,1);
    p->j = j_;
    p->v = v_;
    p->next = NULL;
    return p;
}

slist slist_new(void)
  {
    slist L;
    NEW(L,1);
    L->head = NULL;
    L->tail = NULL;
    return L;
}

smatrix smatrix_new(int n, int m)
{
  int i;
  smatrix S;
  NEW(S, 1);
  NEW(S->R, n);
  S->n = n;
  S->m = m;
  for (i=0; i<n; i++) {
    S->R[i] = slist_new();
  }
  return S;
}


void slist_insert_tail(slist L, slobj r)
{
  slobj t;
  if (L->head==NULL) {
    L->head = r;
    L->tail = r;
  }
  t = L->tail;
  t->next = r;
  L->tail = r;
}

smatrix smatrix_read(){
  int n, m, i, j;
  double val;
  smatrix S;
  scanf("%d %d", &n, &m);
  S = smatrix_new(n, m);
  for (i=0; i<n; i++) {
    while(1) {
      scanf("%d", &j);
      if (j == -1) break;
      scanf("%lf", &val);
      slist_insert_tail(S->R[i], slobj_new(j, val));
    }
  }
  return S;
}

smatrix smatrix_transpose(smatrix S){
  int n, m, i, j;
  double val;
  smatrix S_T;
  slist row;
  slobj elem;
  n = S->n;
  m = S->m;
  S_T = smatrix_new(m, n);
  for (i=0; i<n; i++) {
    row = S->R[i];
    elem = row->head;
    while (elem != NULL) {
      j = elem->j;
      val = elem->v;
      slist_insert_tail(S_T->R[j-1], slobj_new(i+1, val));
      elem = elem->next;
    }
  }
  return S_T;
}

void smatrix_print(smatrix S)
{
  int i, n, m;
  slist row;
  slobj elem;
  n = S->n;
  m = S->m;
  printf("%d %d\n", n, m);
  for (i=0; i<n; i++) {
    row = S->R[i];
    elem = row->head;
    while (elem != NULL) {
      printf("%d %lf ", elem->j, elem->v);
      elem = elem->next;
    }
    printf("-1\n");
  }
}

double smatrix_access(smatrix S, int i, int j)
{
slist L;
slobj p;
int k;
L = S->R[i-1];
p = L->head;
if (p == NULL)
{
  return 0;
}
while(1)
{
  if (p->j == j)
  {
      return p->v;
  }
  if (p->next == NULL)
  {
      return 0;
  }
  p = p->next;
}
}

smatrix smatrix_product(smatrix A, smatrix B)
{  smatrix C;
   int n_A, m_A, n_B, m_B;
   int row, col, i;
   double v, a, b;
   slist C_row;
   n_A = A->n; m_A = A->m;
   n_B = B->n; m_B = B->m;
   C = smatrix_new(n_A, m_B);
   for (row = 0; row < n_A; row++) {
     C_row = C->R[row];
     for (col = 0; col < m_B; col++) {
       v = 0;
       for (i = 0; i < m_A; i++) {
         a = smatrix_access(A, row+1, i+1);
         b = smatrix_access(B, i+1, col+1);
         v = v + a * b;
       }
       if (v != 0) {
         slist_insert_tail(C_row, slobj_new(col+1, v));
       }
     }
   }
   return C;
}

int main(void)
{   
  smatrix A, prod;
  A = smatrix_read();
  prod = smatrix_product(A, A);
  smatrix_print(prod);
  return 0;
}
