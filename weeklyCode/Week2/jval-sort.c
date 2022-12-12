#include"jval.h"
#include"mylib.h"
#include<stdio.h>

void print_i(Jval v){
    printf("v.i = %d\n", jval_i(v));
}

void print_d(Jval v){
    printf("v.d = %d\n", jval_d(v));
}

int gen_less_ji(void *a, void *b){
    Jval *p1 = a,
         *p2 = b;
    return p1->i < p2->i;
}

int main(){
    Jval a[] = {(Jval){.i = 3}, (Jval){.i = 1}, (Jval){.i = 2}};
    int n = sizeof(a)/sizeof(a[0]);
    quickSort(a, n, sizeof(a[0]), gen_less_ji);
    int i;
    for(i = 0; i < n; i++){
        printf("[%d] = %d\n", i, a[i].i);
    }  
    return 0;
}