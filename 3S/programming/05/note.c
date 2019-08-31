#include<stdio.h>
#include<stdlib.h>

#define NEW(p,n){p=malloc((n)*sizeof(p[0])); if((p)==NULL){printf("not enough memory\n"); exit(1);};}

typedef struct slobj_{
    int j;
    double v;
    struct slobj_*next;
}* slobj;

typedef struct{
    slobj head;
    slobj tail;
}* slist;

typedef struct{
    int m,n;
    slist* row_vector;
}*smatrix;

slobj slobj_new(int n,double x)
{
    slobj p;
    NEW(p,1);
    p->j = n;
    p->v=x;
    p->next=NULL;
    return p;
}

slist slist_new(void)
{
    slist L;
    NEW(L,1);
    L->head=NULL;
    L->tail=NULL;
    return L;
}

smatrix smatrix_new(int m, int n){
    int i;
    smatrix M;
    NEW(M,1);
    NEW(M->row_vector,m);
    M->m = m;
    M->n = n;
    for (i=0; i<m; i++){
        M->row_vector[i]=slist_new();
    }
    return M;
}

slist slist_insert_tail(slist L, slobj p)
{
    if(L->head== NULL){
        L->head=p;
    }else{
    L->tail->next=p;
    }
    L->tail=p;
    return L;
}






void slist_free(slist L)
{
    slobj p,q;
    p=L->head;
    while (p !=NULL){
        q=p->next;
        free(p);
        p=q;
    }
    free(L);
}

void smatrix_free(smatrix M){
    int i;
    for (i=0; i<M->m; i++){
        slist_free(M->row_vector[i]);
    }
}



void slist_print(slist L)
{
    slobj p;
    p=L->head;
    while (p!=NULL){
        printf("%d %lf  ",p->j, p->v);
        p=p->next;
    }
    printf("-1\n");
}

smatrix smatrix_read(void){
    int i;
    int line_num;
    int m,n;
    double v;
    slobj p;
    smatrix M;
    scanf(" %d",&m);
    scanf(" %d",&n);
    M=smatrix_new(m,n);
    for(i=0; i<m; i++){
        while(1){
            scanf(" %d",&line_num);
            if(line_num==-1){
                break;
            }
            scanf(" %lf",&v);
            p=slobj_new(line_num,v);
            M->row_vector[i]= slist_insert_tail(M->row_vector[i],p);
        }
    }
    return M;
}

void smatrix_print(smatrix M){
    int i;
    double v;
    printf("%d %d\n", M->m, M->n);
    for (i=0; i<M->m; i++){
        slist_print(M->row_vector[i]);
    }
}



smatrix smatrix_transpose(smatrix M){
    int i;
    smatrix MT = smatrix_new(M->n, M->m);
    slobj p, pt;
    for(i=0; i<M->m; i++){
        p=M->row_vector[i]->head;
        while(p !=NULL){
            pt = slobj_new(i+1, p->v);
            MT->row_vector[p->j - 1]=slist_insert_tail(MT->row_vector[p->j - 1], pt);
            p=p->next;
        }
    }
    return MT;
}

double smatrix_access(smatrix S, int i, int j)
{
    slist L;
    slobj p;
    L = S->row_vector[i-1];
    p = L->head;
    if (p == NULL){
        return 0;
    }
    while(1){
        if (p->j==j){
            return p->v;
        }
        if (p->next == NULL){
            return 0;
        }
        p = p->next;
    }
}

smatrix smatrix_product(smatrix A,smatrix B)
{
    smatrix C;
    int m_A,n_A, m_B, n_B;
    int row, col, i;
    double v, a, b;
    
    n_A = A->n; m_A = A->m;
    n_B = B->n; m_B = B->m;
    C = smatrix_new(m_A, n_B);
    for (row = 0; row<m_A; row++){
        for (col = 0; col < n_B; col++){
            v=0;
            for(i=0; i<n_A; i++)
            {
                a = smatrix_access(A, row+1, i+1);
                b = smatrix_access(B, i+1, col+1);
                v = v + a*b;
            }
        if (v !=0){
            slist_insert_tail(C->row_vector[row], slobj_new(col+1,v));
        }
    }
}
    return C;
}

int main(void){
    smatrix A,B,C;
    double v;
    int n_A, m_A, n_B, m_B;
    A = smatrix_read();
    B = smatrix_read();
    n_A = A->n; m_A = A->m;
    n_B = B->n; m_B = B->m;
    if(n_A != m_B)
    {
        printf("0 0\n");
        return 0;
    }
    C = smatrix_product(A,B);
    smatrix_print(C);
    return 0;
}