//Đóng gói code ở bên "inqueue-demo.c" cho dễ nhìn, 
//gọn nhẹ và dễ sử dụng hơn. Và nó dễ nhận ra cấu trúc hàng đợi hơn

#include "istack.h"

#include <stdio.h>

int main(){
	Dllist s = new_dllist();
	ist_push(s, 1);
	ist_push(s, 2);
	ist_push(s, 3);

	printf("First: %d\n", dll_first(s)->val.i);
	printf("Last: %d\n", dll_last(s)->val.i);

	
	return 0;
}