#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

#define NEW(p,n) {p = malloc((n)*sizeof(p[0])); if ((p)==NULL) {printf("not enough memory\n"); exit(1);};}

#define PARENT(i) (i - 1) / 2
#define LEFT(i) 2 * i + 1
#define RIGHT(i) 2 * i + 2


void heap_swap(heap H, int i, int j){
  int tmp;
  int* A;
  A = H->A;
  tmp = A[i];
  A[i] = A[j];
  A[j] = tmp;
}

void heap_heapify(heap H, int i){
  int l, r, largest, size;
  int* A;
  A = H->A;  size = H->size;
  l = LEFT(i);   r = RIGHT(i);
  largest = i;
  if ((size > l) && (A[l] > A[largest])) {largest = l;}
  if ((size > r) && (A[r] > A[largest])) {largest = r;}
  if (largest != i) {                                                          
    heap_swap(H, i, largest);  // A[i]を子供と入れ替える
    heap_heapify(H, largest);
  }
}

heap heap_build(int n, int* A, int max_size){
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

int heap_extract_max(heap H){
  int max_val, n;
  int* A;
  n = H->size;
  A = H->A;
  max_val = A[0];
  heap_swap(H, 0, n-1);
  H->size = n - 1;
  heap_heapify(H, 0);
  return max_val;
}

// void heap_free(heap H){}

void heap_sort(int n, int* A){
  int i, _;
  heap H;
  H = heap_build(n, A, n);
  for (i = 0; i < n; i++){
    _ = heap_extract_max(H);
  }
}