#ifndef MYLIB_H_
#define MYLIB_H_

typedef int (*predicate_t)(void *a, void *b);

void quickSort(void *A, int n, int member_sz, predicate_t cmp);
#endif //MYLIB_H_