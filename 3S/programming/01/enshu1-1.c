#include <stdio.h>
#include <stdlib.h>

void read_file()
{
  double x;
  char *filename;
  scanf("%s", &filename);
  FILE *fp; // ファイルの読み書きのための変数
  fp = fopen(filename, "r"); // ファイルを読み込みモードで開く
  if (fp == NULL) { // 開けない場合
    printf("cannot open %s\n", filename);
    exit(1); // プログラム終了
  }
  while (!feof(fp)) { // 括弧内の条件が満たされる間繰り返す
                      //  feof(fp) はファイルの末尾まで読んだときに真になる
                      //  ! は否定を表す．つまりファイルの末尾まで読んでいない間whileループを繰り返す
    if (fscanf(fp, "%lf", &x) < 1) { // 実数が読み込めなければ
      break; // while から抜ける (for文中 でも使える)
    }
    fprintf(stdout, "%lf\n", x); // 標準出力に出力(画面に表示)
  }
  fclose(fp); // ファイルを閉じる
}

int main(int argc, char *argv[])
{
    read_file(argv[1]);
    return 0;
}