#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#include"mylib.h"
#include"utility.h"

int main(){  
  int a[] = {3, 2, 1, 5, 8, 9, 4, 7, 6};
  int b[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int c[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};

  int n = sizeof(a)/sizeof(a[0]);
  quickSort(a, n, sizeof(int), gen_less_i);
  

  int i;

  //Kiểm tra xem mảng a đã sắp xếp tăng dần chưa
  for(i = 0; i < n; i++){
      if(a[i] != b[i]){
          printf("Test increasing order: Failed\n");
          return 1;
      }
  }

  //Kiểm tra xem mảng a đã sắp xếp giảm dần chưa
  quickSort(a, n, sizeof(int), gen_great_i);
  for(i = 0; i < n; i++){
    if(a[i] != c[i]){
      printf("Test decreasing order: Failed\n");
      return 1;
    }

  }

  double d1[] = {3.0, 2.0, 5.0, 4.0, 1.0};
  double d2[] = {1.0, 2.0, 3.0, 4.0, 5.0};
  double d3[] = {5.0, 4.0, 3.0, 2.0, 1.0};
  int nd = sizeof(d1)/sizeof(d1[0]);
  quickSort(d1, nd, sizeof(double), gen_less_d);
  //print_a_d(d1, nd);
  for(i = 0; i < nd; i++){
    if(d1[i] != d2[i]){
      printf("Test double increasing order: Failed\n");
      return 1;
    }
  }

  quickSort(d1, nd, sizeof(double), gen_great_d);
  for(i = 0; i < nd; i++){
    if(d1[i] != d3[i]){
      printf("Test double decreasing order: Failed\n");
      return 1;
    }
  }

  printf("OK\n");
  return 0;
}