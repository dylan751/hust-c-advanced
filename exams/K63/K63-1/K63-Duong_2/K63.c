#include "cgraph/cgraph.h"
#include <stdio.h>
#include <stdio_ext.h>

typedef struct {
    int id;
    char name[40];
} vertex;

int main() {
    cgraph_t g;
    cgraph_ivec_t edges = cgraph_ivec_create();
    cgraph_ivec_t neis = cgraph_ivec_create();
    cgraph_rvec_t weights = cgraph_rvec_create();

    cgraph_ivec_t dist = cgraph_ivec_create();
    cgraph_ivec_t father = cgraph_ivec_create();

    int num_v, num_e;  
    vertex vertexes[40]; 

    char choice;
    while(1){
        printf("            ---MENU---\n"
               "|1. In danh sach dinh.           |\n"
               "|2. Tim ban than thiet nhat.     |\n"
               "|3. Kiem tra quan he bac cau.    |\n"
               "|4. Tim ban chung.               |\n"
               "|5. Thoat chuong trinh.          |\n");

        __fpurge(stdin);
        printf("Input your choice: ");
        scanf("%c", &choice);

        while(choice > '5' || choice < '1'){
            __fpurge(stdin);
            printf("Ivalid! Input your choice again: ");
            scanf("%c", &choice);
        }

        switch(choice) {
            case '1': {
                FILE* fptr = fopen("data.txt", "r");
                fscanf(fptr, "%d %d", &num_v, &num_e);
                for(int i = 0; i < num_v; i++) {
                    fscanf(fptr, "%d %s", &vertexes[i].id, vertexes[i].name);
                }

                int id1, id2;
                double w;
                for(int i = 0; i < num_e; i++) {
                    fscanf(fptr, "%d %d %lf", &id1, &id2, &w);
                    cgraph_ivec_push_back(&edges, id1);
                    cgraph_ivec_push_back(&edges, id2);
                    cgraph_rvec_push_back(&weights, w);
                }
                g = cgraph_create(edges, 0, false);
                // cgraph_print(g);
                // cgraph_rvec_print(weights);
                
                /* -------------- DUNG BFS DUYET DO THI ---------------- */
                cgraph_simple_bfs(g, 0, CGRAPH_ALL, 1, &father, &dist);

                for(int i = 0; i < cgraph_ivec_size(dist); i++) {
                    if(dist[i] >= 0) {
                        printf("%d %s\n", vertexes[i].id, vertexes[i].name);
                    }
                }

                
                fclose(fptr);
                break;
            }

            case '2': {
                int id_temp;
                printf("Nhap id cua mot nguoi: ");
                scanf("%d", &id_temp);
                while(id_temp <= 0 || (id_temp > 5 && id_temp < 10) || id_temp > 10) {
                    printf("Id khong ton tai! Nhap lai: ");
                    scanf("%d", &id_temp);
                }

                cgraph_neighbors(g, &neis, id_temp, CGRAPH_ALL);
                /* ------------------------ TIM NEIGHBOUR THAN THIET NHAT  ---------------------- */
                double max = 0;
                for(int i = 0; i < cgraph_ivec_size(neis); i++) {
                    for(int j = 0; j < num_e; j++) {
                        if((g->from[j] == id_temp && g->to[j] == neis[i]) || (g->from[j] == neis[i] && g->to[j] == id_temp)) {
                            max = max > weights[j] ? max: weights[j];
                        }
                    }
                }

                /* -------------------------- IN RA MUC DO THAN THIET LON NHAT -------------------- */
                printf("%.2lf\n", max);

                /* --------------------------- IN RA NHUNG BAN THAN NHAT -------------------------- */
                for(int i = 0; i < num_v; i++) {
                    if(weights[i] == max) {
                        if(g->from[i] == id_temp) {
                            printf("%d %s\n", vertexes[g->to[i]-1].id, vertexes[g->to[i]-1].name);
                        }
                        if(g->to[i] == id_temp) {
                            printf("%d %s\n", vertexes[g->from[i]-1].id, vertexes[g->from[i]-1].name);
                        }
                    }
                }
                break;
            }

            case '3': {
                int id_temp_1, id_temp_2;
                printf("Nhap vao id cua 2 nguoi: ");
                scanf("%d%d", &id_temp_1, &id_temp_2);

                /* -------------- DUNG BFS DUYET DO THI ---------------- */
                cgraph_simple_bfs(g, id_temp_1, CGRAPH_ALL, 1, &father, &dist);
                
                // dist[i] luu khoang cach tu dinh i -> id_temp_1
                if(dist[id_temp_2] >= 2) { // Co duong di nhung khong ke nhau
                    printf("1\n");
                } else {
                    printf("-1\n");
                }

                break;
            }

            case '4': {
                int count = 0;
                int id_temp_1, id_temp_2;
                printf("Nhap vao id cua 2 nguoi: ");
                scanf("%d%d", &id_temp_1, &id_temp_2);

                cgraph_ivec_t neis_1 = cgraph_ivec_create();
                cgraph_ivec_t neis_2 = cgraph_ivec_create();
                cgraph_neighbors(g, &neis_1, id_temp_1, CGRAPH_ALL);
                cgraph_neighbors(g, &neis_2, id_temp_2, CGRAPH_ALL);

                for(int i = 0; i < cgraph_ivec_size(neis_1); i++) {
                    for(int j = 0; j < cgraph_ivec_size(neis_2); j++) {
                        if(neis_2[j] == neis_1[i]) {
                            count++;
                            printf("%d %s\n", vertexes[neis_1[i]-1].id, vertexes[neis_1[i]-1].name);
                        }
                    }
                }
                printf("%d\n", count);

                cgraph_ivec_free(&neis_1);
                cgraph_ivec_free(&neis_2);
                break;
            }

            case '5': {
                cgraph_destroy(&g);

                cgraph_ivec_free(&edges);
                cgraph_ivec_free(&neis);
                cgraph_ivec_free(&father);
                cgraph_ivec_free(&dist);

                cgraph_rvec_free(&weights);

                exit(0);
                break;
            }
        }
    }
    return 0;
}