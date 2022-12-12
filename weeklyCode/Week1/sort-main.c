#include<stdlib.h>
#include<stdio.h>
#include<time.h>

int main(int argc, char* argv[]){  
  int a[] = {3, 2, 1, 5, 8, 9, 4, 7, 6};
  int b[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  int n = sizeof(a)/sizeof(a[0]);
  quickSort(a, n);
  print_a(a, 0, n-1);
  
  int i;
  for(i = 0; i < n; i++){
      if(a[i] != b[i]){
          printf("Something is wrong\n");
          return 1;
      }
  }
  printf("OK\n");
  return 0;
}