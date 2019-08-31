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
  if ((size > l) && (A[l]->priority > A[largest]->priority)) {largest = l;}
  if ((size > r) && (A[r]->priority > A[largest]->priority)) {largest = r;}
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

heapdata* read_heapdata(int n, int max_size){
  heapdata* A;
  int i;
  int val; double pri;
  NEW(A, max_size + 1);
  for (i = 0; i < n; i++){
    scanf("%d %lf", &val, &pri);
    A[i] = heapdata_new(val, pri);
  }
  return A;
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

void heap_sort(int n, heapdata* A){
  int i;
  heapdata _;
  heap H;
  H = heap_build(n, A, n);
  for (i = 0; i < n; i++){
    _ = heap_extract_max(H);
  }
}

int main(){
  int max_size, n;
  heapdata* A;
  int val; double pri;
  int i;
  scanf("%d", &max_size); scanf("%d", &n);
  A = read_heapdata(n, max_size);
  heap_sort(n, A);
  for (i = 0; i < n; i++){
    val = A[i]->value; pri = A[i]->priority;
    printf("%d %lf\n", val, pri);}
  return 0;
}