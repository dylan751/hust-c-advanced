/*
Sử dụng g1 (đọc g1 từ file input.txt)
    + Nhập đỉnh u
    + Xuất: - Bậc vào u
            - Danh sách đỉnh đi tới u
            - Bậc ra u
            - Danh sách đỉnh đi ra từ u
*/

#include <stdio.h>
#include "cgraph/cgraph.h"
#include <stdlib.h>

int list_to_u(cgraph_t *g1, int u, int size){
    int i;
    printf("Edges comes to %d: ", u);
    for(i = 0; i < size; i++){
        if(g1->to[i] == u){
            printf("%d ", g1->from[i]);
        }
    }
    printf("\n");
}

int list_from_u(cgraph_t *g1, int u, int size){
    int i;
    printf("Edges comes from %d: ", u);
    for(i = 0; i < size; i++){
        if(g1->from[i] == u){
            printf("%d ", g1->to[i]);
        }
    }
    printf("\n");
}

int get_in_deg_u(cgraph_t *g1, int u){
    printf("Indeg: %d", (g1->is)[u+1] - (g1->is)[u]);
    printf("\n");
}

int get_out_deg_u(cgraph_t *g1, int u){
    printf("Outdeg: %d", (g1->os)[u+1] - (g1->os)[u]);
    printf("\n");
}

int main(){
    FILE *fptr;
    int u;
    int i, arr[40];
    int size; //The number of edges

    fptr = fopen("../input.txt", "r");
    if(fptr == NULL){
        printf("Cannot open input.txt\n");
        return -1;
    }

    fscanf(fptr, "%d\n", &size);
    
    for(i = 0; i < 2*size; i += 2){
        fscanf(fptr, "%d %d\n", &arr[i], &arr[i+1]);
    }
    
    printf("Input u: ");
    scanf("%d", &u);
    
    cgraph_ivec_t edges = cgraph_ivec_from_array(arr, 2*size);

    cgraph_t *g1 = malloc(sizeof(cgraph_t));
    cgraph_create(g1, edges, 0, true);
    
    get_in_deg_u(g1, u);
    list_to_u(g1, u, size);
    get_out_deg_u(g1, u);
    list_from_u(g1, u, size);

    free(g1);
    fclose(fptr);
}