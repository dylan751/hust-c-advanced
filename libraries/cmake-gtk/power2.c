#include <stdio.h>

double readX() {
  printf("x = ");
  double x;
  scanf("%lf", &x);
  return x;
}

double display(double value) {
  printf("%lf\n", value);
}

int main() {
  double x = readX();
  display(x * x);
  return 0;
}