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
  NEW(p,1); // 構造体の要素のメモリを確保する
  p->v = x; // 構造体へ x を格納する
  p->next = NULL; // 必ず初期化しておく
  return p;
}

slist slist_new(void)
{
  slist L;
  NEW(L,1);
  L->head = NULL; // head が NULL のときは空のリストを表す
  return L;
}

slobj slist_search(slist L, int x)
{
  slobj p;
  p = L->head; // p はリストの先頭要素を指す
  while (p != NULL && p->v != x) { // リストが空でなく，リストの要素に格納されている値が x ではない間
    p = p->next; // リストの次の要素に移動する
  }
  return p;
}

void slist_insert_head(slist L, slobj p) // リストの先頭に要素を追加する
{
  p->next = L->head;
  L->head = p;
}

void slist_print_rev(slist L) // リストを逆順に表示
{
    slobj p;
    p = L->head;
    while (p != NULL)
    {
        printf("%d ", p->v);
        p = p->next;
    }
    
    printf("-1\n");
}

slist slist_join(slist L1, slist L2)
{
  slist L3;
  slobj p1, p2, p3;
  int v1, v2;
  L3 = slist_new();
  p1 = L1->head;
  p2 = L2->head;
  while (p1 != NULL && p2 != NULL){
    v1 = p1->v;
    v2 = p2->v;
    if (v1 > v2){
      p1 = p1->next;
    } else if (v1 < v2){
      p2 = p2->next;
    } else {
      slist_insert_head(L3, slobj_new(v1));
      p1 = p1->next;
      p2 = p2->next;
    }
  }
  return L3;
}

int main(int argc, char *argv[])
{
  slist L1, L2, L3;
  int x;
  L1 = slist_new();
  L2 = slist_new();
  L3 = slist_new();
  while (1)
  {
    scanf("%d", &x);
    if (x < 0 ) break;
    slist_insert_head(L1, slobj_new(x));
  }
  while (1)
  {
    scanf("%d", &x);
    if (x < 0 ) break;
    slist_insert_head(L2, slobj_new(x));
  }
  L3 = slist_join(L1, L2);
  slist_print_rev(L3);
  return 0;
}