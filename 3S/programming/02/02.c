#include <stdio.h>
#include <stdlib.h>

int main()
{
 int i, j, n, m;
  double R[3][2] = {{1,2},
                    {3,4},
                    {5,6}};
  n = 3;  m = 2;
  for (i=0; i<n; i++) {
      for (j=0; j<m; j++) {
        printf("%lf   ", R[i][j]); // i 行 j 列要素
      }
      printf("\n");
   }
   return 0;
}