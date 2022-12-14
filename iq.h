#ifndef IQ_H_
#define IQ_H_

#include "libfdr/dllist.h"

#include <stdio.h>

static void iq_enqueue(Dllist q, int i) {
	dll_append(q, (Jval){.i = i}); //Tương đương với append trong Queue
}

static int iq_dequeue(Dllist q){
	int value = (dll_first(q)->val.i);
	dll_delete_node(dll_first(q));  //Tương đương với dequeue trong Queue
	return value;
}
static void iq_traverse(Dllist q){
    Dllist cur;
    dll_traverse(cur, q){
        printf("%d ", cur->val.i);
    }
    printf("\n");
}

static void iq_rtraverse(Dllist q){
    Dllist cur;
    dll_rtraverse(cur, q){
        printf("%d ", cur->val.i);
    }
    printf("\n");
}

#endif //IQ_H_