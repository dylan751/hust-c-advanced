#include <stdio.h>
#include "graph_by_jrb_with_ID.h"


int main(){
    int i, previous[100], s,t ;
    double w;
    Graph g = createGraph();
    
    addVertex(g, 0, "V0"); addVertex(g, 1, "V1");
    addVertex(g, 2, "V2"); addVertex(g, 3, "V3"); 
    addVertex(g, 4, "V4");

    addEdge(g, 0, 1, 1); addEdge(g, 1, 2, 3);
    addEdge(g, 2, 0, 3); addEdge(g, 1, 3, 1);
    addEdge(g, 3, 2, 1); addEdge(g, 4, 3, 5);
    printf("Nhap id dinh bat dau va dinh ket thuc ( nam trong khoang 0 den 4) :\n");
    scanf("%d %d",&s ,&t);
    w = shortestPath_s_To_t(g, s, t, previous);
    if(w == INFINITIVE_VALUE) printf("Khong ton tai duong di tu %s den %s\n", getVertex(g, s), getVertex(g,t));
    else {
        printf("Duong di ngan nhat tu %s den %s la \n", getVertex(g, s), getVertex(g,t));
        printf("Do dai = %f \n", w);
        printf("Duong di :\n"); i = t;
        do{
            printf("%s <== ", getVertex(g,i));
            i = previous[i];
        }
        while(i != s);
        printf("%s", getVertex(g, s));

    }
    dropGraph(g);

}