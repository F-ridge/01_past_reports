#include <stdio.h>
#include <stdlib.h>
#define NEW(p,n) {p = malloc((n)*sizeof(p[0])); if ((p)==NULL) {printf("not enough memory\n"); exit(1);};}

#define PARENT(i) (i - 1) / 2
#define LEFT(i) 2 * i + 1
#define RIGHT(i) 2 * i + 2

typedef char* String;

typedef struct {
    int value;
    int priority;                  // 要素を格納する配列
}* heapdata;

typedef struct {
    int max_size;        // 配列 A に格納できる最大要素数
    int size;                 // ヒープに格納されている要素の数
    heapdata* A;                  // 要素を格納する配列
}* heap;

typedef struct slobj_ {
    struct slobj_ *next;
    int v;
    char d;
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


int string_len(String str)
{
  int len=0;
  while (str[len] != 0) {
    len++;
  }
  return len;
}

String string_input(void)
{
  int i, len;
  char buf[1000000];
  String str;
  scanf("%s", buf);

  len = string_len(buf);
  
  NEW(str, len+1);
  for (i=0; i<len; i++) {
    str[i] = buf[i];
  }
  str[len] = 0;
  return str;
}


slobj slobj_new(int v_, char d_)
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

/*
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
*/

graph graph_read(String A, String B, int len_A, int len_B){
  int i, j, n, m;
  int k, k_n;
  n = (len_A+1) * (len_B+1); // nodes
  m = (len_A+1) * (len_B+1) * 3 - ((len_A+1) + (len_B+1)) * 2 + 1; //edges
  graph G;
  G = graph_new(n, m);
  for (i = 0; i < len_A; i++) {
    for (j = 0; j < len_B; j++) {
      k = i*(len_B+1)+j; // current node
      k_n = k+(len_B+1)+1;  // naname node
      slist_insert_tail(G->E[k], slobj_new(k+1, 1)); // yoko
      slist_insert_tail(G->E[k], slobj_new(k+(len_B+1), 1)); // tate
      if (A[i] == B[j])
        {slist_insert_tail(G->E[k], slobj_new(k_n, 0));}
      else
        {slist_insert_tail(G->E[k], slobj_new(k_n, 1));} // naname
    }
  }
  for (i = 0; i < len_A; i++) {
    k = i*(len_B+1)+len_B; // current node
    slist_insert_tail(G->E[k], slobj_new(k+(len_B+1), 1)); // tate
  }
  for (j = 0; j < len_B; j++) {
    k = len_A*(len_B+1)+j; // current node
    slist_insert_tail(G->E[k], slobj_new(k+1, 2)); // yoko
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

heapdata heapdata_new(int val, int pri){
  heapdata h;
  NEW(h, 1);
  h->value = val;
  h->priority = pri;
  return h;
}

void heap_insert(heap H, heapdata h){
  int n;
  int i;
  heapdata* A;
  double pri, pri_parent;
  n = H->size;
  A = H->A;
  A[n] = h;
  H->size = n + 1;
  i = n;
  while(1){
    if (i == 0) {break;}
    pri = A[i]->priority;
    pri_parent = A[PARENT(i)]->priority;
    if (pri < pri_parent) {
      heapdata* A;
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

void dijkstra(graph G, int s, int* dist){
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
  NEW(A, m);
  A[0] = heapdata_new(s, 0);
  NEW(H, 1);
  H->max_size = m;
  H->size = 1;
  H->A = A;
  //int c = 0;
  while(H->size >= 0){
   // if (H->size == 0) {break;}
    h = heap_extract_min(H);
    v = h->value;
    //c++; printf("%d, %d\n", c, v);
    if (dist[v] >= h->priority) {
      dist[v] = h->priority;
      e = graph_firstedge(G, v);
      while(e != NULL){
        // if (e == NULL) {break;}
        if (dist[e->v] > dist[v] + e->d) {
          dist[e->v] = dist[v] + e->d;
          heap_insert(H, heapdata_new(e->v, dist[e->v]));
        }
        e = graph_nextedge(G, v, e);
      }
    }
  }
}

/* 
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
        printf("%d %d ", elem->v, elem->d);
        break;
        }
      printf("%d %d ", elem->v, elem->d);
      elem = elem->next;
    }
    printf("-1\n");
  }
}
*/


int main(){
  int len_A, len_B, ans;
  String A, B;
  A = string_input(); B = string_input();
  len_A = string_len(A); len_B = string_len(B);
  int i, n;
  graph G;
  int* dist;
  G = graph_read(A, B, len_A, len_B);
  //graph_print(G);
  n = G->n;
  NEW(dist, n);
  dijkstra(G, 0, dist);
  printf("%d\n", dist[n-1]);
  return 0;
}
