#include <stdio.h>
#include <stdlib.h>
#include "dllist.h"
typedef struct{
    int *matrix;
    int n;
}Graph;
// đồ thị trong thư viện này là đo thi ko có hướng
Graph createGraph(int n); // ham tao do thi
void addEdge(Graph graph, int v1, int v2); // ham them canh vao do thi
int adjacent(Graph graph, int v1, int v2); //ham kiem tra xem do thi co canh(v1,v2) hay ko
int getAdjacentVertices(Graph graph, int v, int *output);// Trả về số lượng các đỉnh kề với đỉnh v trên đồ thị; đồng thời mảng output sẽ chứa danh sách các đỉnh kề với đỉnh v
void dropGraph(Graph graph);

Graph createGraph(int n){
    Graph g;
    g.n = n;
    g.matrix = (int*)malloc(n*n*sizeof(int));
    return g;
}

void addEdge(Graph graph, int v1, int v2){
    graph.matrix[v1* graph.n + v2] =  1;
    graph.matrix[v2* graph.n + v1] = 1;
}

int adjacent(Graph graph, int v1, int v2){
    return graph.matrix[v1 *graph.n +v2];
}
int getAdjacentVertices(Graph graph, int v, int *output){
    int total = 0, i;
    for(i = 0; i <graph.n ; i++){
        if(adjacent(graph, v, i)){
        output[total++] = i;
        }
    }
    return total;
}
void dropGraph(Graph graph){
    free(graph.matrix);
    graph.matrix = NULL;
    graph.n = 0;
}
void PrintVertex(int v){
    printf("%4d", v);
}
void BFS(Graph graph, int start, int stop, void (*func)(int)){
    
int visited[1000] = {};
int n, output[100], i, u, v;
Dllist node, queue;
queue = new_dllist();
dll_append(queue, new_jval_i(start)); //thêm phần tử start vào queue
while ( !dll_empty(queue) )
{
node = dll_first(queue);
u = jval_i(node->val);
dll_delete_node(node);
if (!visited[u]) //nếu u chưa được thăm
{
func(u);
visited[u] = 1;
if ( u == stop ) return; //đỉnh u = stop  kết thúc BFS
n = getAdjacentVertices(graph, u, output);
for (i=0; i<n; i++) //xét lần lượt các đỉnh kề với đỉnh u
{
v = output[i];
if (!visited[v]) //thêm v vào queue nếu v chưa được thăm
dll_append(queue, new_jval_i(v));
}
}
}
}
//#endif //IQ_H_

void BFS_Shortest_Path(Graph graph,int start, int stop, int*truoc){
    int visited[1000] = {};
int n, output[100], i, u, v;
Dllist node, queue;
queue = new_dllist();
dll_append(queue, new_jval_i(start)); //thêm phần tử start vào queue
while ( !dll_empty(queue) )
{
node = dll_first(queue);
u = jval_i(node->val);
dll_delete_node(node);
if (!visited[u]) //nếu u chưa được thăm
{
visited[u] = 1;
if ( u == stop ) return; //đỉnh u = stop  kết thúc BFS
n = getAdjacentVertices(graph, u, output);
for (i=0; i<n; i++) //xét lần lượt các đỉnh kề với đỉnh u
{
v = output[i];
if (!visited[v]){
    truoc[v] = u; 
dll_append(queue, new_jval_i(v)); //thêm v vào queue nếu v chưa được thăm
}
}
}
}
}
