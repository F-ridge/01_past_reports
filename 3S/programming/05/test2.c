int main(void)
{   
  int i, k;
  for (i = 0; k < i; i++)
  {
    for (j = 1; j <= m_A; j++)
    {
      v = smatrix_access(A, i, j);
      printf("(%d, %d): %lf\n", i, j, v);
    }
    
  }
  return 0;
}