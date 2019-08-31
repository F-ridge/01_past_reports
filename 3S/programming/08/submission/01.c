#include <stdio.h>
#include <stdlib.h>
#define NEW(p,n) {p = malloc((n)*sizeof(p[0])); if ((p)==NULL) {printf("not enough memory\n"); exit(1);};}

typedef struct slobj_ {
    struct slobj_ *next;
    int v;
    double d;
}* slobj;

typedef slobj edge;

typedef struct {
  slobj head;
  slobj tail;
}* slist;

typedef struct {
  int n; // 節点数
  int m; // 枝数
  slist* E; // 枝リストの配列
}* graph;


slobj slobj_new(int v_, double d_)
  {
    slobj p;
    NEW(p,1);
    p->v = v_;
    p->d = d_;
    p->next = NULL;
    return p;
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

slist slist_new(void)
  {
    slist L;
    NEW(L,1);
    L->head = NULL;
    L->tail = NULL;
    return L;
}

graph graph_new(int n, int m){
  int i;
  graph G;
  NEW(G, 1);
  NEW(G->E, n);
  G->n = n;
  G->m = m;
  for (i=0; i<n; i++) {
    G->E[i] = slist_new();
  }
  return G;
}

graph graph_read(void){
  int n, m, i, j;
  double val;
  graph G;
  scanf("%d %d", &n, &m);
  G = graph_new(n, m);
  for (i=0; i<n; i++) {
    while(1) {
      scanf("%d", &j);
      if (j == -1) break;
      scanf("%lf", &val);
      slist_insert_tail(G->E[i], slobj_new(j, val));
    }
  }
  return G;
}

graph graph_transpose(graph G){
  int n, m, i, j;
  double val;
  graph G_T;
  slist row;
  slobj elem;
  n = G->n;
  m = G->m;
  G_T = graph_new(n, m);
  for (i=0; i<n; i++) {
    row = G->E[i];
    elem = row->head;
    while (elem != NULL) {
      j = elem->v;
      val = elem->d;
      if (elem->v == row->tail->v) {
        slist_insert_tail(G_T->E[j-1], slobj_new(i+1, val));
        break;}
      slist_insert_tail(G_T->E[j-1], slobj_new(i+1, val));
      elem = elem->next;
      
    }
  }
  return G_T;
}

void graph_print(graph G){
  int i, n, m;
  slist row;
  slobj elem;
  n = G->n;
  m = G->m;
  printf("%d %d\n", n, m);
  for (i=0; i<n; i++) {
    row = G->E[i];
    elem = row->head;
    while (elem != NULL) {
      if (elem->v == row->tail->v) {
        printf("%d %lf ", elem->v, elem->d);
        break;
        }
      printf("%d %lf ", elem->v, elem->d);
      elem = elem->next;
    }
    printf("-1\n");
  }
}

slobj graph_firstedge(graph G, int i){
}

slobj graph_nextedge(graph G, int i, edge e){

}

int main(void)
{   
  graph G, G_T;
  G = graph_read();
  G_T = graph_transpose(G);
  graph_print(G_T);
  return 0;
}