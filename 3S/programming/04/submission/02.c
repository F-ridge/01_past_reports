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
}* slist;

typedef struct {
  int n, m;
  slist* A;
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
    return L;
}

smatrix smatrix_new(int n, int m)
{
  int i;
  smatrix S;
  NEW(S, 1);
  NEW(S->A, n);
  S->n = n;
  S->m = m;
  for (i=0; i<n; i++) {
    S->A[i] = slist_new();
  }
  return S;
}

void slist_insert(slist L, slobj r)
{
  slobj p, q;
  p = L->head;
  q = p;
  while (p != NULL && p->v <= r->v) {
    q = p;
    p = p->next;
  }
  if (p == L->head) {
    L->head = r;
    r->next = p;
  } else {
    q->next = r;
    r->next = p;
  }
}

void slist_insert_tail(slist L, slobj r)
{
  slobj p, q;
  p = L->head;
  q = p;
  if(p == NULL){
    L->head = r;
  } else {
  while (p != NULL) {
    q = p;
    p = p->next;
  }
  q->next = r;
  }
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
      slist_insert_tail(S->A[i], slobj_new(j, val));
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
    row = S->A[i];
    elem = row->head;
    while (elem != NULL) {
      j = elem->j;
      val = elem->v;
      slist_insert_tail(S_T->A[j-1], slobj_new(i+1, val));
      elem = elem->next;
    }
  }
  return S_T;
}

void slist_free(slist L)
{
  slobj p, q;
  p = L->head;
  while (p != NULL) {
    q = p->next;
    free(p);
    p = q;
  }
  free(L);
}

void slist_print(slist L)
{
  slobj p;
  p = L->head;
  while (p != NULL) {
    printf("%lf ", p->v);
    p = p->next;
  }
  printf("-1\n");
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
    row = S->A[i];
    elem = row->head;
    while (elem != NULL) {
      printf("%d %lf ", elem->j, elem->v);
      elem = elem->next;
    }
    printf("-1\n");
  }
}


int main(void)
{   
  smatrix S, S_T;
  S = smatrix_read();
  S_T = smatrix_transpose(S);
  smatrix_print(S_T);
  return 0;
}
