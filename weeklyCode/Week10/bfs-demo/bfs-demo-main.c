#include "cgen/s2i.h"
#include "cgen/svector.h"
#include "cgraph/cgraph.h"

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
	cgraph_ivec_t edges = cgraph_ivec_create();
	FILE *inp = fopen("input.txt", "r");
	if(inp == NULL){
		printf("Cannot open!\n");
		return -1;
	} 
	int n, d; //n: Số cạnh, d=1 -> có hướng, d=0 -> vô hướng
	fscanf(inp, "%d %d", &n, &d);
	char u[100], v[100];
	for(int i = 0; i < n; ++i) {
		fscanf(inp, "%s %s", u, v);
		int uid = get_save_id(u);
		int vid = get_save_id(v);
		cgraph_ivec_push_back(&edges, uid);
		cgraph_ivec_push_back(&edges, vid);
	}
	fclose(inp);
	cgraph_t g = cgraph_create(edges, 0, d == 1? CGRAPH_DIRECTED : CGRAPH_UNDIRECTED);
	printf("Nhap dinh: ");
	scanf("%s", u);
	int uid = s2i_value(s2i, u);
	cgraph_ivec_t father = cgraph_ivec_create(),
	              dist = cgraph_ivec_create();
	cgraph_simple_bfs(g, uid, CGRAPH_OUT, false, &father, &dist);
	printf("Tu %s di toi: ", u);
	for(int i = 0; i < cgraph_ivec_size(dist); i++) {
		if(dist[i] >= 0) {
			printf("%s ", i2s[i]);
		}
	}
	printf("\n");
	
	cgraph_destroy(&g);
	s2i_free(&s2i);
	gtv_free(&i2s);
	//...
	return 0;
}