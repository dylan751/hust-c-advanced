#include <stdio.h>
#include "jrb.h"
#include "dllist.h"
typedef JRB Graph;
// do thi trong day la do thi co huong
Graph createGraph();
void addEdge(Graph graph, int v1, int v2);
int adjacent(Graph graph, int v1, int v2); //ham kiem tra xem do thi co canh(v1,v2) hay ko
int getAdjacentVertices(Graph graph, int v, int *output);// Trả về số lượng các đỉnh kề với đỉnh v trên đồ thị; đồng thời mảng output sẽ chứa danh sách các đỉnh kề với đỉnh v
void dropGraph(Graph graph);

Graph createGraph(){
    return make_jrb();
}

void addEdge(Graph graph, int v1, int v2)
{
JRB node, tree;
//1. Thêm cạnh (v1, v2):
if (!adjacent(graph, v1, v2)) //(v1, v2) chưa có trên đồ thị
{
node = jrb_find_int(graph, v1); //tìm đỉnh v1 trên đồ thị
if (node==NULL) { //đồ thị chưa có đỉnh v1:
tree = make_jrb();
jrb_insert_int(graph, v1, new_jval_v(tree));
}
else //đồ thị đã có đỉnh v1:
tree = (JRB) jval_v(node->val);
jrb_insert_int(tree, v2, new_jval_i(1));
}
//2. Thêm cạnh (v2, v1):

}
void dropGraph(Graph graph){
    JRB node, tree;
    jrb_traverse(node, graph){
        tree = (JRB) jval_v(node->val);
        jrb_free_tree(tree);
    }
    jrb_free_tree(graph);
}
int adjacent(Graph graph, int v1, int v2)
{
JRB node, tree;
//kiểm tra xem đồ thị g có chứa đỉnh v1 hay không:
node = jrb_find_int(graph, v1);
if (node==NULL) return 0; //g ko co dinh v1
/* đồ thị g có v1: tiếp tục lấy trường value (chứa danh sách kề) của đỉnh v1 để kiểm tra xem
v1 có kề với v2 không: */
tree = (JRB) jval_v(node->val);
if (jrb_find_int(tree, v2)== NULL)
return 0;
else return 1;
}
int getAdjacentVertices (Graph g, int v, int* output){
//Để lấy ra các đỉnh liền kề của v trong đồ thị g:
JRB node = jrb_find_int(g, v); //tìm đỉnh v trong g
if (node == NULL) return 0;
JRB tree = (JRB) jval_v(node->val); /*truy cập vào trường
value của đỉnh v ~ 1 cây đỏ đen */
int total = 0;
//duyệt cây đỏ đen của đỉnh v, để đưa ra các đỉnh kề với đỉnh v vào mảng output:
jrb_traverse(node, tree)
output[total++] = jval_i(node->key);
return total;
}

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
