/*
  Menu: 1. Nhập tên hàm và in ra danh sách các hàm gọi nó -> Nếu không tồn tại thì in ra
  Menu: 2. In ra một trật tự hoàn thành các hàm
  Menu: 3. Kiểm tra có phải DAG hay không. Nếu có thì in ra "Là DAG", nếu không thì in ra "Không phải DAG"
*/
/*BTVN: Up bài vào w14-5 -> Homework*/

#include "cgraph/cgraph.h"
#include "cgen/s2i.h"
#include "cgen/svector.h"

#include <stdlib.h>

#include <stdio.h>

bn_tree_t s2i = NULL;
vector_t i2s = NULL;

int get_save_id(char *key) {
    int id = s2i_value(s2i, key);    //search
    if(id != k_s2i_invalid) {        //Nếu tìm thấy -> return
        return id;                 
    }                   
    svec_push_back(&i2s, key);
    id = gtv_size(i2s) - 1;
    s2i_insert(s2i, key, id);       //Nếu không tìm thấy -> insert
    return id;
}

int main(){
    s2i = s2i_create();  //String to int
    i2s = gtv_create();  //Int to string
    FILE *fptr = NULL;
    cgraph_ivec_t edges = cgraph_ivec_create();

    fptr = fopen("input.txt", "r");
    if(fptr == NULL){
        printf("Cannot open input.txt!\n");
        return -1;
    }

    int d;//number of edges
    fscanf(fptr, "%d", &d);
    char u[100], v[100];
    for(int i = 0; i < d; i++){
        fscanf(fptr, "%s %s", u, v);
        int uid = get_save_id(u);
        int vid = get_save_id(v);
        cgraph_ivec_push_back(&edges, uid);
        cgraph_ivec_push_back(&edges, vid);
    }
    fclose(fptr);

    cgraph_t g = cgraph_create(edges, 0, CGRAPH_DIRECTED);

    int choice;
    printf("               ---------MENU---------                 \n"
           "|1. Nhập tên hàm và in ra danh sách các hàm gọi nó.  |\n"
           "|2. In ra một trật tự hoàn thành các hàm.            |\n"
           "|3. Kiểm tra danh sách có là một DAG.                |\n"
           "|4. Thoát.                                           |\n");
    
    while(1){
        printf("Input choice: ");
        scanf("%d", &choice);
        switch(choice){
            case 1: {
                printf("Input a vertex: ");
                scanf("%s", u);
                int uid = s2i_value(s2i, u);
                cgraph_ivec_t father = cgraph_ivec_create(),
                              dist = cgraph_ivec_create();
                cgraph_simple_bfs(g, uid, CGRAPH_IN, false, &father, &dist);
                printf("Các hàm gọi tới %s: ", u);
                for(int i = 0; i < cgraph_ivec_size(dist); i++) {
                    if(dist[i] > 0) {
                        printf("%s ", i2s[i]);
                    }
                }
                printf("\n");
                break;
            }

            case 2: {
                cgraph_topological_sorting(g, &edges, CGRAPH_OUT);
                printf("Topo: ");
                for(int i = 0; i < cgraph_ivec_size(edges); i++){
                    printf("%s -> ", i2s[edges[i]]);
                }
                printf("\n");
                break;
            }
            case 3: {
                if(cgraph_is_dag(g)) printf("La DAG\n");
                else printf("Khong la DAG\n");
                break;
            }
            case 4: {
                exit(0);
                break;
            }
            default: {
                printf("Invalid input! try again!\n");
            }
        }
    }

    cgraph_destroy(&g);
    s2i_free(&s2i);
    gtv_free(&i2s);
    return 0;
}

