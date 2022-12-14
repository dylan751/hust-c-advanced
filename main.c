#include <stdio.h>
#include <stdlib.h>

#include "cgraph/cgraph.h"

#define MAX 100

int my_ivec_print(cgraph_ivec_t const v) {
  printf("size: %lld, cap: %lld, elems: ",
              (long long)cgraph_ivec_size(v),
              (long long)cgraph_ivec_capacity(v));
  for (CGRAPH_INTEGER i = 0; i < cgraph_ivec_size(v); ++i) {
    printf(" %c", (char)v[i]);
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
	char arr[MAX];
	FILE *fptr = fopen("Input.txt", "r");
	if(fptr == NULL){
		printf("Cannot open input.txt!\n");
		return -1;
	}
	int mark = 0; //Xem có đỉnh đấy ko
	char name;
	int num_edges; //The number of edges
	int style; //1: Có hướng 2: Không có hướng 

	fscanf(fptr, "%d %d\n", &num_edges, &style);
	for(i = 0; i < num_edges * 2; i += 2){
		fscanf(fptr, "%c %c\n", &arr[i], &arr[i+1]);
	}

	cgraph_ivec_t edges = cgraph_ivec_create();
	for(i = 0; i < num_edges*2; i++){
		cgraph_ivec_push_back(&edges, arr[i]);
	}

	
	my_ivec_print(edges);

	printf("Input vertices name: ");
	scanf("%c", &name);

	int int_name = (int)name; //Convert nodes name into integer
	for(i = 0; i < num_edges*2; i++){
		if(int_name == arr[i]){
			mark = 1;
		}
	}
	if(mark == 0){
		printf("There is no vertices %c!\n", name);
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