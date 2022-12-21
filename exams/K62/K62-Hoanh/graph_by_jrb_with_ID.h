#include <stdio.h>
#include "libfdr/jrb.h"
#include "libfdr/dllist.h"
#include <string.h>
#define INFINITIVE_VALUE 10000

typedef struct 
{
    JRB edges;
    JRB verticles;
}Graph;

Graph createGraph(){
    Graph g;
    g.edges = make_jrb();
    g.verticles = make_jrb();
    return g;
}
void addVertex(Graph g, int id, char * name){
    //kiem tra xem dinh do co ton tai tren do thi g hay chua 
    JRB node =  jrb_find_int(g.verticles, id);
    {
        if(node == NULL){  // dinh chua ton tai
            jrb_insert_int(g.verticles, id, new_jval_s((name)));
        }
    }
}
JRB getfullItemVertex(Graph g, int id){
    JRB node = jrb_find_int(g.verticles, id);
    if(node == NULL) 
    return  NULL;
    else return  node;  //jval_s(node->val);
}
char *getVertex(Graph g, int id){
    JRB node = jrb_find_int(g.verticles, id);
    if(node == NULL) 
    return  NULL;
    else return jval_s(node->val);
}
double getEdgeValue(Graph graph, int v1, int v2){
    JRB node, tree;
    node = jrb_find_int(graph.edges, v1);
    if(node ==  NULL) return INFINITIVE_VALUE;

    tree = (JRB)jval_v(node->val);
    node =  jrb_find_int(tree, v2);
    if(node == NULL) // v2 ko ke voi v1
    return INFINITIVE_VALUE; // graph ko co canh v1 v2
    else return jval_d(node->val); // truy cap vao truong val de lay trong so cua  canh v1, v2

}

int indegree(Graph graph,  int v, int *output){      // tim bac vao cua dinh
    JRB tree, node;
    int total = 0;
    jrb_traverse(node, graph.edges){
        tree =  (JRB) jval_v(node->val);
        if(jrb_find_int(tree, v)){
            output[total] == jval_i(node->key);
            total ++;
        }
    }
    return total;
}
int outdegree(Graph graph, int v, int *output){   // tim bac ra cua dinh
    int total = 0;
    JRB node  = jrb_find_int(graph.edges, v);
    if(node == NULL) return 0;
    JRB tree =  (JRB)jval_v(node->val);
    jrb_traverse(node, tree)
    {
        output[total] =  jval_i(node->key);
        total++;
    }
    return total;
    
}
int DFS_DAG(Graph graph, int start){
    int visited[1000] = {};
    int n, output[100], i, u , v;
    Dllist node, stack;
    stack = new_dllist();
    dll_append(stack, new_jval_i(start));
    while(! dll_empty(stack)){
        node = dll_last(stack);
        u = jval_i(node->val);
        dll_delete_node(node);
        if(!visited[u]){
            visited[u] =  1;
            n = outdegree(graph, u, output);
            for(i =0; i < n ; i++){
                v = output[i];
                if(v == start) return 0; //cycle deleted
                if(!visited[v]) dll_append(stack, new_jval_i(v));
            }
        }
    }
    return 1;
}

