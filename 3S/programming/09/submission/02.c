#include <stdio.h>
#include <stdlib.h>
#define NEW(p,n) {p = malloc((n)*sizeof(p[0])); if ((p)==NULL) {printf("not enough memory\n"); exit(1);};}

typedef struct slobj_ {
    struct slobj_ *next;
    int v;
    double d;
}* slobj;

// typedef slobj edge;

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
  slobj fe;
  fe = G->E[i]->head;
  return fe;
}

slobj graph_nextedge(graph G, int i, slobj e){
  slobj ne, tail;
  tail = G->E[i]->tail;
  if (e == tail) {ne = NULL;}
  else {ne = e->next;}
  return ne;
}

void DFS_visit(
    graph G, int i,
    int* time, int* pi, int* d, int* f, int* color){
  int j;
  slobj adj;
  color[i] = 1;
  time[0]++;
  d[i] = time[0];
  adj = graph_firstedge(G, i);
    while (adj != NULL) {
      j = adj->v - 1;
      if (color[j] == 0) {
        pi[j] = i+1; DFS_visit(G, j, time, pi, d, f, color);
      }
      adj = graph_nextedge(G, i, adj);
    }
  color[i] = 2;
  time[0]++;
  f[i] = time[0];
}

void DFS(graph G, int* pi, int* d, int* f){
  int i, n;
  int* time; int* color;
  n = G->n;
  NEW(time, 1); NEW(color, n);
  for (i = 0; i < n; i++) {color[i] = 0;}
  time[0] = 0;
  for (i = 0; i < n; i++) {
    if (color[i] == 0) {DFS_visit(G, i, time, pi, d, f, color);}
  }
}

void DFS_order(
    graph G, int* pi, int* d, int* f, int* order){
  int i, u, n;
  int* time; int* color;
  n = G->n;
  NEW(time, 1); NEW(color, n);
  for (i = 0; i < n; i++) {color[i] = 0;}
  time[0] = 0;
  for (i = 0; i < n; i++) {
    u = order[i];
    if (color[u] == 0) {DFS_visit(G, u, time, pi, d, f, color);}
  }
}

int* make_order(int* f, int n){
  int i, k;
  int* order_tmp; int* order;
  NEW(order_tmp, 2*n+1); NEW(order, n);
  for (i=0; i<2*n; i++) order_tmp[i] = -1;
  for (i=0; i<n; i++) order_tmp[f[i]-1] = i;
  k = 0;
  for (i=2*n-1; i>=0; i--) {
    if (order_tmp[i] != -1) {
      order[k] = order_tmp[i];
      k++;
    }
  }
  return order;
}

void graph_SCC(graph G, int* P){
  int* d; int* f; int* order;
  int i, n;
  graph G_T;
  n = G->n;
  NEW(d, n); NEW(f, n);
  for (i = 0; i < n; i++) {d[i] = 0; f[i] = 0;}
  DFS(G, P, d, f);
  G_T = graph_transpose(G);
  order = make_order(f, n);
  for (i = 0; i < n; i++) {
    P[i] = -1; d[i] = 0; f[i] = 0;
  }
  DFS_order(G_T, P, d, f, order);
}

int main(void)
{   
  graph G;
  int* P;
  int i, n;
  G = graph_read(); n = G->n;
  NEW(P, n);
  for (i = 0; i < n; i++) {P[i] = -1;}
  graph_SCC(G, P);
  for (i = 0; i < n; i++) {
    printf("%d ", P[i]);
  }
  return 0;
}