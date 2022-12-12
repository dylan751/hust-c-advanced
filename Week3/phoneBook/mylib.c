#include"mylib.h"

typedef int (*predicate_t)(void *a, void *b); //Con tro ham


static void swap(void *a, void *b, int member_sz){
  int i;
  char *pa = a,
       *pb = b;
  char tmp;
  for(i = 0; i < member_sz; i++){
    tmp = *pa;
    *pa = *pb;
    *pb = tmp;
    ++pa;
    ++pb;
  }
}

//static để người dùng ko thể gọi hàm partition ngoài phạm vi file này
static int partition(void *A, int p, int r, int member_sz, predicate_t cmp){
  char *t = A;
  //a[r] ~ t + r * member_sz
  int i, j;
  void *x = t + r * member_sz;
  i = p-1;

  for(j = p; j < r; j++){
    if(cmp(t + j * member_sz, x)){
      i += 1;
      //Swap A[i] and A[j]
      swap(t + i *member_sz, t + j *member_sz, member_sz);
    }
  }
  swap(t + (i+1) * member_sz, t + r * member_sz, member_sz);

  return i+1;
}

//Da chuyen ve 2 tham so thay vi 3 tham so nhu ban dau
void quickSort(void *A, int n, int member_sz, predicate_t cmp){
  int q;
  if(1 < n){
    q = partition(A, 0, n-1, member_sz, cmp);
    quickSort(A, q, member_sz, cmp);
    char *tmp = A;
    tmp += (q+1) * member_sz;
    quickSort(tmp, n-1-q, member_sz, cmp);
  }
}