#include <stdio.h>
#include <stdio_ext.h>

#include "cgraph/cgraph.h"

int main() {
    char choice;
    cgraph_ivec_t edges = cgraph_ivec_create();
    cgraph_rvec_t weights = cgraph_rvec_create();
    cgraph_ivec_t neis = cgraph_ivec_create();

    cgraph_t g;
    int num_v, num_e, i, j;

    while(1){
        printf("             ---------------MENU---------------\n"
           "|1. Doc tu file dothi.txt.                                                |\n"
           "|2. In ra danh sach ke cua moi thanh tri.                                 |\n"
           "|3. a) Dua ra danh sach thanh tri co the den truc tiep bang cach di bo.   |\n"
           "|   b) Dua ra thanh tri co bac vao lon nhat.                              |\n"
           "|4. Tim duong di ngan nhat tu thanh tri s -> t.                           |\n"
           "|5. Tim duong di bo ngan nhat tu thanh tri s -> t.                        |\n"
           "|6. Exit.                                                                 |\n");

        __fpurge(stdin);
        printf("Input your choice: ");
        scanf("%c", &choice);

        while(choice > '6' || choice < '1'){
            __fpurge(stdin);    
            printf("Ivalid! Input your choice: ");
            scanf("%c", &choice);
        }

        switch(choice){
        case '1':{
            char s1[40], s2[40];
            int a, b; 
            double w;//Weight
            FILE* fptr = fopen("dothi.txt", "r");
            fscanf(fptr, "%d %d", &num_v, &num_e);
            for(i = 0; i < num_e; i++) {
                // fscanf(fptr, "%s %s %d", s1, s2, &w);
                // int s1_id = get_save_id(s1);
                // int s2_id = get_save_id(s2);

                // cgraph_ivec_push_back(&edges, s1_id);
                // cgraph_ivec_push_back(&edges, s2_id);
                fscanf(fptr, "%d %d %lf", &a, &b, &w);
                cgraph_ivec_push_back(&edges, a);
                cgraph_ivec_push_back(&edges, b);
                cgraph_rvec_push_back(&weights, w);
            }

            g = cgraph_create(edges, 0, false);
            
            int res[100][100] = {0}; //Ma tran ke ket qua
            printf("---Ma tran ke---\n");
            for(i = 0; i < num_e; i++) {
                for(j = 0; j < num_e; j++) {
                    res[g->from[j] - 1][g->to[j] - 1] = 1;
                    res[g->to[j] - 1][g->from[j] - 1] = 1;
                }
            }

            for(i = 0; i < num_v; i++) {
                for(j = 0; j < num_v; j++) {
                    printf("%d ", res[i][j]);
                }
                printf("\n");
            }

            fclose(fptr);
            break;
        }

        case '2':{
            printf("---Danh sach ke cua moi thanh tri---\n");
            for(i = 0; i < num_v; i++) {
                cgraph_neighbors(g, &neis, i+1, CGRAPH_ALL);
                printf("Castle %d: ", i+1);
                for(j = 0; j < cgraph_ivec_size(neis); j++) {
                    printf("%d ", neis[j]);
                }
                printf("\n");
            }
            break;
        }

        case '3':{
            int mark = 0;
            int weight_tmp[10];

            printf("a) Danh sach cac thanh tri chi co the den no truc tiep bang cach di bo: ");

            /*---------------------Tim castle nao co weight cua tat ca neighbour > 50 -> In ra--------------------*/
            for(i = 0; i < num_v; i++) {
                mark = 0;
                cgraph_neighbors(g, &neis, i+1, CGRAPH_ALL);
                for(j = 0; j < num_e; j++) {
                    for(int k = 0; k < cgraph_ivec_size(neis); k++) {
                        if((g->from[j] == i+1 && g->to[j] == neis[k]) || (g->to[j] == i+1 && g->from[j] == neis[k])) {
                            if(weights[j] < 50) { //Nghia la phai di ngua
                                mark = 1; //Khong thoa man dieu kien
                            }   
                        }
                    }
                }

                if(mark == 0) {
                    printf("%d ", i+1);
                }
            }
            printf("\n");

            /*---------------------Tim castle co indeg lon nhat-------------------*/
            printf("\nb) Cac thanh co bac vao (indeg) lon nhat: ");
            int max;       

            cgraph_ivec_t res = cgraph_ivec_create();
            cgraph_degree_all(g, &res, CGRAPH_ALL, 0);
            max = res[1]; //Khoi tao max = so neighbour cua castle 1

            /*--------------------Tim so neighbour lon nhat trong cac castle---------------*/
            for(i = 1; i < cgraph_ivec_size(res); i++) {
                max = max > res[i+1] ? max : res[i+1];
            }

            /*---------------------In ra ket qua------------------*/
            for(i = 0; i < cgraph_ivec_size(res); i++) {
                if(max == res[i]) {
                    printf("%d ", i);
                }
            }
            printf("\n");

            cgraph_ivec_free(&res);
            break;
        }

        case '4':{
            int s, t;
            printf("Nhap thanh tri xuat phat: ");
            scanf("%d", &s);
            while(s < 1 || s > 8) {
                printf("Hay chon thanh 1 -> 8!\nChon lai: ");
                scanf("%d", &s);
            }
            printf("Nhap thanh tri dich: ");
            scanf("%d", &t);
            while(t < 1 || t > 8) {
                printf("Hay chon thanh 1 -> 8!\nChon lai: ");
                scanf("%d", &t);
            }

            cgraph_ivec_t vpath = cgraph_ivec_create();
            cgraph_ivec_t epath = cgraph_ivec_create();

            int is_path;  
            /*is_path = 0 -> Co duong, is_path = -1 -> khong co duong*/
            is_path = cgraph_get_shortest_path_dijkstra(g, &vpath, &epath, s, t, weights, CGRAPH_ALL);

            // for(i = 0; i < cgraph_ivec_size(epath); i++) {
            //     printf("\n%d\n", epath[i]);
            // }

            if(is_path == -1) {
                printf("Khong co duong di tu %d den %d\n", s, t);
                break;
            }
            int length = 0;
            for(int i = 0; i < cgraph_ivec_size(epath); i++){
                length += weights[epath[i]];
            }
            printf("\nDo dai duong di: %d\n", length);
            printf("Cac thanh tri phai di qua: ");
            for(i = 0; i < cgraph_ivec_size(vpath); i++) {
                printf("%d ", vpath[i]);
            }
            printf("\n");

            cgraph_ivec_free(&epath);
            cgraph_ivec_free(&vpath);
            break;
        }

        case '5':{
            /*------------TAO 1 DO THI CHI CHUA CAC CANH CO WEIGHT >= 50 TU FILE INPUT------------*/
            cgraph_ivec_t edges_diBo = cgraph_ivec_create();
            cgraph_rvec_t weights_diBo = cgraph_rvec_create();
            
            for(i = 0; i < cgraph_ivec_size(weights); i++) {
                if(weights[i] >= 50) {
                    cgraph_ivec_push_back(&edges_diBo, edges[2*i]);
                    cgraph_ivec_push_back(&edges_diBo, edges[2*i + 1]);
                    cgraph_rvec_push_back(&weights_diBo, weights[i]);
                }
            }
 
            cgraph_t g_diBo;
            g_diBo = cgraph_create(edges_diBo, 0, false);
            
            /*---------------SU DUNG DIJKSTRA DE TIM DUONG----------------*/
            int s, t;
            printf("Nhap thanh tri xuat phat: ");
            scanf("%d", &s);
            while(s < 1 || s > 8) {
                printf("Hay chon thanh 1 -> 8!\nChon lai: ");
                scanf("%d", &s);
            }
            printf("Nhap thanh tri dich: ");
            scanf("%d", &t);
            while(t < 1 || t > 8) {
                printf("Hay chon thanh 1 -> 8!\nChon lai: ");
                scanf("%d", &t);
            }

            cgraph_ivec_t vpath = cgraph_ivec_create();
            cgraph_ivec_t epath = cgraph_ivec_create();

            int is_path;  
            /*is_path = 0 -> Co duong, is_path = -1 -> khong co duong*/
            is_path = cgraph_get_shortest_path_dijkstra(g_diBo, &vpath, &epath, s, t, weights_diBo, CGRAPH_ALL);

            if(is_path == -1) {
                printf("Khong co duong di tu %d den %d\n", s, t);
                break;
            }
            int length = 0;
            for(int i = 0; i < cgraph_ivec_size(epath); i++){
                length += weights_diBo[epath[i]];
            }
            printf("\nDo dai duong di: %d\n", length);
            printf("Cac thanh tri phai di bo qua: ");
            for(i = 0; i < cgraph_ivec_size(vpath); i++) {
                printf("%d ", vpath[i]);
            }
            printf("\n");

            cgraph_ivec_free(&epath);
            cgraph_ivec_free(&vpath);
            cgraph_ivec_free(&edges_diBo);
            cgraph_rvec_free(&weights_diBo);
            cgraph_destroy(&g_diBo);
            break;
        }

        case '6':{
            cgraph_rvec_free(&weights);
            cgraph_ivec_free(&edges);
            cgraph_ivec_free(&neis);
            cgraph_destroy(&g);
            exit(0);
            break;
        }

        }
    }
    return 0;
}