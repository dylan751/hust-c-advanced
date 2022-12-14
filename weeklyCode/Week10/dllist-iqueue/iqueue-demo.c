#include "libfdr/dllist.h"

#include <stdio.h>

int main(){
	Dllist list = new_dllist();
	dll_append(list, (Jval){.i = 1}); //Tuong với Enqueue trong Queue
	dll_append(list, (Jval){.i = 2});
	dll_append(list, (Jval){.i = 3});

	printf("First: %d\n", dll_first(list)->val.i);
	printf("Last: %d\n", dll_last(list)->val.i);

	Dllist cur;
	dll_traverse(cur, list){
		printf("%d ", cur->val.i);
	}
	printf("\n");

	dll_rtraverse(cur, list){
		printf("%d ", cur->val.i);
	}
	printf("\n");

	dll_delete_node(dll_first(list));  //Tương đương với dequeue trong Queue
	dll_traverse(cur, list){
		printf("%d ", cur->val.i);
	}
	printf("\n");
	return 0;
}