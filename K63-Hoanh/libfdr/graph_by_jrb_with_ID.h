#include <stdio.h>
#include "libfdr/jrb.h"
#include "libfdr/dllist.h"
#define INFINITIVE_VALUE

typedef struct 
{
    JRB edges;
    JRB verticles;
}Graph;
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
int outdegree(Graph graph, int v, int *output){
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
       dll_append(queue, new_jval_i(jval_i)(node->key));
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
            dll_delete_node(node);

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