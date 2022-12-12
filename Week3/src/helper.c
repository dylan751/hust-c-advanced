#include<stdio.h>

void print_a(int *A, int n){
  int i;
  for(i = 0; i < n; i++){
    printf("%5d", A[i]);
  }
  printf("\n");
}

//In kieu double
void print_a_d(double *A, int n){
  int i;
  for(i = 0; i < n; i++){
    printf("%5d", A[i]);
  }
  printf("\n");
}