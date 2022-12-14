#include "cgraph/cgraph.h"

#include<stdio.h>

void print_out_degree(cgraph_t *gp, int u){
    CGRAPH_INTEGER res;
    cgraph_degree_one(gp, &res, u, CGRAPH_OUT, false);
    printf("Out degree of %d = %d", u, (int)res);
}

void printf_out_neighbours(cgraph_t *gp, int u){
    cgraph_ivec_t neis = cgraph_ivec_create();
    cgraph_neighbors(gp, &neis, u, CGRAPH_OUT);
    printf("Our neighbours of %d: ", u);
    cgraph_ivec_print(neis);
}

int main(){
    FILE *inp = fopen("input.txt", "r");
    int n;
    fscanf(inp, "%d", &n);
    cgraph_ivec_t edges = cgraph_ivec_create();
    for(int i = 0; i < 2*n; i++){
        int value;
        fscanf(inp, "%d", &value);
        cgraph_ivec_push_back(&edges, value);
    }
    fclose(inp);
    cgraph_ivec_print(edges);

    cgraph_t g;
    cgraph_create(&g, edges, 0, true); // true = có hướng
    //Ở các phiên bản sau: g = cgraph_create(edges, 0, true);

    int u;
    printf("Nhap u: ");
    scanf("%d", &u);
    print_out_degree(&g, u);
    printf_out_neighbours(&g, u);
    cgraph_destroy(&g);
    return 0;
}