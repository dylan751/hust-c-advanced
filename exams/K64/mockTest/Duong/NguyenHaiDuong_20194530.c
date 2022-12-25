#include "cgraph/cgraph.h"
#include "cgen/s2i.h"
#include "cgen/svector.h"

#include <stdio.h>
#include <string.h>
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
    char maHP[10];
    char tenHP[50];
} hocPhan;

typedef struct {
    char tenHP[10];
} passed;

int main() {
    s2i = s2i_create();
    i2s = gtv_create();
    
    cgraph_ivec_t edges = cgraph_ivec_create();
    cgraph_ivec_t neis = cgraph_ivec_create();
    cgraph_t g = NULL;

    int num_v = 0, num_e;
    hocPhan HP[20];
    passed pass[20];

    char choice;
    while(1){
        printf("                ---MENU---\n"
               "|1. Tra cuu dieu kien dang ky hoc phan.  |\n"
               "|2. Thoat chuong trinh.                  |\n");

        __fpurge(stdin);
        printf("Nhap lua chon: ");
        scanf("%c", &choice);

        while(choice > '2' || choice < '1'){
            __fpurge(stdin);
            printf("Khong hop le! Nhap lai: ");
            scanf("%c", &choice);
        }

        switch(choice) {
            case '1': {
                FILE *fptr1 = fopen("hocphan.txt", "r");
                if(fptr1 == NULL) {
                    printf("Khong the mo file hocphan.txt!\n");
                    return -1;
                }

                FILE *fptr2 = fopen("passed.txt", "r");
                if(fptr2 == NULL) {
                    printf("Khong the mo file passed.txt!\n");
                    return -1;
                }

                char str[100];
                int i = 0;
                while(1) {
                    fscanf(fptr1, "%s", str);

                    if(strcmp(str, "0000") != 0)  {
                        strcpy(HP[i].maHP, str);
                        int str_id = get_save_id(str);

                        fgets(str, 100, fptr1);
                        strcpy(HP[i].tenHP, str);
                        i++;
                        num_v++;
                    } else {
                        break;
                    }       
                }

                // for(int i = 0; i < num_v; i++) {
                //     printf("%d: %s %s", s2i_value(s2i, HP[i].maHP), HP[i].maHP, HP[i].tenHP);
                // }

                char s1[20], s2[20];    
                int s1_id, s2_id;
                while((fscanf(fptr1, "%s %s", s1, s2)) != EOF) {
                    s1_id = s2i_value(s2i, s1);
                    s2_id = s2i_value(s2i, s2);

                    cgraph_ivec_push_back(&edges, s1_id);
                    cgraph_ivec_push_back(&edges, s2_id);
                }

                g = cgraph_create(edges, num_v, true);

                i = 0;
                int num_passed = 0;
                while((fscanf(fptr2, "%s", s1)) != EOF) {
                    strcpy(pass[i].tenHP, s1);
                    num_passed++;
                    i++;
                }

                /* --------------------------------------------------------------- */
                char HP_inp[10];
                int mark = 0;
                printf("Nhap vao 1 hoc phan: ");
                scanf("%s", HP_inp);

                int HP_id = s2i_value(s2i, HP_inp);
                if(HP_id == k_s2i_invalid) {
                    printf("Khong tim thay ma hoc phan!\n");
                } else {
                    for(int i = 0; i < num_passed; i++) {
                        if(strcmp(pass[i].tenHP, HP_inp) == 0) {
                            mark = 1;   // Da hoan thanh hoc phan
                            printf("Da hoan thanh hoc phan!\n");
                        }
                    }

                    if(mark == 0) { // Chua hoan thanh hoc phan
                        cgraph_neighbors(g, &neis, HP_id, CGRAPH_IN);
                        for(int i = 0; i < num_passed; i++) {
                            if(strcmp(pass[i].tenHP, i2s[neis[0]].s) == 0) {
                                mark = 1;   // Da hoan thanh hoc phan
                                printf("Du dieu kien dang ky!\n");
                            }
                        }
                        if(mark == 0) {
                            printf("Khong dang ky duoc!\n");
                        }
                    }
                }


                break;
            }

            case '2': {
                cgraph_ivec_free(&edges);
                cgraph_ivec_free(&neis);
                if(g != NULL) {
                    cgraph_destroy(&g);
                }
                exit(0);
                break;
            }

        }
    }
    return 0;
}