#include <stdio.h>
#include <stdlib.h>

#define NEW(p,n) {p = malloc((n)*sizeof(p[0])); if ((p)==NULL) {printf("not enough memory\n"); exit(1);};}


int bsearch_mist(int n, int* S, int k)
{
int high, low, mid;
  low = 0;                // 探索の範囲は最初は配列全体 [0..n-1]
  high = n-1;
  if (S[0] >= k) {return 0;}
  while (low <= high) {
      if (low == high){return low;}
      mid = (low + high) / 2;
      if (S[mid] == k) { // 見つかった
          return mid;
      } else if (S[mid] < k) {
          low = mid + 1; // 探索範囲を後半だけにする
      } else {
          high = mid - 1; // 探索範囲を前半だけにする
      }
  }
  return -1; // 見つからなかった
}

int main(void){
  int i, n, k, mid, res;
  int* S;
  scanf("%d", &n);
  NEW(S, n);
  for (i = 0; i < n; i++) {scanf("%d", &S[i]);}
  scanf("%d", &k);
  mid = bsearch_mist(n, S, k);
  //printf("%d\n", mid);
  if (mid == -1){printf("%d", n); return 0;}
  res = mid;
  while(1) {
    if (S[res] < k){res++; break;}
    if (res == 0){break;}
    res--;
  }
  printf("%d", res);
  return 0;
}