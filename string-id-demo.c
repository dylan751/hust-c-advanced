#include "cgen/s2i.h"
#include "cgen/svector.h"

#include <stdio.h>

bn_tree_t s2i = NULL;
vector_t i2s = NULL;
int g_id = 0;

int get_save_id(char *key) {
	int res = s2i_value(s2i, key);    //search
	if(res != k_s2i_invalid) {		  //Nếu tìm thấy -> return
		return res;					
	} 					
	s2i_insert(s2i, key, g_id);		  //Nếu không tìm thấy -> insert
	svec_push_back(&i2s, key);
	res = g_id;
	++g_id;
	return res;
}

int main(){
	s2i = s2i_create();  //String to int
	i2s = gtv_create();	 //Int to string
	FILE *inp = fopen("input.txt", "r");
	if(inp == NULL){
		printf("Cannot open!\n");
	}

	int n, d;
	fscanf(inp, "%d %d", &n, &d);
	char u[100], v[100];
	for(int i = 0; i < n; ++i) {
		fscanf(inp, "%s %s", u, v);
		int uid = get_save_id(u);
		int vid = get_save_id(v);
	}
	fclose(inp);
	printf("Nhap ten dinh: ");
	scanf("%s", u);
	int id = s2i_value(s2i, u);
	if(id == k_s2i_invalid) {
		printf("Dinh khong ton tai!");
	} else {
		printf("Id of %s = %d\n", u, id);
	}

	printf("Nhap id: ");
	scanf("%d", &id);
	if(id < 0 || id >= g_id) {
		printf("Ngoai khoang gia tri!\n");
	} else {
		printf("Name of %d is %s\n", id, (char*)i2s[id]);
	}

	s2i_free(&s2i);
	gtv_free(&i2s);
	return 0;
}