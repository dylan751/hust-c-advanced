#ifndef IQ_H_
#define IQ_H_
#include "libfdr/dllist.h"
#include "libfdr/graph_by_jrb.h"
void BFS(Graph graph, int start, int stop, void (*func)(int));
// static void iq_enqueue(Dllist q, int i);
// void iq_enqueue(Dllist q, int i) {
// 	dll_append(q, (Jval){.i = i}); //Tương đương với append trong Queue
// }

// static int iq_dequeue(Dllist q);
// int iq_dequeue(Dllist q){
// 	int value = (dll_first(q)->val.i);
// 	dll_delete_node(dll_first(q));  //Tương đương với dequeue trong Queue
// 	return value;
// }
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
#endif //IQ_H_

