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

slist slist_join(slist L1, slist L2)
{
  slist L3;
  slobj p1, p2, p3;
  int j1, j2;
  L3 = slist_new();
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
      slist_insert_tail(L3, slobj_new(j1, 0.0));}
      p1 = p1->next; p2 = p2->next;
  } 
  return L3;
}

void slist_print(slist L)
{
    slobj p;
    p = L->head;
    while (p != NULL)
    {
        printf("%d ", p->j);
        p = p->next;
    }
    printf("-1\n");
}

int main(void)
{   
  smatrix A, A_T, prod;
  slist a, b, c;
  double v;
  int nrow, ncol;
  A = smatrix_read();
  nrow = A->n; ncol = A->m;
  A_T = smatrix_transpose(A);
  a = A->R[0]; b = A_T->R[0];
  c = slist_join(a, b);
  slist_print(c);
  // prod = smatrix_product(A, A);
  // smatrix_print(prod);
  return 0;
}