void dropGraph(Graph graph){
    JRB node, tree;
    jrb_traverse(node, graph.edges)
    {
        tree = (JRB)jval_v(node->val);
        jrb_free_tree(tree);
    }
    jrb_free_tree(graph.edges);
    jrb_free_tree(graph.verticles);
}
int DAG(Graph graph){
    int start, notCycle;
    JRB vertex;
    jrb_traverse(vertex, graph.verticles){ // duyet  qua từng đỉnh của đồ thị
        start = jval_i(vertex->key);
        printf("goi DFS xuat phat tu dinh  %d \n", start);
        notCycle =  DFS_DAG(graph, start);
        if(notCycle == 0) return 0; // do thi ko phai là DAG; detect cycle
    
    }return 1; // do thi la DAG, no cycle
}
void addEdge(Graph graph, int v1, int v2, double weight){
    JRB node, tree;
    if(getEdgeValue(graph, v1, v2) == INFINITIVE_VALUE){ // neu graph chua co canh v1,v2
        node = jrb_find_int(graph.edges, v1); // tim dinh v1 tren tap canh graph.edges
        if(node == NULL){
            tree = make_jrb();
            jrb_insert_int(graph.edges, v1, new_jval_v(tree)); // them v1 vao graph.edges
        }
        else // graph.edges  da co dinh v1
           tree = (JRB) jval_v(node->val); // tree : cay do den cua dinh v1
           // them v2 vao cay do den cua dinh v2
           jrb_insert_int(tree, v2, new_jval_d(weight));

        
    }
}

int count;
double shortestPath_s_To_t(Graph g, int s, int t, int* p ){
    double d[1000], k[1000], min, w;
    int n, output[100], i, u ,v;
    Dllist ptr, queue;
    JRB node;
  
    for (i = 0;  i <1000; i++){
        d[i] = INFINITIVE_VALUE;
        k[i] =  0; // chua tim duoc duong di tu s den i
    }
    d[s] = 0; p[s] = s;
    // bo sung tat ca dinh cua do thi vao hang doi Q
    queue = new_dllist();
    jrb_traverse(node, g.verticles)
       dll_append(queue, new_jval_i(jval_i(node->key)));
       while( !dll_empty(queue)){

            min =  INFINITIVE_VALUE +1;
            dll_traverse(ptr, queue)
            {
                 v = jval_i(ptr->val);
                 if(min > d[v]){
                     min = d[v];
                     node = ptr; 
                     u = v;
                 }
            }
            k[u] = 1; // da tim dc ddnn tu s den u
            dll_delete_node((Dllist)node);

            if(u == t) break;
            n = outdegree(g, u, output);
            for( i = 0; i < n; i++){
                v = output[i];
                if(k[v] == 0){
                    w = getEdgeValue(g, u, v);
                    if(d[v] > d[u] + w){
                        d[v] = d[u] + w;
                        p[v]  = u;
                    }
                }
            }

       }
    return d[t];
}


int adjacent(Graph graph, int v1, int v2)
{
JRB node, tree;
//kiểm tra xem đồ thị g có chứa đỉnh v1 hay không:
node = jrb_find_int(graph.edges, v1);
if (node==NULL) return 0; //g ko co dinh v1
/* đồ thị g có v1: tiếp tục lấy trường value (chứa danh sách kề) của đỉnh v1 để kiểm tra xem
v1 có kề với v2 không: */
tree = (JRB) jval_v(node->val);
if (jrb_find_int(tree, v2)== NULL)
return 0;
else return 1;
}
int count_Connected_Component(Graph g, int ver_num) {
    int mark[ver_num + 1];

    int succes;
    int count = 0, i,j, Connected_Comp_Num = 0;
    for( i = 0; i< ver_num; i++) //khoi tao cac dinh chua danh dau
        mark[i] = 0;
        do {
           j = 0;
           while(mark[j]==1) //tim 1 dinh chua duoc danh dau
           j++;
           mark[j] = 1; //danh dau dinh tim duoc
           count++; //tang so dinh danh dau len 1
           Connected_Comp_Num ++; //tang so thanh phan lien thong len 1
          do {
              succes = 0;
              for(i = 0; i < ver_num; i++)
                 if(mark[i]==1)
                    for(j = 0; j < ver_num; j++)
                          if (mark[j] == 0 && getEdgeValue(g, i, j) != INFINITIVE_VALUE) {
                               mark[j] = 1;
                               succes =1;
                               count ++;
                               if(count == ver_num) return Connected_Comp_Num;
                           }
             }while (succes == 1);
         } while(count < ver_num); //lap lai khi con dinh chua duoc danh dau
    return Connected_Comp_Num;
}