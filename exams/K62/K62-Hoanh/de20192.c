#include <stdio.h>
#include <string.h>
#include "graph_by_jrb_with_ID.h"

typedef struct {
    int id;
    char ten[100];
} name;
void import_vertex(Graph g, int ver_num, FILE* fptr ,name *per){
    for(int i = 0; i < ver_num ; i++){
        fscanf(fptr, "%d %s\n", &per[i].id, per[i].ten);
        addVertex(g, per[i].id, per[i].ten);
    }
}
void import_edges(Graph g, int ed_num, FILE* fptr){
    int id1, id2;
    double weight;

    for(int i =0; i< ed_num; i++){
       fscanf(fptr, "\n%d %d %lf", &id1, &id2, &weight); 
       addEdge(g, id2, id1, weight);
       addEdge(g, id1, id2, weight);
       
    }
}
void print_vertex(Graph g, name* per, int num){
    // for(int i = 0; i < num; i++){
    //     printf("%d : %s\n", per[i].id, getVertex(g, per[i].id));
    // }
    for(int i = 0; i < num; i++){
        printf("%d : %s\n", jval_i(getfullItemVertex(g, per[i].id)->key), jval_s(getfullItemVertex(g, per[i].id)->val));
    }
}

int bac_cau(Graph g, int id1, int id2){
    double w;
    int p[10];
    if(getEdgeValue(g, id1, id2) != INFINITIVE_VALUE || jrb_find_int(g.edges, id1) == NULL|| jrb_find_int(g.edges, id2) == NULL ) return -1; // graph co canh v1 v2 / graph ko co id1 / graph ko co id2
    else {
        w = shortestPath_s_To_t(g, id1, id2, p);
        if(w >0 && w != INFINITIVE_VALUE) return 1;
        else return -1;
    }
}
int tim_ban_chung(Graph g, int id1, int id2){
    int p[10];
    double w;
    int ke1_num, ke2_num, chung; // so dinh ke id1 va so dinh ke id2 va so ban chung cua ca 2
    int list_ke1[10] = {0}, list_ke2[10] = {0}, count = 0;
    if(jrb_find_int(g.edges, id1) == NULL|| jrb_find_int(g.edges, id2) == NULL ) printf ("\n-1\n");
    else {
        w = shortestPath_s_To_t(g, id1, id2, p);  
        if(w == INFINITIVE_VALUE) printf ("\n-1\n"); // neu ko co duong di tu id1 -> id2  => ko co ban chung
        else {
            ke1_num = outdegree(g, id1, list_ke1);
            ke2_num = outdegree(g, id2, list_ke2);
            for(int i = 0; i < ke1_num; i++ ){
                for(int j = 0; j < ke2_num; j++){
                    if(list_ke1[i] == list_ke2[j] && list_ke1[i]!= id2){
                        printf("\n\n%d \t %s\n", list_ke1[i], getVertex(g, list_ke1[i]));
                        count ++;
                    }
                }
            }
            if(count == 0 ) printf("\n-1\n");
            else printf("\nTong so ban chung cua ca 2 la : %d\n", count);
        }
    }
}
void find_best_friend(Graph graph, int v1){
    JRB node, tree;
    int output[100];
    int i, n;
    double max , sosanh[10] = {0};
    node = getfullItemVertex(graph, v1);
    if(node ==  NULL) {
        printf("This id is not available in the graph !\n"); // neu dinh ko ton tai
        return;
    }
    n = outdegree(graph, v1, output);
    if (n != 0){
    for( i = 0; i< n ; i++){
        sosanh[i] = getEdgeValue(graph, v1, output[i]);
        //printf("%lf\t",sosanh[i]);
    }
    printf("\n");
    max = sosanh[0];
    for(int i = 0; i < n; i++){
       if(sosanh[i]<sosanh[i+1]){
            max = sosanh[i +1];
       }
    }
    printf("%lf\n", max);
    for (i = 0; i < n; i++){
        
        if(sosanh[i] == max) 
        printf("%d : %s\n", jval_i(getfullItemVertex(graph, output[i])->key), jval_s(getfullItemVertex(graph , output[i])->val));
    }
    }
    else printf("Ban %s ko co ban than =(( ( theo de bai thi in ra -1)\n", getVertex(graph, v1));
}
int main(){
    int choice = 0;
    Graph g = createGraph();
    int ver_num, ed_num;
    FILE * fptr = fopen("../data.txt", "r");
    fscanf(fptr, "%d %d\n" ,&ver_num, &ed_num);
    name person[ver_num];
    int i, id1,id2;
    int id_choice;
    import_vertex(g, ver_num, fptr, person);
    import_edges(g,ed_num, fptr);
    while(choice != 5){
    printf(" ---Menu---\n"
     "|1. In danh sach dinh .        |\n"
     "|2. Tim ban than thiet nhat .  |\n"
     "|3. Kiem tra quan he bac cau . |\n"
     "|4. Tim ban chung.             |\n"
     "|5. Exit.                      |\n");
    printf("Nhap lua chon cua ban : ");
    scanf("%d", &choice);
    switch(choice){
    case 1 :{
      print_vertex(g, person, ver_num); 
      break;
    }
    case 2 :{
      printf("Enter person's ID :");
      scanf("%d", &id_choice);
      find_best_friend(g, id_choice);
      break;
    }
    case 3 :{
      printf("Enter 2 ID to check : \n");
      scanf("%d %d",&id1, &id2);
      printf("\n%d\n\n", bac_cau(g, id1, id2));
      break;
    }
    case 4 :{
      printf("Enter 2 ID to check : \n");
      scanf("%d %d",&id1, &id2);
      tim_ban_chung(g, id1,id2);
      break;
    }
    }
    }
    fclose(fptr);
}