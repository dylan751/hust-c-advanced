#include <stdio.h>
#include <stdlib.h>

#include "cgraph/cgraph.h"

#define MAX 100

typedef struct {
	char* name;
	int ID;
} name_arr;

int my_ivec_print(cgraph_ivec_t const v) {
  printf("size: %lld, cap: %lld, elems: ",
              (long long)cgraph_ivec_size(v),
              (long long)cgraph_ivec_capacity(v));
  for (CGRAPH_INTEGER i = 0; i < cgraph_ivec_size(v); ++i) {
    printf(" %lld", (long long)v[i]);
  }
  printf("\n");
  return 0;
}

void print_out_neighbours(cgraph_t *g, int name){
	cgraph_ivec_t neis = cgraph_ivec_create();
    cgraph_neighbors(g, &neis, name, CGRAPH_OUT);
    printf("Our neighbours of %c: ", (char)name);
    my_ivec_print(neis);	
}

int main(){
	int i;
	name_arr arr[MAX];
	int avalaible[100000] = {0};
	FILE *fptr = fopen("Input.txt", "r");
	if(fptr == NULL){
		printf("Cannot open input.txt!\n");
		return -1;
	}
	int mark = 0; //Xem có đỉnh đấy ko
	char name[MAX];
	int num_edges; //The number of edges
	int style; //1: Có hướng 2: Không có hướng 

	fscanf(fptr, "%d %d\n", &num_edges, &style);
	for(i = 0; i < num_edges * 2; i += 2){
		fscanf(fptr, "%s %s\n", arr[i].name, arr[i+1].name);
	}
	int x = 0;

	int int_arr[MAX];
	for(i = 0; i < num_edges*2; i++){
		int_arr[i] = (int)arr[i].name;
	}	

	for(i = 0; i < num_edges*2; i++){
		if(avalaible[int_arr[i]] == 0){
			arr[i].ID = x;
			x++;
			avalaible[int_arr[i]]++;
		}
	}

	for(i = 0; i < num_edges*2; i++){
		printf("%d\n", arr[i].ID);
	}

	cgraph_ivec_t edges = cgraph_ivec_create();
	for(i = 0; i < num_edges*2; i++){
		cgraph_ivec_push_back(&edges, arr[i].ID);
	}

	
	my_ivec_print(edges);

	printf("Input vertices name: ");
	scanf("%s", name);

	int int_name = (int)name; //Convert nodes name into integer
	for(i = 0; i < num_edges*2; i++){
		if(int_name == arr[i].ID){
			mark = 1;
		}
	}
	if(mark == 0){
		printf("There is no vertices %s!\n", name);
		return -1;
	}


	cgraph_t g;
	if(style == 1){ //Có hướng
		cgraph_create(&g, edges, 0, true); // true = có hướng
	}
	else{           //Vô hướng
		cgraph_create(&g, edges, 0, false); // false = vô hướng
	}
	print_out_neighbours(&g, int_name);

	fclose(fptr);
	return 0;
}