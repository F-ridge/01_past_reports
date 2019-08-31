#include <stdio.h>
#include <stdlib.h>
#define NEW(p,n) {p = malloc((n)*sizeof(p[0])); if ((p)==NULL) {printf("not enough memory\n"); exit(1);};}

#define PARENT(i) (i - 1) / 2
#define LEFT(i) 2 * i + 1
#define RIGHT(i) 2 * i + 2

typedef struct {
    int value;
    double priority;                  // 要素を格納する配列
}* heapdata;

typedef struct {
    int max_size;        // 配列 A に格納できる最大要素数
    int size;                 // ヒープに格納されている要素の数
    heapdata* A;                  // 要素を格納する配列
}* heap;

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


void heap_swap(heap H, int i, int j){
  heapdata tmp;
  heapdata* A;
  A = H->A;
  tmp = A[i];
  A[i] = A[j];
  A[j] = tmp;
}

void heap_heapify(heap H, int i){
  int l, r, largest, size;
  heapdata* A;
  A = H->A; size = H->size;
  l = LEFT(i); r = RIGHT(i);
  largest = i;
  if ((size > l) && (A[l]->priority < A[largest]->priority)) {largest = l;}
  if ((size > r) && (A[r]->priority < A[largest]->priority)) {largest = r;}
  if (largest != i) {                                                          
    heap_swap(H, i, largest);  // A[i]を子供と入れ替える
    heap_heapify(H, largest);
  }
}

heapdata heapdata_new(int val, double pri){
  heapdata h;
  NEW(h, 1);
  h->value = val;
  h->priority = pri;
  return h;
}

void heap_insert(heap H, heapdata h){
  int n;
  int i;
  n = H->size;
  H->A[n] = h;
  H->size = n + 1;
  i = n;
  while(1){
    if (i == 0) {break;}
    if (H->A[i]->priority < H->A[PARENT(i)]->priority) {
      heap_swap(H, i, PARENT(i));
      i = PARENT(i);
    } else {break;}
  }
}

heap heap_build(int n, heapdata* A, int max_size){
  int i;
  heap H;
  NEW(H, 1);
  H->max_size = max_size;
  H->size = n;
  H->A = A; // ヒープの構造体に配列 A をそのまま入れる (複製を作らない)
  for (i = (n-1)/2; i >= 0; i--) {
    heap_heapify(H,i);
  }
  return H;
}

/*
heapdata heap_extract_max(heap H){
  heapdata max_data;
  int n;
  heapdata* A;
  n = H->size;
  A = H->A;
  max_data = A[0];
  heap_swap(H, 0, n-1);
  H->size = n - 1;
  heap_heapify(H, 0);
  return max_data;
}
*/

heapdata heap_extract_min(heap H){
  heapdata min_data;
  int n;
  heapdata* A;
  n = H->size;
  A = H->A;
  min_data = A[0];
  heap_swap(H, 0, n-1);
  H->size = n - 1;
  heap_heapify(H, 0);
  return min_data;
}

void dijkstra(graph G, int s, double* dist){
  int n, m;
  int i, v;
  heapdata h, _; heapdata* A; heap H;
  slobj e;
  n = G->n;
  m = G->m;
  for (i = 0; i < n; i++){
    if (i == s) {dist[i] = 0;}
    else {dist[i] = 999999;} // infinity
  }
  NEW(A, n + 1);
  A[0] = heapdata_new(s, 0.0);
  NEW(H, 1);
  H->max_size = m;
  H->size = 1;
  H->A = A;
  while(1){
    if (H->size == 0) {break;}
    h = heap_extract_min(H);
    v = h->value;
    printf("%lf %lf %d\n", dist[v], h->priority, h->value);
    if (dist[v] >= h->priority) {
      dist[v] = h->priority;
      e = graph_firstedge(G, v);
      while(1){
        if (e == NULL) {break;}
        if (dist[e->v - 1] > dist[v] + e->d) {
          dist[e->v - 1] = dist[v] + e->d;
          heap_insert(H, heapdata_new(e->v - 1, dist[e->v - 1]));
        }
        e = graph_nextedge(G, v, e);
      }
    }
  }
}

int main(){
  int i, n;
  graph G;
  double* dist;
  G = graph_read();
  n = G->n;
  NEW(dist, n);
  dijkstra(G, 0, dist);
  for (i = 0; i < n; i++){printf("%d %lf\n", i+1, dist[i]);}
  return 0;
}