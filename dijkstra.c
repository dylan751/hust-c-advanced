#include "cgraph/cgraph.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

cgraph_t create_g() {
    cgraph_ivec_t edges = cgraph_ivec_from_array(
        (CGRAPH_INTEGER[]){ 0, 2,
                            0, 7,
                            0, 6,
                            2, 3,
                            3, 5,
                            6, 3,
                            6, 5,
                            6, 7,
                            7, 5,
                            5, 4,
                            5, 8,
                            7, 8,
                            4, 8,
                            3, 8,
                            4, 3}, 30);
  return cgraph_create(edges, 0, true);
}

int main() {
    cgraph_t g = create_g();
    double w[] = {9, 15, 14, 24, 2, 18, 30, 5, 20, 11, 16, 44, 6, 19, 6};
    int n = sizeof(w) / sizeof(double);
    int sum;
    cgraph_rvec_t weights = cgraph_rvec_create();
    for (int i = 0; i < n; ++i) {
        cgraph_rvec_push_back(&weights, w[i]);
    }

    cgraph_ivec_t vpath = cgraph_ivec_create(),
                  epath = cgraph_ivec_create();

    cgraph_get_shortest_path_dijkstra(g, &vpath, &epath, 0, 8, weights, CGRAPH_OUT);
    bool any = false;
    cgraph_ivec_print(vpath);
    
    int length = 0;
    for(int i = 0; i < cgraph_ivec_size(epath); i++){
        length += weights[epath[i]];
    }
    printf("Do dai duong di: %d\n", length);
  
    return 0;
}