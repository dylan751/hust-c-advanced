//Quicksort -> n.logn

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

void quickSort(int *A, int p, int r){
  int q;
  if(p < r){
    q = partition(A, p, r);
    quickSort(A, p, q-1);
    quickSort(A, q+1, r);
  }
}


int main(int argc, char* argv[]){
  if(argc != 2){
    printf("Wrong syntax! Should be: ./soSanhHieuNangQuicksort <number of elements>\n");
    return -1;
  }

  srand(time(NULL));
  int n;
  sscanf(argv[1], "%d", &n); //Doc so phan tu

  int i;
  int *A = malloc(sizeof(int) * n);
  
  for(i = 0; i < n; i++){
    A[i] = rand();
  }
  
  double start = clock();
  quickSort(A, 0, n-1);
  double end = clock();

  printf("%d phan tu: %lf\n", n, (double)(end-start)/CLOCKS_PER_SEC);

  free(A);
  return 0;
}
