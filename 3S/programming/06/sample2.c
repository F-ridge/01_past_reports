#include <stdio.h>
#include <stdlib.h>
#define NEW(p,n) {p = malloc((n)*sizeof(p[0])); if ((p)==NULL) {printf("not enough memory\n"); exit(1);};}

typedef struct slobj_ {
  struct slobj_ *next;     // 後の要素へのポインタ
  int key;                 // キー
  double value;            // 付属データ
}* slobj;

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
  slobj* T;
}* hash;

hash hash_new(int u)
{
  hash H;
  int i;
  NEW(H, 1);
  H->u = u;
  NEW(H->T, u);
  for (i=0; i<u; i++) H->T[i] = NULL;
  return H;
}

void hash_insert(hash H, slobj obj)
{
  H->T[obj->key] = obj;
}

slobj hash_search(hash H, int k)
{
  if (k >= H->u || k < 0) return NULL;
  return H->T[k];
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
  H = hash_new(10000);
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
      printf("NO\n");
    }
  }
  hash_free(H);
  return 0;
}