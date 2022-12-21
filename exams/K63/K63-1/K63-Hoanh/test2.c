 #include "libfdr/cgraph_datatype.h"
//#include "libfdr/graph_by_jrb.h"
// #include "libfdr/jrb.h"
//#include "graph_by_jrb_with_ID.h"
int main(){
    int i, n, output[10];
    Graph g = createGraph(10);
    addEdge(g, 0, 1);
    addEdge(g, 1 ,2);
    addEdge(g, 1 ,3);
    addEdge(g, 2 ,3);
    addEdge(g, 2, 4);
    addEdge(g, 4 ,5);
    addEdge(g, 6 , 8);
    for( int i = 0; i< 7; i ++){
    n = getAdjacentVertices(g , i ,output);
    if( n == 0 ) printf("\nDinh %d khong ke voi dinh nao cua do thi", i);
    else {
        printf("\n Co %d dinh ke voi %d -> Danh sach cac dinh ke voi %d :", n , i, i );
        for(int j = 0; j < n; j++) printf("%5d", output[j]);
    }
    }
    printf("\nDuyet do thi tu 1 den 5 :\n");
    BFS(g, 1, 5, PrintVertex);
    int truoc[100] = {-1};
    int start = 1, stop = 5;
    BFS_Shortest_Path(g,start , stop, truoc);
    if(truoc[stop] != -1){
        printf("\nDuong di ngan nhat tu 1 den 5 la :\n");
        int i = stop;
        while(i != start)
        {
            printf("%d <-- ", i );
            i = truoc[i];
        }
        
        printf("%d\n", start);
    }
    else printf("Ko ton tai duong di tu %d den %d", start , stop);
    dropGraph(g);
}
