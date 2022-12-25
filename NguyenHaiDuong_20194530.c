#include "cgraph/cgraph.h"
#include "cgen/svector.h"
#include "cgen/s2i.h"

#include <string.h>
#include <stdio.h>
#include <stdio_ext.h>

bn_tree_t s2i = NULL;
vector_t i2s = NULL;

int g_id = 0;

int get_save_id(char *key) {
    int res = s2i_value(s2i, key);    //search
    if(res != k_s2i_invalid) {        //Nếu tìm thấy -> return
        return res;                 
    }                   
    s2i_insert(s2i, key, g_id);       //Nếu không tìm thấy -> insert
    svec_push_back(&i2s, key);
    res = g_id;
    ++g_id;
    return res;
}

typedef struct {
    int id;
    char CCCD[20];
    char soDT[20];
    char name[50];
} vertex;

typedef struct {
    char thoiGian[20];
} edge;

int main() {
    char choice;
        
    cgraph_ivec_t edges = cgraph_ivec_create();
    cgraph_ivec_t neis = cgraph_ivec_create();
    cgraph_ivec_t father = cgraph_ivec_create();
    cgraph_ivec_t dist = cgraph_ivec_create();
    cgraph_t g = NULL;

    int num_v, num_e;
    vertex V[20];
    edge E[20];

    while(1){
        printf("            ---MENU---\n"
               "|1. Doc file.                     |\n"
               "|2. Dang ki 1 cong dan moi.       |\n"
               "|3. Ghi nhan tiep xuc.            |\n"
               "|4. Tra cuu cong dan.             |\n"
               "|5. Tra cuu thong tin tiep xuc.   |\n"
               "|6. Tra cuu mang luoi tiep xuc.   |\n"
               "|7. Thoat chuong trinh.           |\n");

        __fpurge(stdin);
        printf("Input your choice: ");
        scanf("%c", &choice);

        while(choice > '7' || choice < '1'){
            __fpurge(stdin);
            printf("Ivalid! Input your choice again: ");
            scanf("%c", &choice);
        }

        switch(choice) {
        case '1': {
            FILE* fptr1 = fopen("dancu.txt", "r");
            if(fptr1 == NULL) {
                printf("Cannot open dancu.txt!\n");
            }
            FILE* fptr2 = fopen("tiepxuc.txt", "r");
            if(fptr2 == NULL) {
                printf("Cannot open tiepxuc.txt!\n");
            }

            /* Doc FILE dancu.txt */
            fscanf(fptr1, "%d", &num_v);
            for(int i = 0; i < num_v; i++) {
                fscanf(fptr1, "%s %s %s", V[i].CCCD, V[i].soDT, V[i].name);
                V[i].id = i;
            }

            /* Doc FILE tiepxuc.txt */
            char s1[20], s2[20];
            int s1_id, s2_id;
            fscanf(fptr2, "%d", &num_e);
            for(int i = 0; i < num_e; i++) {
                fscanf(fptr2, "%s %s %s", s1, s2, E[i].thoiGian);
                for(int j = 0; j < num_v; j++) {
                    if(strcmp(V[j].CCCD, s1) == 0) {
                        s1_id = j;
                    }
                    if(strcmp(V[j].CCCD, s2) == 0) {
                        s2_id = j;
                    }
                }
                cgraph_ivec_push_back(&edges, s1_id);
                cgraph_ivec_push_back(&edges, s2_id);
            }

            g = cgraph_create(edges, num_v, false);
            printf("So dinh: %d\n", cgraph_vcount(g));
            printf("So canh: %d\n", cgraph_ecount(g));


            fclose(fptr1);
            fclose(fptr2);
            break;
        }

        case '2': {
            int mark = 0;
            char CCCD_inp[20], soDT_inp[20], name_inp[50];
            printf("Nhap CCCD: ");
            scanf("%s", CCCD_inp);
            printf("Nhap so dien thoai: ");
            scanf("%s", soDT_inp);
            printf("Nhap ten: ");
            scanf("%s", name_inp);

            for(int i = 0; i < num_v; i++) {
                if(strcmp(CCCD_inp, V[i].CCCD) == 0) { // Da ton tai CCCD trong CSDL
                    mark = 1;
                    strcpy(V[i].soDT, soDT_inp);
                    strcpy(V[i].name, name_inp);
                    printf("Cap nhat thong tin!\n");
                }
            }

            if(mark == 0) { // Chua ton tai CCCD trong CSDL
                // Them vao mang
                V[num_v].id = num_v;
                strcpy(V[num_v].CCCD, CCCD_inp);
                strcpy(V[num_v].soDT, soDT_inp);
                strcpy(V[num_v].name, name_inp);
                num_v++;

                // Them vao do thi
                cgraph_add_vertices(g, V[num_v-1].id);

                printf("Them cong dan!\n");
            }

            printf("So ban ghi cong dan: %d\n", num_v);
            break;
        }

        case '3': {
            int mark = 0, mark_1 = 0, mark_2 = 0;
            char CCCD_inp_1[20], CCCD_inp_2[20], thoiGian_inp[20];
            printf("Nhap CCCD nguoi 1: ");
            scanf("%s", CCCD_inp_1);

            for(int i = 0; i < num_v; i++) {
                if(strcmp(CCCD_inp_1, V[i].CCCD) == 0) { // Nguoi 2 da ton tai CCCD trong CSDL
                    mark_1 = 1;
                }
            }

            if(mark_1 == 0) { // Nguoi 1 chua ton tai CCCD trong CSDL
                printf("Nguoi 1 khong ton tai! Nhap lai: ");
                scanf("%s", CCCD_inp_1);
            }

            printf("Nhap CCCD nguoi 2: ");
            scanf("%s", CCCD_inp_2);

            for(int i = 0; i < num_v; i++) {
                if(strcmp(CCCD_inp_2, V[i].CCCD) == 0) { // Nguoi 1 da ton tai CCCD trong CSDL
                    mark_2 = 1;
                }
            }

            if(mark_2 == 0) { // Nguoi 2 chua ton tai CCCD trong CSDL
                printf("Nguoi 2 khong ton tai! Nhap lai: ");
                scanf("%s", CCCD_inp_2);
            }

            printf("Nhap thoi gian tiep xuc (DDMMYYYY): ");
            scanf("%s", thoiGian_inp);

            // Tim neighbour cua nguoi 1
            int dangXet;
            for(int i = 0; i < num_v; i++) {
                if(strcmp(V[i].CCCD, CCCD_inp_1) == 0) {
                    dangXet = i;    // Luu id cua dinh dang xet
                    cgraph_neighbors(g, &neis, i, CGRAPH_ALL);
                }
            }

            // Xem nguoi 1 vs nguoi 2 tiep xuc chua
            for(int i = 0; i < cgraph_ivec_size(neis); i++) {
                for(int j = 0; j < num_v; j++) {
                    if(strcmp(V[neis[i]].CCCD, CCCD_inp_2) == 0) { // Da tiep xuc truoc do
                        mark = 1;

                        // Cap nhat thoi gian tiep xuc
                        for(int k = 0; k < num_e; k++) {
                            if((g->from[k] == dangXet && g->to[k] == neis[i]) || (g->from[k] == neis[i] && g->to[k] == dangXet)) {
                                strcpy(E[k].thoiGian, thoiGian_inp);
                            }
                        }
                    }
                }
            }

            if(mark == 0) { // Chua tiep xuc truoc do
                cgraph_ivec_t edges_add = cgraph_ivec_create();
                for(int i = 0; i < num_v; i++) {
                    if(strcmp(V[i].CCCD, CCCD_inp_1) == 0) {
                        cgraph_ivec_push_back(&edges_add, V[i].id);
                    }
                    if(strcmp(V[i].CCCD, CCCD_inp_2) == 0) {
                        cgraph_ivec_push_back(&edges_add, V[i].id);
                    }
                }

                cgraph_add_edges(g, edges_add);

                printf("Them tiep xuc!\n");
            }

            break;
        }

        case '4': {
            int mark = 0;
            char CCCD_inp[20];
            printf("Nhap CCCD: ");
            scanf("%s", CCCD_inp);

            for(int i = 0; i < num_v; i++) {
                if(strcmp(CCCD_inp, V[i].CCCD) == 0) { // Da ton tai CCCD trong CSDL
                    mark = 1;
                    printf("Ho ten: %s\n", V[i].name);
                    printf("Sdt: %s\n", V[i].soDT);
                }
            }

            if(mark == 0) { // Chua ton tai CCCD trong CSDL
                printf("Khong ton tai!\n");
            }

            break;
        }

        case '5': {
            int mark = 0;
            char CCCD_inp[20];
            printf("Nhap CCCD: ");
            scanf("%s", CCCD_inp);

            for(int i = 0; i < num_v; i++) {
                if(strcmp(CCCD_inp, V[i].CCCD) == 0) { // Da ton tai CCCD trong CSDL
                    mark = 1;
                    cgraph_neighbors(g, &neis, i, CGRAPH_ALL);

                    if(cgraph_ivec_size(neis) == 0) {
                        printf("Khong co tiep xuc!\n");
                    } else{
                        printf("--- Danh sach nguoi tiep xuc truc tiep ---\n");
                        for(int j = 0; j < cgraph_ivec_size(neis); j++) {
                            printf("Ho ten: %s\n", V[neis[j]].name);
                            printf("CCCD: %s\n", V[neis[j]].CCCD);
                            printf("Sdt: %s\n", V[neis[j]].soDT);
                            printf("Thoi gian tiep xuc: %s\n\n", E[j].thoiGian);
                        }
                    }
                }
            }

            if(mark == 0) { // Chua ton tai CCCD trong CSDL
                printf("Khong ton tai!\n");
            }
            break;
        }

        case '6': {
            int mark = 0;
            char CCCD_inp[20];
            printf("Nhap CCCD: ");
            scanf("%s", CCCD_inp);

            for(int i = 0; i < num_v; i++) {
                if(strcmp(CCCD_inp, V[i].CCCD) == 0) { // Da ton tai CCCD trong CSDL
                    mark = 1;
                    cgraph_simple_bfs(g, i, CGRAPH_ALL, 0, &father, &dist);

                    for(int k = 0; k < cgraph_ivec_size(dist); k++) {
                        if(dist[i] != 0) {
                            mark = 0;   // Khong co tiep xuc -> thay doi mark = 0
                        }
                    }
                    if(mark == 1) {
                        printf("Khong co tiep xuc!\n");
                    } else {
                        printf("--- Danh sach tiep xuc truc tiep va gian tiep ---\n");
                        for(int j = 0; j < cgraph_ivec_size(dist); j++) {
                            if(dist[j] >= 1) {
                                printf("Ho ten: %s\n", V[j].name);
                                printf("CCCD: %s\n", V[j].CCCD);
                                printf("Sdt: %s\n\n", V[j].soDT);
                            }
                        }
                    }
                }
            }

            if(mark == 0) { // Chua ton tai CCCD trong CSDL
                printf("Khong ton tai!\n");
            }
            break;
        }

        case '7': {
            cgraph_ivec_free(&edges);
            cgraph_ivec_free(&neis);
            cgraph_ivec_free(&father);
            cgraph_ivec_free(&dist);

            cgraph_destroy(&g);
            exit(0);
            break;
        }

        }
    }
    return 0;
}