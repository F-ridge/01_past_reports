#include <stdio.h>
#include <stdlib.h>
#define NEW(p,n) {p = malloc((n)*sizeof(p[0])); if ((p)==NULL) {printf("not enough memory\n"); exit(1);};}

typedef struct slobj_ {
  struct slobj_ *next;     // 後の要素へのポインタ
  int key;                 // キー
  double value;            // 付属データ
}* slobj;

typedef struct {
  slobj head;
}* slist;

slobj slobj_new(int key, double value)
{
  slobj p;
  NEW(p,1);
  p->key = key;
  p->value = value;
  p->next = NULL;
  return p;
}

typedef struct {
  int u;
  slist* T;
}* hash;

void slist_insert(slist L, slobj p) // リストの先頭に要素を追加する
{
  p->next = L->head;
  L->head = p;
}

slist slist_new(void)
  {
    slist L;
    NEW(L,1);
    L->head = NULL;
    return L;
}

hash hash_new(int u)
{
  hash H;
  int i;
  NEW(H, 1);
  H->u = u;
  NEW(H->T, u);
  for (i=0; i<u; i++) H->T[i] = slist_new();
  return H;
}

void slist_print(slist L)
{
  slobj p;
  p = L->head;
  printf("---\n");
  while (p != NULL) {
    printf("(%d, %lf) ", p->key, p->value);
    p = p->next;
  }
  printf("\n---\n");
}


void hash_insert(hash H, slobj obj)
{
  //printf("insert (%d, %lf), index: %d\n",
  //  obj->key, obj->value, obj->key % H->u);
  slist_insert(H->T[obj->key % H->u], obj);
}

slobj slist_search(slist L, int x)
{
  slobj p;
  p = L->head;
  while (p != NULL && p->key != x) {
    p = p->next;
  }
  return p;
}

slobj hash_search(hash H, int k)
{
  //printf("search for key %d, index: %d\n", k, k % H->u);
  //slist_print(H->T[k % H->u]);
  return slist_search(H->T[k % H->u], k);
}

void hash_free(hash H)
{
  int i;
  for (i=0; i<H->u; i++) {
    if (H->T[i] != NULL) {
      free(H->T[i]);
    }
  }
  free(H->T);
  free(H);
}

int main()
{
  hash H;
  slobj obj;
  int n, i, k, q;
  double v;
  H = hash_new(1000);
  scanf(" %d", &n);
  for (i=0; i<n; i++) {
  	scanf(" %d %lf", &k, &v);
  	hash_insert(H, slobj_new(k, v));
  }
  scanf(" %d", &q);
  for (i=0; i<q; i++) {
    scanf(" %d", &k);
    obj = hash_search(H, k);
    if (obj != NULL) {
      printf("%d %lf\n", obj->key, obj->value);
    } else {
      printf("-1\n");
    }
  }
  //hash_free(H);
  return 0;
}