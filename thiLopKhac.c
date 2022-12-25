#include "cgraph/cgraph.h"
#include "cgen/svector.h"
#include "cgen/s2i.h"

#include <stdio.h>
#include <stdio_ext.h>
#include <ctype.h>

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

int main() {
    int choice;
  
    s2i = s2i_create();
    i2s = gtv_create();

    int num_v;
    cgraph_ivec_t edges = cgraph_ivec_create();
    cgraph_ivec_t neis = cgraph_ivec_create();
    cgraph_t g;

    while(1){
        printf("                     ---MENU---\n"
               "|1. Doc vao danh sach tiep xuc gan tu file.             |\n"
               "|2. In danh sach tiep xuc gan.                          |\n"
               "|3. Kiem tra tiep xuc gan.                              |\n"
               "|4. in danh sach tiep xuc gan cua 1 nguoi.              |\n"
               "|5. Nhung nguoi tiep xuc gan nhieu nhat.                |\n"
               "|6. In ra danh sach F1 va F2.                           |\n"
               "|7. Bo sung nguoi vao danh sach.                        |\n"
               "|8. Bo sung thong tin tiep xuc gan da co giua 2 nguoi.  |\n"
               "|9. Ghi danh sach ra file text.                         |\n"
               "|10. Thoat chuong trinh.                                |\n");

        __fpurge(stdin);
        printf("Input your choice: ");
        scanf("%d", &choice);

        while(choice > 10 || choice < 1){
            printf("Ivalid! Input your choice again: ");
            scanf("%d", &choice);
        }

        switch(choice) {
            case 1: {
                FILE *fptr = fopen("tiepXucGan.txt", "r");
                if(fptr == NULL) {
                    printf("Cannot open tiepXucGan.txt!\n");
                    return -1;
                }

                char s1[2], s2[2];
                char c;
                int s1_id, s2_id;
                int first = 0;
                fscanf(fptr, "%d", &num_v);
                
                for(int i = 0; i < num_v; i++) {
                    s1[0] = 'A' + i;
                    s1[1] = '\0';
                    s1_id = get_save_id(s1);
                }

                while((c = fgetc(fptr)) != EOF) {
                    if(c == ' ') {
                        if(first == 0) {
                            first = 1;
                        }
                    } else if(c == '\n') {
                        first = 0;
                    } else {
                        if(first == 0) {
                            s1[0] = c;
                            s1[1] = '\0';
                            s1_id = get_save_id(s1);
                        } else {
                            s2[0] = c;
                            s2[1] = '\0';
                            s2_id = get_save_id(s2);
                            cgraph_ivec_push_back(&edges, s1_id);
                            cgraph_ivec_push_back(&edges, s2_id);
                        }
                    }
                }

                g = cgraph_create(edges, 0, true);

                fclose(fptr);
                break;
            }

            case 2: {
                for(int i = 0; i < num_v; i++) {
                    cgraph_neighbors(g, &neis, i, CGRAPH_OUT);
                    printf("%s ", i2s[i].s);
                    for(int j = 0; j < cgraph_ivec_size(neis); j++) {
                        printf("%s ", i2s[neis[j]].s);
                    }
                    printf("\n");
                }
                break;
            }

            case 3: {
                char s1[2], s2[2];
                printf("Nhap ten 2 nguoi: ");
                scanf("%s%s", s1, s2);

                int mark = 0; // Chua tim thay tiep xuc gan
                int s1_id = s2i_value(s2i, s1);
                int s2_id = s2i_value(s2i, s2);

                cgraph_neighbors(g, &neis, s1_id, CGRAPH_OUT);

                for(int i = 0; i < cgraph_ivec_size(neis); i++) {
                    if(s2_id == neis[i]) {
                        mark = 1;
                        printf("Co tiep xuc gan!\n");
                    }
                }
                if(mark == 0) {
                    printf("Khong tiep xuc gan!\n");
                }

                break;
            }

            case 4: {
                char inp_name[2];
                printf("Nhap vao ten 1 nguoi:");
                scanf("%s", inp_name);

                int name_id = s2i_value(s2i, inp_name);

                cgraph_neighbors(g, &neis, name_id, CGRAPH_OUT);
                printf("Danh sach tiep xuc gan: ");
                for(int i = 0; i < cgraph_ivec_size(neis); i++) {
                    printf("%s ", i2s[neis[i]].s);
                }
                printf("\n");

                break;
            }

            case 5: {
                cgraph_ivec_t res = cgraph_ivec_create();
                cgraph_degree_all(g, &res, CGRAPH_OUT, 1);

                int max = res[0];
                for(int i = 1; i < cgraph_ivec_size(res); i++) {
                    max = max > res[i] ? max : res[i];
                }

                printf("Nhung nguoi tiep xuc gan voi nhieu nguoi nhat: ");
                for(int i = 0; i < num_v; i++) {
                    if(res[i] == max) {
                        printf("%s", i2s[i].s);
                    }
                }
                printf("\n");
                cgraph_ivec_free(&res);
                break;
            }

            case 6: {
                char inp_name[2];
                int mark = 0;
                printf("Nhap ten nguoi nghi nhiem F0: ");
                scanf("%s", inp_name);

                int name_id = s2i_value(s2i, inp_name);
                for(int i = 0; i < num_v; i++) {
                    if(name_id == i) {
                        mark = 1;
                    }
                }
                if(mark == 0) {
                    printf("Nguoi ban nhap khong ton tai! Nhap lai: ");
                    scanf("%s", inp_name);
                    int name_id = s2i_value(s2i, inp_name);
                }
                
                cgraph_ivec_t neis_tmp = cgraph_ivec_create();

                cgraph_neighbors(g, &neis, name_id, CGRAPH_OUT);
                /* ---- Danh sach F1 ----*/
                printf("Danh sach F1: ");
                for(int j = 0; j < cgraph_ivec_size(neis); j++) {
                    printf("%s ", i2s[neis[j]].s);
                }
                printf("\n");

                /* ---- Danh sach F2 -> Nhung nguoi tiep xuc vs F1 nhung khong phai F0 ---- */
                cgraph_ivec_t father = cgraph_ivec_create();
                cgraph_ivec_t dist = cgraph_ivec_create();
                cgraph_ivec_t father_tmp = cgraph_ivec_create();
                cgraph_ivec_t dist_tmp = cgraph_ivec_create();
                
                cgraph_simple_bfs(g, name_id, CGRAPH_OUT, 1, &father, &dist);

                printf("Danh sach F2: "); // F2: distF1 = 1, distF0 > 1
                for(int i = 0; i < cgraph_ivec_size(neis); i++) {
                    cgraph_simple_bfs(g, neis[i], CGRAPH_OUT, 1, &father_tmp, &dist_tmp);
                    for(int j = 0; j < cgraph_ivec_size(dist_tmp); j++) {
                        if(dist_tmp[j] == 1 && dist[j] > 1) {
                            printf("%s ", i2s[j].s);
                        }
                    }
                }
                printf("\n");   
                
                cgraph_ivec_free(&neis_tmp);
                cgraph_ivec_free(&father);
                cgraph_ivec_free(&dist);
                cgraph_ivec_free(&father_tmp);
                cgraph_ivec_free(&dist_tmp);
                break;
            }

            case 7: {
                char inp_name[2], tx_name[2];
                int name_id;
                printf("Nhap nguoi muon bo sung vao danh sach: ");
                scanf("%s", inp_name);

                if((s2i_value(s2i, inp_name)) == k_s2i_invalid) {
                    name_id = get_save_id(inp_name);
                    cgraph_add_vertices(g, name_id);
                    num_v++;
                }

                printf("Nhap nguoi tiep xuc gan voi %s: ", inp_name);
                scanf("%s", tx_name);

                int tx_name_id = s2i_value(s2i, tx_name);
                cgraph_ivec_t edges_add = cgraph_ivec_create();
                cgraph_ivec_push_back(&edges_add, name_id);
                cgraph_ivec_push_back(&edges_add, tx_name_id);

                cgraph_ivec_push_back(&edges_add, tx_name_id);
                cgraph_ivec_push_back(&edges_add, name_id);

                cgraph_add_edges(g, edges_add);

                printf("Update thanh cong!\n");

                cgraph_ivec_free(&edges_add);
                break;
            }

            case 8: {
                char s1[2], s2[2];
                printf("Them thong tin tiep xuc gan giua 2 nguoi trong danh sach: ");
                scanf("%s%s", s1, s2);
                int s1_id = s2i_value(s2i, s1);
                int s2_id = s2i_value(s2i, s2);
                
                cgraph_ivec_t edges_add = cgraph_ivec_create();
                cgraph_ivec_push_back(&edges_add, s1_id);
                cgraph_ivec_push_back(&edges_add, s2_id);

                cgraph_ivec_push_back(&edges_add, s2_id);
                cgraph_ivec_push_back(&edges_add, s1_id);

                cgraph_add_edges(g, edges_add);

                cgraph_ivec_free(&edges_add);
                break;
            }

            case 9: {
                FILE* fout = fopen("ketQua.txt", "w");
                
                for(int i = 0; i < num_v; i++) {
                    fprintf(fout, "%s ", i2s[i].s);
                    cgraph_neighbors(g, &neis, i, CGRAPH_OUT);
                    for(int j = 0; j < cgraph_ivec_size(neis); j++) {
                        fprintf(fout, "%s ", i2s[neis[j]].s);
                    }
                    fprintf(fout, "\n");
                }
                printf("Ghi ra file ketQua.txt thanh cong!\n");

                fclose(fout);
                break;
            }

            case 10: {
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