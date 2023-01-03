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
    char name[20];
    double weight;
} vertex;

int main() {
    s2i = s2i_create();
    i2s = gtv_create();
    
    cgraph_ivec_t edges = cgraph_ivec_create();
    cgraph_ivec_t neis = cgraph_ivec_create();
    cgraph_rvec_t weights = cgraph_rvec_create();

    cgraph_ivec_t father = cgraph_ivec_create();
    cgraph_ivec_t dist = cgraph_ivec_create();

    cgraph_t g = NULL;

    int num_v;
    int n; // So luong danh sach phu thuoc
    vertex V[20];

    char choice;
    while(1){
        printf("             ---MENU---\n"
               "|1. Gioi thieu tac gia.             |\n"
               "|2. Dem so cap phu thuoc truc tiep. |\n"
               "|3. Tim rui ro cuc dai.             |\n"
               "|4. Tim danh sach dai nhat.         |\n"
               "|5. Kiem tra lan truyen.            |\n"
               "|6. Tinh tong thiet hai.            |\n"
               "|7. Tim tong thiet hai lon nhat.    |\n"
               "|8. Thoat chuong trinh.             |\n");

        __fpurge(stdin);
        printf("Nhap lua chon: ");
        scanf("%c", &choice);

        while(choice > '8' || choice < '1'){
            __fpurge(stdin);
            printf("Khong hop le! Nhap lai: ");
            scanf("%c", &choice);
        }

        switch(choice) {
            case '1': {
                // IN THONG TIN SINH VIEN
                printf("STT: %s\n", "11");
                printf("Ho va ten: %s\n", "Nguyen Hai Duong");
                printf("MSSV: %s\n", "20194530");
                // DOC FILE
                FILE *fptr = fopen("dichvu2.txt", "r");
                if(fptr == NULL) {
                    printf("Khong the mo file dichvu.txt!\n");
                    return -1;
                }

                char s1[20], s2[20];
                int s1_id, s2_id;
                fscanf(fptr, "%d", &num_v);
                for(int i = 0; i < num_v; i++) {
                    fscanf(fptr, "%s %lf", V[i].name, &V[i].weight);
                    s1_id = get_save_id(V[i].name);
                    cgraph_rvec_push_back(&weights, V[i].weight);
                }
                
                // for(int i = 0; i < num_v; i++) {
                //     printf("%d %s %lf\n", s2i_value(s2i, V[i].name), V[i].name, V[i].weight);
                // }

                int list_length; // Do dai danh sach
                int first = 0;   // Check dau dong
                fscanf(fptr, "%d", &n);
                for(int i = 0; i < n; i++) {
                    fscanf(fptr, "%d", &list_length);
                    for(int j = 0; j < list_length; j++) {
                        if(first == 0) {    // Dau dong
                            fscanf(fptr, "%s", s1);
                            s1_id = s2i_value(s2i, s1);
                            first = 1;
                        } else {
                            fscanf(fptr, "%s", s2);
                            s2_id = s2i_value(s2i, s2);
                            cgraph_ivec_push_back(&edges, s2_id);
                            cgraph_ivec_push_back(&edges, s1_id);
                        }
                    }
                    first = 0;
                }

                // cgraph_ivec_print(edges);
                g = cgraph_create(edges, num_v, true);
                // cgraph_print(g);
                fclose(fptr);
                break;
            }

            case '2': {
                printf("So luong cap phu thuoc truc tiep la: %d", cgraph_ecount(g));
                printf("\n\n");
                break;
            }

            case '3': { 
                // TIM GIA TRI THIET HAI MAX
                double max = weights[0];
                for(int i = 1; i < cgraph_rvec_size(weights); i++) {
                    max = max > weights[i] ? max : weights[i];
                }
                // printf("%lf\n", max);
                printf("--- Cac dich vu co thiet hai lon nhat ---\n");
                for(int i = 0; i < cgraph_rvec_size(weights); i++) {
                    if(weights[i] == max) {
                        printf("%s %.0lf\n", V[i].name, weights[i]);
                    }
                }
                printf("\n");
                break;
            }

            case '4': {
                cgraph_ivec_t res = cgraph_ivec_create();
                cgraph_degree_all(g, &res, CGRAPH_IN, 1);

                // TIM DICH VU CO BAC MAX
                int max = res[0];
                for(int i = 1; i < cgraph_ivec_size(res); i++) {
                    max = max > res[i] ? max : res[i];
                }

                // IN KET QUA
                printf("--- Cac danh sach phu thuoc dai nhat ---\n");
                for(int i = 0; i < cgraph_ivec_size(res); i++) {
                    if(res[i] == max) {
                        cgraph_neighbors(g, &neis, s2i_value(s2i, V[i].name), CGRAPH_IN);
                        printf("%d %s ", cgraph_ivec_size(neis) + 1, V[i].name);
                        for(int j = 0; j < cgraph_ivec_size(neis); j++) {
                            printf("%s ", i2s[neis[j]].s);
                        }
                        printf("\n");
                    }
                }
                printf("\n");

                cgraph_ivec_free(&res);
                break;
            }

            case '5': {
                char name_1[20], name_2[20];
                printf("Nhap vao 2 ten dich vu khac nhau: ");
                scanf("%s%s", name_1, name_2);

                int name_1_id = s2i_value(s2i, name_1);
                int name_2_id = s2i_value(s2i, name_2);

                while(name_1_id == k_s2i_invalid || name_2_id == k_s2i_invalid) {
                    printf("Phai nhap 2 ten co trong du lieu! Nhap lai: ");
                    scanf("%s%s", name_1, name_2);

                    name_1_id = s2i_value(s2i, name_1);
                    name_2_id = s2i_value(s2i, name_2);
                }

                
                cgraph_simple_bfs(g, name_1_id, CGRAPH_IN, false, &father, &dist);
                
                if(dist[name_2_id] > 0) {
                    printf("YES\n");
                } else {
                    printf("NO\n");
                }

                printf("\n");
                break;
            }

            case '6': {
                char name[20];
                printf("Nhap vao 1 ten dich vu: ");
                scanf("%s", name);

                int name_id = s2i_value(s2i, name);

                while(name_id == k_s2i_invalid) {
                    printf("Phai nhap ten co trong du lieu! Nhap lai: ");
                    scanf("%s", name);

                    name_id = s2i_value(s2i, name);
                }

                // TIM CAC DUONG DI CUA name_id -> TONG WEIGHTS CUA name_id VA CAC HANG XOM 
                cgraph_ivec_t father = cgraph_ivec_create();
                cgraph_ivec_t dist = cgraph_ivec_create();
                cgraph_simple_bfs(g, name_id, CGRAPH_IN, false, &father, &dist);

                double tongThietHai = weights[name_id]; // Ban dau, tongThietHai = thiet hai cua dich vu minh nhap vao
                for(int i = 0; i < cgraph_ivec_size(dist); i++) {
                    if(dist[i] > 0) {
                        tongThietHai += weights[i];
                    }
                }

                printf("Tong thiet hai neu %s gap su co: %.0lf", i2s[name_id].s, tongThietHai);
                printf("\n");

                
                break;
            }

            case '7': {
                double tongThietHai;
                double result[20]; // Mang luu gia tri tong thiet hai cua tung dich vu
                
                int j = 0;
                for(int i = 0; i < num_v; i++) {
                    cgraph_simple_bfs(g, i, CGRAPH_IN, false, &father, &dist);

                    tongThietHai = weights[i]; // Ban dau, tongThietHai = thiet hai cua dich vu minh nhap vao
                    for(int i = 0; i < cgraph_ivec_size(dist); i++) {
                        if(dist[i] > 0) {
                            tongThietHai += weights[i];
                        }
                    }

                    // Luu tongThietHai vao Array result
                    result[j] = tongThietHai;
                    j++;
                }

                // TIM TONG THIET HAI MAX
                int max = result[0];
                for(int i = 1; i < num_v; i++) {
                    max = max > result[i] ? max : result[i];
                }

                // IN KET QUA
                printf("--- Cac dich vu co tong thiet hai lon nhat ---\n");
                for(int i = 0; i < num_v; i++) {
                    if(result[i] == max) {
                        printf("%s %.0lf\n", V[i].name, result[i]);
                    }
                }
                printf("\n");

                break;
            }

            case '8': {
                s2i_free(&s2i);
                gtv_free(&i2s);


                cgraph_ivec_free(&edges);
                cgraph_ivec_free(&neis);
                cgraph_rvec_free(&weights);
                cgraph_ivec_free(&father);
                cgraph_ivec_free(&dist);
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
