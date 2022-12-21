#include "cgraph/cgraph.h"
#include "cgen/s2i.h"
#include "cgen/svector.h"

#include <stdio.h>
#include <stdio_ext.h>

typedef struct {
    char url[100];
    char id[10];
    double weight;
} vertex;

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

void webpage_init(vertex *V, int n) {
    for(int i = 0; i < n; i++) {
        V[i].weight = 1;
    }
}

int main() {
    char choice;    
    
    s2i = s2i_create();
    i2s = gtv_create();

    cgraph_ivec_t edges = cgraph_ivec_create();
    
    cgraph_t g;

    int num_v;
    vertex V[50];

    while(1){
        printf("                ---MENU---\n"
               "|1. Doc file.                           |\n"
               "|2. PageRank sau 1 lan lap.             |\n"
               "|3. PageRank sau m lan lap.             |\n"
               "|4. In ra so luong webpage thoa man.    |\n"
               "|5. Khoang cach nho nhat tu id1 -> id2. |\n"
               "|6. Thoat chuong trinh.                 |\n");

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
            FILE *fptr1 = fopen("webpages.txt", "r");
            if(fptr1 == NULL) {
                printf("Cannot open webpages.txt!\n");
                return -1;
            }

            FILE *fptr2 = fopen("pageConnections.txt", "r");
            if(fptr2 == NULL) {
                printf("Cannot open pageConnections.txt!\n");
                return -1;
            }

            fscanf(fptr1, "%d", &num_v);
            
            for(int i = 0; i < num_v; i++) {
                fscanf(fptr1, "%s %s", V[i].url, V[i].id);
            }
            /* ---------------------- IN KET QUA ------------------------ */
            for(int i = 0; i < num_v; i++) {
                printf("%s %s\n", V[i].url, V[i].id);
            }

            int n;

            char s1[10], s2[10];
            int first = 0; // Kiem tra xem co phai phan tu dau dong ko
            int j = 0;
            int s1_id, s2_id;

            fscanf(fptr2, "%d\n", &n);
            while(1) {
                char c = fgetc(fptr2);

                if(c == ' ') {
                    if(first == 0) {
                        first = 1;
                        s1[j] = '\0';
                        s1_id = get_save_id(s1);
                        j = 0;
                    } else{
                        s2[j] = '\0';
                        s2_id = get_save_id(s2);
                        cgraph_ivec_push_back(&edges, s1_id);
                        cgraph_ivec_push_back(&edges, s2_id);
                        j = 0;
                    }
                } else if(c == '\n') {
                    first = 0;
                    s2[j] = '\0';
                    s2_id = get_save_id(s2);
                    cgraph_ivec_push_back(&edges, s1_id);
                    cgraph_ivec_push_back(&edges, s2_id);
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

            g = cgraph_create(edges, 0, true);

            cgraph_ivec_t res_in = cgraph_ivec_create();

            cgraph_degree_all(g, &res_in, CGRAPH_IN, 0);

            int max = res_in[0];
            int min = res_in[0];
            for(int i = 0; i < cgraph_ivec_size(res_in); i++) {
                max = max > res_in[i] ? max : res_in[i];
                min = min < res_in[i] ? min : res_in[i];
            }
            
            for(int i = 0; i < num_v; i++) {
                if(max == res_in[i]) {
                    printf("Webpage co nhieu lien ket toi nhat: %s\n", V[i].url);
                }
                if(min == res_in[i]) {
                    printf("Webpage co it lien ket toi nhat: %s\n", V[i].url);
                }
            }

            cgraph_ivec_free(&res_in);
            fclose(fptr2);
            fclose(fptr1);
            break;
        }

        case '2': {
            webpage_init(V, num_v);
    
            cgraph_ivec_t res_out = cgraph_ivec_create();
            cgraph_degree_all(g, &res_out, CGRAPH_OUT, 0);

            double temp_weight[50] = {0}; // Mang luu trong so tam thoi
            for(int i = 0; i < num_v; i++) {
                for(int j = 0; j < cgraph_ivec_size(edges) / 2; j++) {
                    if(g->to[j] == i) {
                        temp_weight[i] += V[g->from[j]].weight / res_out[g->from[j]];
                    }
                }
            }

            /* ---------- Chuyen tu temp_weight sang V[i].weight */
            for(int i = 0; i < num_v; i++) {
                V[i].weight = temp_weight[i];
            }

            double max = V[0].weight;
            double min = V[0].weight;
            for(int i = 0; i < num_v; i++) {
                max = max > V[i].weight ? max : V[i].weight;
                min = min < V[i].weight ? min : V[i].weight;
            }

            for(int i = 0; i < num_v; i++) {
                if(max == V[i].weight) {
                    printf("Webpage co trong so cao nhat: %s\n", V[i].url);
                }
                if(min == V[i].weight) {
                    printf("Webpage co trong so thap nhat: %s\n", V[i].url);
                }
            }

            break;
        }

        case '3': {
            int m, count = 0;
            printf("Nhap so lan lap: ");
            scanf("%d", &m);

            while(m <= 10 || m >= 50) {
                printf("10 < m < 50! Nhap lai: ");
                scanf("%d", &m);
            }

            webpage_init(V, num_v);
            double temp_weight[50] = {0}; // Mang luu trong so tam thoi
            
            cgraph_ivec_t res_out = cgraph_ivec_create();
            cgraph_degree_all(g, &res_out, CGRAPH_OUT, 0);

            while(count < m) {
                // Khoi tao lai temp_weight = 0
                for(int i = 0; i < num_v; i++) {
                    temp_weight[i] = 0;
                }

                for(int i = 0; i < num_v; i++) {
                    for(int j = 0; j < cgraph_ivec_size(edges) / 2; j++) {
                        if(g->to[j] == i) {
                            temp_weight[i] += V[g->from[j]].weight / res_out[g->from[j]];
                        }
                    }
                }

                /* ---------- Chuyen tu temp_weight sang V[i].weight */
                for(int i = 0; i < num_v; i++) {
                    V[i].weight = temp_weight[i];
                }

                count++;
            }

            // In ra top 3 webpage quan trong nhat
            for(int i = num_v - 1; i >= 0; i--) {
                for(int j = 0; j < i; j++) {
                    if(V[j].weight < V[j+1].weight) {
                        vertex tmp = V[j];
                        V[j] = V[j+1];
                        V[j+1] = tmp;
                    }
                }
            }

            printf("3 webpage quan trong nhat!\n");
            for(int i = 0; i < 3; i++) {
                printf("%s: %lf\n", V[i].url, V[i].weight);
            }
            break;
        }

        case '4': {
            int count_in = 0, count_out = 0;

            cgraph_ivec_t res_out = cgraph_ivec_create();
            cgraph_degree_all(g, &res_out, CGRAPH_OUT, 0);
            cgraph_ivec_t res_in = cgraph_ivec_create();
            cgraph_degree_all(g, &res_in, CGRAPH_IN, 0);

            for(int i = 0; i < num_v; i++) {
                if(res_in[i] != 0 && res_out[i] == 0) {
                    count_in++;
                }
                if(res_in[i] == 0 && res_out[i] != 0) {
                    count_out++;
                }
            }
            printf("So luong webpage chi co lien ket den, khong co lien ket ra ngoai: %d\n", count_in);
            printf("So luong webpage chi co lien ket ra ngoai, khong co lien ket den: %d\n", count_out);

            break;
        }

        case '5': {
            char s1[10], s2[10];
            double length = 0;

            printf("Nhap 2 id: ");
            scanf("%s %s", s1, s2);

            int s1_id = s2i_value(s2i, s1);
            int s2_id = s2i_value(s2i, s2);

            cgraph_ivec_t vpath = cgraph_ivec_create();
            cgraph_ivec_t epath = cgraph_ivec_create();
            cgraph_rvec_t weights = cgraph_rvec_create();

            for(int i = 0; i < cgraph_ivec_size(edges)/2; i++) {
                cgraph_rvec_push_back(&weights, 1);
            }

            cgraph_get_shortest_path_dijkstra(g, &vpath, &epath, s1_id, s2_id, weights, CGRAPH_OUT);
            
            if(cgraph_ivec_size(epath) == 0) {
                printf("-1\n");
            } else{
                for(int i = 0; i < cgraph_ivec_size(epath); i++) {
                    length += weights[epath[i]];
                }
                printf("Khoang cach nho nhat tu %s den %s = %.2lf\n", s1, s2, length);
            }

            break;
        }

        case '6': {
            cgraph_ivec_free(&edges);
            cgraph_destroy(&g);
            exit(0);
            break;
        }

        }
    }
    return 0;
}
