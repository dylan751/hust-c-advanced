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
    char id[5];
    char name[25];
} vertex;

int main() {
    s2i = s2i_create();
    i2s = gtv_create();

    cgraph_ivec_t edges = cgraph_ivec_create();
    cgraph_ivec_t neis = cgraph_ivec_create();
    cgraph_t g = NULL;

    int num_v;
    vertex V[50];

    char choice;

    while(1){
        printf("        ---MENU---\n"
               "|1. Input data.         |\n"
               "|2. List friend.        |\n"
               "|3. Popular person.     |\n"
               "|4. Check friend.       |\n"
               "|5. Suggest friend.     |\n"
               "|6. Thoat chuong trinh. |\n");

        __fpurge(stdin);
        printf("Input your choice: ");
        scanf("%c", &choice);

        while(choice > '6' || choice < '1'){
            __fpurge(stdin);
            printf("Ivalid! Input your choice again: ");
            scanf("%c", &choice);
        }

        switch(choice) {
        case '1': {
            FILE *fptr1 = fopen("users.txt", "r");
            if(fptr1 == NULL) {
                printf("Cannot open users.txt!\n");
                return -1;
            }

            FILE *fptr2 = fopen("friends.txt", "r");
            if(fptr1 == NULL) {
                printf("Cannot open friends.txt!\n");
                return -1;
            }

            /* --------- Doc file users.txt --------- */
            char s1[5], s2[25];
            int s1_id, s2_id;
            fscanf(fptr1, "%d", &num_v);
            for(int i = 0; i < num_v; i++) {
                fscanf(fptr1, "%s %s", s1, s2);
                strcpy(V[i].id, s1);
                strcpy(V[i].name, s2);

                s1_id = get_save_id(s1);
            }

            /* --------- Doc file friends.txt --------- */
            char c;
            int first = 0, j = 0;
            while(1) {
                c = fgetc(fptr2);
                if(c == ' ') {
                    if(first == 0) {
                        first = 1;
                        s1[j] = '\0';
                        s1_id = get_save_id(s1);
                        j = 0;
                    } else {
                        s2[j] = '\0';
                        s2_id = get_save_id(s2);
                        cgraph_ivec_push_back(&edges, s1_id);
                        cgraph_ivec_push_back(&edges, s2_id);
                        j = 0;
                    }
                } else if(c == '\n') {
                    if(first != 0) {
                        s2[j] = '\0';
                        s2_id = get_save_id(s2);
                        cgraph_ivec_push_back(&edges, s1_id);
                        cgraph_ivec_push_back(&edges, s2_id);
                    }
                    first = 0;
                    j = 0;
                } else {
                    if(first == 0) {
                        s1[j] = c;
                        j++;
                    } else {
                        s2[j] = c;
                        j++;
                    }
                }
                if(c == EOF) {
                    s2[j-1] = '\0';
                    s2_id = get_save_id(s2);
                    cgraph_ivec_push_back(&edges, s1_id);
                    cgraph_ivec_push_back(&edges, s2_id);
                    break;
                }
            }

            g = cgraph_create(edges, num_v, true);

            for(int i = 0; i < num_v; i++) {
                printf("%s %s\n", V[i].id, V[i].name);
            }
            for(int i = 0; i < num_v; i++) {
                cgraph_neighbors(g, &neis, i, CGRAPH_OUT);
                printf("%s ", i2s[i].s);
                for(int j = 0; j < cgraph_ivec_size(neis); j++) {
                    printf("%s ", i2s[neis[j]].s);
                }
                printf("\n");
            }

            fclose(fptr1);
            fclose(fptr2);
            break;
        }

        case '2': {
            char inp_name[25];
            int mark = 0;
            int inp_id;         // Tim id dua tren name nhap vao
            printf("Nhap ten 1 nguoi: ");
            scanf("%s", inp_name);

            for(int i = 0; i < num_v; i++) {
                if(strcmp(V[i].name, inp_name) == 0) {
                    inp_id = s2i_value(s2i, V[i].id);
                    mark = 1;
                }
            }

            if(mark == 0) {
                printf("Khong co ten trong du lieu!\n");
            } else {
                printf("%d\n", inp_id);
                cgraph_neighbors(g, &neis, inp_id, CGRAPH_OUT);
                if(cgraph_ivec_size(neis) == 0) {
                    printf("Khong co ban!\n");
                } else{
                    for(int i = 0; i < cgraph_ivec_size(neis); i++) {
                        printf("%s\n", V[neis[i]].name);
                    }
                }
            }

            break;
        }

        case '3': {
            cgraph_ivec_t res = cgraph_ivec_create();
            cgraph_degree_all(g, &res, CGRAPH_OUT, true);
            printf("%d\n", cgraph_ivec_size(res));

            /* ------------- Tao mang V_tmp luu tam thoi mang V ------------- */
            vertex V_tmp[100];
            for(int i = 0; i < num_v; i++) {
                strcpy(V_tmp[i].id, V[i].id);
                strcpy(V_tmp[i].name, V[i].name);
            }

            /* ------------- Sap xep lai mang res ------------- */
            for(int i = cgraph_ivec_size(res) - 1; i >= 0; i--) {
                for(int j = 0; j < i; j++) {
                    if(res[j] < res[j+1]) {
                        int tmp = res[j];
                        res[j] = res[j+1];
                        res[j+1] = tmp;

                        /* Dao lai mang V_tmp */
                        vertex x = V_tmp[j];
                        V_tmp[j] = V_tmp[j+1];
                        V_tmp[j+1] = x;
                    }
                }
            }

            for(int i = 0; i < cgraph_ivec_size(res); i++) {
                printf("%-20s %d\n", V_tmp[i].name, res[i]);
            }

            cgraph_ivec_free(&res);
            break;
        }

        case '4': {
            char name_1[25], name_2[25];
            int name_1_id, name_2_id, mark = 0;
            printf("Nhap ten 2 nguoi: ");
            scanf("%s%s", name_1, name_2);

            for(int i = 0; i < num_v; i++) {
                if(strcmp(V[i].name, name_1) == 0) {
                    name_1_id = s2i_value(s2i, V[i].id);
                }
                if(strcmp(V[i].name, name_2) == 0) {
                    name_2_id = s2i_value(s2i, V[i].id);
                }
            }

            cgraph_neighbors(g, &neis, name_1_id, CGRAPH_OUT);
            for(int i = 0; i < cgraph_ivec_size(neis); i++) {
                if(name_2_id == neis[i]) {
                    printf("La ban be cua nhau!\n");
                    mark = 1;
                    break;
                }
            }

            if(mark == 0) {
                printf("Khong la ban be cua nhau!\n");
            }
            break;
        }

        case '5': {
            char inp_name[25];
            int inp_id, mark = 0;
            printf("Nhap ten 1 nguoi: ");
            scanf("%s", inp_name);

            for(int i = 0; i < num_v; i++) {
                if(strcmp(V[i].name, inp_name) == 0) {
                    inp_id = s2i_value(s2i, V[i].id);
                    mark = 1;
                }
            }

            if(mark == 0) {
                printf("Khong co ten trong du lieu!\n");
            } else {
                printf("--- Goi y ket ban ---\n");

                cgraph_ivec_t father = cgraph_ivec_create();
                cgraph_ivec_t dist = cgraph_ivec_create();
                cgraph_simple_bfs(g, inp_id, CGRAPH_OUT, false, &father, &dist);
                for(int i = 0; i < num_v; i++) {
                    if(dist[i] >= 2) {
                        printf("%s\n", V[i].name);
                    }
                }

            }

            cgraph_ivec_free(&father);
            cgraph_ivec_free(&dist);
            break;
        }

        case '6': {
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