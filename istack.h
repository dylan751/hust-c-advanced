#ifndef ISTACK_H_
#define ISTACK_H_

#include "libfdr/dllist.h"

static void ist_push(Dllist s, int value) {	  //ist: istack
	dll_append(s, (Jval){.i = value});
}  


static int ist_pop(Dllist s) { 				  //Lấy giá trị và xóa
	int value = (dll_last(s)->val.i);
	dll_delete_node(dll_last(s));
	return value;
}

static int ist_top(Dllist s) {				  //Lấy giá trị (không xóa)
	int value = (dll_last(s)->val.i);
	return value;
}

#endif //ISTACK_H_

