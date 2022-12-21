#include "duyet_cay.h"

int main(){
    int i, n, output[10];
    Graph g = createGraph();
    addEdge(g, 1, 0);
    addEdge(g, 1 ,2);
    addEdge(g, 1 ,3);
    addEdge(g, 2, 3);
    addEdge(g, 2 ,4);
    addEdge(g, 4 ,5);
    printf("BFS from 1 -> 4 :");
    BFS(g, 1, 4, PrintVertex);
    printf("BFS from 1 -> all :");
    BFS(g, 1, -1, PrintVertex);
}