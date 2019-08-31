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

double slist_join_product(slist L1, slist L2)
{
  double res;
  slobj p1, p2, p3;
  int j1, j2;
  res = 0.0;
  p1 = L1->head;
  p2 = L2->head;
  while ((p1 != NULL) && (p2 != NULL)){
    j1 = p1->j;
    j2 = p2->j;
    if (j1 < j2){
      p1 = p1->next;
    } else if (j1 > j2){
      p2 = p2->next;
    } else {
      res += p1->v * p2->v;
      p1 = p1->next; p2 = p2->next;
    }
  } 
  return res;
}

smatrix smatrix_product(smatrix A, smatrix B)
{  smatrix B_T, C;
   int n_A, m_A, n_B, m_B;
   int row, col, count;
   double v;
   slist A_row, C_row;
   n_A = A->n; m_A = A->m;
   n_B = B->n; m_B = B->m;
   B_T = smatrix_transpose(B);
   C = smatrix_new(n_A, m_B);
   count = 0;
   for (row = 0; row < n_A; row++) {
    A_row = A->R[row];
    C_row = C->R[row];
     for (col = 0; col < m_B; col++) {
       v = slist_join_product(A_row, B_T->R[col]);
       if (v != 0.0) {
         count++;
         slist_insert_tail(C_row, slobj_new(col+1, v));
       }
     }
   }
   printf("non-zero product num is %d\n", count);
   return C;
   
}

void smatrix_elem_count(smatrix S)
{
  int i, n, m, count;
  slist row;
  slobj elem;
  n = S->n;
  m = S->m;
  count = 0;
  for (i=0; i<n; i++) {
    row = S->R[i];
    elem = row->head;
    while (elem != NULL) {
      count++;
      elem = elem->next;
    }
  }
  printf("%d\n", count);
}

int main(void)
{   
  smatrix A, prod;
  A = smatrix_read();
  prod = smatrix_product(A, A);
  printf("The number of non-zero elements in the original matrix is ");
  smatrix_elem_count(A);
  printf("The number of non-zero elements in the squared matrix is ");
  smatrix_elem_count(prod);
  return 0;
}