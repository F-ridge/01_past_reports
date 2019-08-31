for (i = 1; i <= n_A; i++)
  {
    for (j = 1; j <= m_A; j++)
    {
      v = smatrix_access(A, i, j);
      printf("(%d, %d): %lf\n", i, j, v);
    }
    
  }