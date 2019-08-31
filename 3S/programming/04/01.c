#include <stdio.h>
#include <stdlib.h>

#define NEW(p,n) {p = malloc((n)*sizeof(p[0])); if ((p)==NULL) {printf("not enough memory\n"); exit(1);};}

typedef struct slobj_ {
  int v;                    // 値
  struct slobj_* next;      // 後の要素へのポインタ
}* slobj;

typedef struct {
  slobj head;               // 先頭要素のポインタ
}* slist;

slobj slobj_new(int x)
{
  slobj p;
  NEW(p,1);
  p->v = x;
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

slobj slist_search(slist L, int x)
{
  slobj p;
  p = L->head;
  while (p != NULL && p->v != x) {
    p = p->next;
  }
  return p;
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

void slist_insert_head(slist L, slobj p)
{
  p->next = L->head;
  L->head = p;
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

void slist_print(slist L)
{
  slobj p;
  p = L->head;
  while (p != NULL) {
    printf("%d ", p->v);
    p = p->next;
  }
  printf("-1\n");
}

void slist_print_(slist L, int i)
{
  int k;
  for (k=0; k<i; k++) {
    printf("%lf ", L[i]);
  }
  printf("-1\n");
}

int main(void)
{
  slist L;
  int x, i;

  L = slist_new();
  i = 0;
  while (1) {
    scanf("%d", &x);
    if (x < 0) break;
    i = i + 1;
    slist_insert_tail(L, slobj_new(x));
  }

  slist_print(L);
  slist_print_(&L, i);
  slist_free(L);
  return 0;
}