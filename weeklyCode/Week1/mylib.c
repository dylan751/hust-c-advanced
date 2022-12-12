#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void swap(int* a, int* b){
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}

void print_a(int *A, int p, int r){
  int i;
  for(i = p; i <= r; i++){
    printf("%5d", A[i]);
  }
  printf("\n");
}

int partition(int *A, int p, int r){
  int i, j;
  int x = A[r];
  i = p-1;

  for(j = p; j < r; j++){
    if(A[j] <= x){
      i += 1;
      //Swap A[i] and A[j]
      swap(&A[i], &A[j]);
    }
  }
  swap(&A[i+1], &A[r]);

  return i+1;
}

//Da chuyen ve 2 tham so thay vi 3 tham so nhu ban dau
void quickSort(int *A, int n){
  int q;
  if(1 < n){
    q = partition(A, 0, n-1);
    //p = 0
    //r = n-1
    //p->q-1 co p-q phan tu
    quickSort(A, q);//n = q-p = q-0
    //quickSort(A, q+1, r); //n = r-q
    quickSort(A+q+1, n-1-q);
  }
}