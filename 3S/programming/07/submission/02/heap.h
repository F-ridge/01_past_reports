#ifndef HEAP_H
#define HEAP_H

typedef struct {
    int max_size;        // 配列 A に格納できる最大要素数
    int size;                 // ヒープに格納されている要素の数
    int* A;                  // 要素を格納する配列
}* heap;

void heap_swap(heap H, int i, int j);
void heap_heapify(heap H, int i);
heap heap_build(int n, int* A, int max_size);
int heap_extract_max(heap H);
// void heap_free(heap H);
void heap_sort(int n, int* A);

#endif