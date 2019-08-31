#include <stdio.h>
#include <stdlib.h>

#define NEW(p,n) {p = malloc((n)*sizeof(p[0])); if ((p)==NULL) {printf("not enough memory\n"); exit(1);};}
#define EPS 1E-10

typedef struct {
  int d; // degree
  double* a;
}* polynomial;

void read_func(polynomial f, int d){
  int i;
  for (i = 0; i <= d; i++) {scanf("%lf", &f->a[i]);}
}

double eval(polynomial f, double x){
  int i, _; double x_, val;
  val = 0.0;
  for (i = 0; i <= f->d; i++) {
    x_ = 1.0;
    for (_ = 0; _ < f->d - i; _++) {x_ *= x;}
    val += f->a[i] * x_;
  }
  return val;
}

double solve(polynomial f, double s, double e){
  double f_s, f_e, f_m;
  double range, s_, e_, mid;
  s_ = s; e_ = e;
  range = e_ - s_;
  mid = (s_ + e_) / 2;
  while (range > EPS){
    f_s = eval(f, s_); f_m = eval(f, mid); f_e = eval(f, e_);
    if (f_s == 0.0) {return s_;}
    if (f_m == 0.0) {return mid;}
    if (f_e == 0.0) {return e_;}
    if (f_s * f_m >= 0) {s_ = mid;}
    else {e_ = mid;}
    mid = (s_ + e_) / 2;
    range = e_ - s_;
  }
  return mid;
}

int main(void) {
  polynomial f;
  int d;
  double s, e;
  double res;
  scanf("%d", &d);
  NEW(f, 1);
  NEW(f->a, d+1);
  f->d = d;
  read_func(f, d);
  scanf("%lf %lf", &s, &e);
  res = solve(f, s, e);
  printf("%.10lf", res);
  return 0;
}