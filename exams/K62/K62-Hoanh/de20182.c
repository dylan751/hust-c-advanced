#include "graph_by_jrb_with_ID.h"

#include <stdio.h>

double shortestPath_s_To_t_by_foot(Graph g, int s, int t, int* p ){
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
                    if(d[v] > d[u] + w && w >= 50){
                        d[v] = d[u] + w;
                        p[v]  = u;
                    }
                }
            }

       }
    return d[t];
}
void import_edges(Graph g, int ed_num, FILE* fptr){
    int id1, id2;
    double weight;

    for(int i =0; i< ed_num; i++){
       fscanf(fptr, "\n%d %d %lf", &id1, &id2, &weight); 
       addEdge(g, id2, id1, weight);
       addEdge(g, id1, id2, weight);
       addVertex(g, id1, (char*)id1);
       addVertex(g, id2, (char*)id2);
    }
}
void print_vertex(Graph g, int ver_num){
    for(int i = 1; i <= ver_num; i ++){
        for(int j = 1; j<= ver_num; j++){
            if(getEdgeValue(g, i, j) != INFINITIVE_VALUE) printf("%4d",1);
            else printf("%4d", 0);
        }
        printf("\n");
    }
    
}
void print_tower_near_list(Graph g, int ver_num){
    for(int i = 1; i <= ver_num; i ++){
        int list[ver_num];
        int n = outdegree(g, i, list);
        printf("\nCastle %d :_", i);
        for( int j = 0; j < n; j++){
            printf("%4d", list[j]);
        }
    }
    printf("\n");
}
void how_to_go_by_foot(Graph g, int ver_num){
    int tower[ver_num];
    int count = 0;
    
    for(int i = 1; i <= ver_num; i ++){
        int dem = 0;
        int output[ver_num];
        int n = outdegree(g, i, output);
        //printf("%d\n", n);
        for(int j = 0; j < n; j++){
            //printf("%.1lf\n", getEdgeValue(g, i, output[j]));
            if(getEdgeValue(g, output[j], i) < 50) dem = INFINITIVE_VALUE;
            
        }
        if(dem != INFINITIVE_VALUE) {
            tower[count] = i; 
            count ++;
        }
    }
    //printf("%d", count);
    if(count == 0) printf("Ko co thanh tri co the di truc tiep den no bang cach di bo !\n");
    else {
        printf("Cac thanh tri co the den truc tiep bang di bo la :\n");
        for(int i =0; i< count; i ++) printf("%4d", tower[i]);
    }
    printf("\n");
}
void print_most_road(Graph g, int ver_num){
    int max = 0;
    int n;
    int output[ver_num];
    for(int i = 1; i <= ver_num; i ++){
        
        n = indegree(g, i, output);
        if(max < n) max = n;
        //printf("%d\n", n);
        
    }
    printf("Cac toa thanh co nhieu duong di den no nhat la :\n");
    for(int i = 1; i <= ver_num; i++){
        n = indegree(g, i, output);
        if(n == max) printf("%4d", i);
    }
    printf("\n");
}
int main(){
    int choice = 0;
    Graph g = createGraph();
    int ver_num, ed_num;
    FILE * fptr = fopen("../dothi.txt", "r");
    fscanf(fptr, "%d %d\n" ,&ver_num, &ed_num);
    int i, tower1, tower2;
    
    //import_vertex(g, ver_num, fptr, person);
    import_edges(g,ed_num, fptr);
    while(choice != 6){
    printf(" ---Menu---\n"
     "|1. In ra ma tran do thi .             |\n"
     "|2. In ra danh sach thanh tri lien ke. |\n"
     "|3. Go only by foot/ have most road    |\n"
     "|4. Shortest Path tower 1 and tower 2  |\n"
     "|5. Shortest Path go by foot           |\n"
     "|6. Exit.                              |\n");
    printf("Nhap lua chon cua ban : ");
    scanf("%d", &choice);
    switch(choice){
    case 1 :{
      print_vertex(g, ver_num); 
      break;
    }
    case 2 :{
      print_tower_near_list(g, ver_num);
      
      break;
    }
    case 3 :{
      how_to_go_by_foot(g, ver_num);
      print_most_road(g, ver_num);
      break;
    }
    case 4 :{
      
      printf("Enter start tower and finish tower :\n");
      scanf("%d %d", &tower1, &tower2);
      int output[ver_num];
      double time = shortestPath_s_To_t(g, tower1, tower2, output);
      if(time == INFINITIVE_VALUE) printf("Route not found\n");
      else {
        printf("Thoi gian ngan nhat di tu tower %d den tower %d la :__", tower1, tower2);
        printf("%.0lf\n", time);
        printf("Nguoi dua thu can di theo tuyen duong :\n");
        i = tower2;
        do{
            printf("%d <== ", i);  
            i = output[i];                       
        }
        while(i != tower1);
        printf("%d\n", tower1);
      }
      break;
    }
    case 5 :{
      
      printf("Enter start tower and finish tower :\n");
      scanf("%d %d", &tower1, &tower2);
      int output[ver_num];
      double time = shortestPath_s_To_t_by_foot(g, tower1, tower2, output);
      if(time == INFINITIVE_VALUE) printf("Route not found\n");
      else {
        printf("Thoi gian di bo ngan nhat di tu tower %d den tower %d la :__", tower1, tower2);
        printf("%.0lf\n", time);
        printf("Nguoi dua thu can di theo tuyen duong :\n");
        i = tower2;
        do{
            printf("%d <== ", i);  
            i = output[i];                       
        }
        while(i != tower1);
        printf("%d\n", tower1);
      }
      break;
    }
    }
    }
    fclose(fptr);
}
