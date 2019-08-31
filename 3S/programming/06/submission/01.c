#include <stdio.h>
#include <stdlib.h>

#define NEW(p,n) {p = malloc((n)*sizeof(p[0])); if ((p)==NULL) {printf("not enough memory\n"); exit(1);};}

typedef struct slobj_ {
  struct slobj_* next;
  int j;
  double v;
}* slobj;

typedef struct {
  slobj head;
  slobj tail;
}* slist;

typedef struct{
    int n;
    int m;
    slist* T;
}* hash;

hash hash_new(int m){
    hash H;
    NEW(H, 1)
}

slobj hash_search(hash H, slobj obj){
    
}

void hash_insert(hash H, slobj obj){

}

