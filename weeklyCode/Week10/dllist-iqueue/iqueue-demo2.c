/* Đóng gói code ở bên "inqueue-demo.c" cho dễ nhìn, 
gọn nhẹ và dễ sử dụng hơn. Và nó dễ nhận ra cấu trúc hàng đợi hơn */

#include "iq.h"

int main(){
	Dllist q = new_dllist();
	iq_enqueue(q, 1);
	iq_enqueue(q, 2);
	iq_enqueue(q, 3);

	printf("First: %d\n", dll_first(q)->val.i);
	printf("Last: %d\n", dll_last(q)->val.i);

	iq_traverse(q);
	iq_rtraverse(q);

	printf("Dequeue: %d ", iq_dequeue(q));
	printf("\nAfter dequeued: ");
	iq_traverse(q);
	
	free_dllist(q);
	printf("\n");
	return 0;
}