#include<stdlib.h>

int less_i(int a, int b){
  return a < b;
}

//So sánh bình thường nhưng mà kiểu void* (generic)
int gen_less_i(void *a, void *b){
  int v1 = *((int*)a),
      v2 = *((int*)b);
  return less_i(v1, v2); 
}

int great_i(int a, int b){
  return a > b;
}

int gen_great_i(void *a, void *b){
  return great_i(*((int*)a), *((int*)b)); //Ep kieu *
}

int less_d(double a, double b){
  return a < b;
}

int gen_less_d(void *a, void *b){
  return less_d((*(double*)a), *((double*)b));
}

int great_d(double a, double b){
  return a > b;
}

int gen_great_d(void *a, void *b){
  return great_d((*(double*)a), *((double*)b));
}