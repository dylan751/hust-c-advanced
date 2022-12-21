//include "libfdr/cgraph_datatype.h"
#include "libfdr/graph_by_jrb.h"
//#include "libfdr/jrb.h"

int main(){
    int i, n, output[10];
    Graph g = createGraph();
    addEdge(g, 0, 1);
    addEdge(g, 0 ,2);
    addEdge(g, 1 ,2);
    addEdge(g, 1 ,3);
    addEdge(g, 3, 4);
    addEdge(g, 0 ,4);
    addEdge(g, 1 ,5);
    addEdge(g, 6 ,5);
    for( int i = 0; i< 7; i ++){
    n = getAdjacentVertices(g , i ,output);
    if( n == 0 ) printf("\n Dinh %d khong ke voi dinh nao cua do thi", i);
    else {
        printf("\n Co %d dinh ke voi %d -> Danh sach cac dinh ke voi %d :", n , i, i );
        for(int j = 0; j < n; j++) printf("%5d", output[j]);
    }
    }
    dropGraph(g);
}