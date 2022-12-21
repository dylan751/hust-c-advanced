#include "cgraph/cgraph.h"
#include "cgen/s2i.h"
#include "cgen/svector.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>

typedef struct {
  char id[10];
  char name[100];
} Vertex;

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
  s2i = s2i_create();  
  i2s = gtv_create();
  
  cgraph_ivec_t edges = cgraph_ivec_create();
  cgraph_rvec_t weights = cgraph_rvec_create();
  cgraph_t g;

  int num_v, num_e, i, j;
  Vertex V[100];

  char choice;
  while(1) {
    printf("     ---MENU---\n"
     "|1. In danh sach dinh.          |\n"
     "|2. Tim ban than thiet nhat.    |\n"
     "|3. Kiem tra quan he bac cau.   |\n"
     "|4. Tim ban chung.              |\n"
     "|5. Thoat.                      |\n");

    __fpurge(stdin);
    printf("Input your choice: ");
    scanf("%c", &choice);

    while(choice > '5' || choice < '1') {
      __fpurge(stdin);
      printf("Ivalid! Input your choice again: ");
      scanf("%c", &choice);
    }

    switch(choice) {
      case '1':{
        FILE* fptr = fopen("data.txt", "r");
        if(fptr == NULL) {
          printf("Cannot open data.txt!\n");
          return -1;
        }

        fscanf(fptr, "%d %d", &num_v, &num_e);

        for(i = 0; i < num_v; i++) {
          fscanf(fptr, "%s %s", s1, s2);
          strcpy(V[i].id, s1);
          strcpy(V[i].name, s2);
        }

        char s1[100], s2[100];
        double w; //Weight
        for(i = 0; i < num_e; i++) {
          fscanf(fptr, "%s %s %lf", s1, s2, &w);

          cgraph_ivec_push_back(&edges, get_save_id(s1));
          cgraph_ivec_push_back(&edges, get_save_id(s2));
          cgraph_rvec_push_back(&weights, w);
          
        }

        g = cgraph_create(edges, 0, false);

        /*--------Duyet ca do thi bang BFS -> In ra--------*/
        cgraph_ivec_t father = cgraph_ivec_create(),
                      dist = cgraph_ivec_create();
        cgraph_simple_bfs(g, 0, CGRAPH_ALL, false, &father, &dist);
        for(i = 0; i < num_e; i++) {
          if(dist[i] >= 0) {
            printf("%s %s\n", V[i].id, V[i].name);
          }
        }
        fclose(fptr); 
        break;
      }

      case '2':{ //NHỚ SỬ DỤNG HÀM cgraph_get_eid() trong type_indexededgelist.c
        char x[10];
        printf("Nhap id cua 1 nguoi: ");
        scanf("%s", x);

        int x_id = s2i_value(s2i, x);
        cgraph_ivec_t neis = cgraph_ivec_create();
        cgraph_neighbors(g, &neis, x_id, CGRAPH_ALL); //Tim duoc cac neighbours cua x

        /*-----------------------------------------------------------------------------------*/
        /* ------------------------ TIM NEIGHBOUR THAN THIET NHAT  ---------------------- */
        double max = 0;
        for(int i = 0; i < cgraph_ivec_size(neis); i++) {
            for(int j = 0; j < num_e; j++) {
                if((g->from[j] == x_id && g->to[j] == neis[i]) || (g->from[j] == neis[i] && g->to[j] == x_id)) {
                    max = max > weights[j] ? max: weights[j];
                }
            }
        }

        /* -------------------------- IN RA MUC DO THAN THIET LON NHAT -------------------- */
        printf("%.2lf\n", max);

        /* --------------------------- IN RA NHUNG BAN THAN NHAT -------------------------- */
        for(int i = 0; i < num_v; i++) {
            if(weights[i] == max) {
                if(g->from[i] == x_id) {
                    printf("%s %s\n", V[g->to[i]].id, V[g->to[i]].name);
                }
                if(g->to[i] == x_id) {
                    printf("%s %s\n", V[g->from[i]].id, V[g->from[i]].name);
                }
            }
        }
        break;
      }

      case '3':{
        char a[10], b[10];
        printf("Nhap id cua 2 nguoi: ");
        scanf("%s %s", a, b);
        int a_id = s2i_value(s2i, a);
        int b_id = s2i_value(s2i, b);

        cgraph_ivec_t father = cgraph_ivec_create(),
                      dist = cgraph_ivec_create();
        cgraph_simple_bfs(g, a_id, CGRAPH_ALL, false, &father, &dist);

        /*---Neu co duong di tu a -> b va dist[b] > 1 (Khong la neighbours) -> co quan he bac cau---*/
          if(dist[b_id] >= 2) { 
            printf("1\n");
          } else {
            printf("-1\n");
          }

        cgraph_ivec_free(&father);
        cgraph_ivec_free(&dist);
        break;
      }

      case '4':{
        char a[10], b[10];
        int mark = 0;
        printf("Nhap id cua 2 nguoi: ");
        scanf("%s %s", a, b);
        int a_id = s2i_value(s2i, a);
        int b_id = s2i_value(s2i, b);

        cgraph_ivec_t neis_a = cgraph_ivec_create();
        cgraph_ivec_t neis_b = cgraph_ivec_create();

        cgraph_neighbors(g, &neis_a, a_id, CGRAPH_ALL);
        cgraph_neighbors(g, &neis_b, b_id, CGRAPH_ALL);

        int k = 0, count = 0;
        /*---Neu a, b cung neighbours x -> x la ban chung---*/
        int result[10]; //Mang luu cac hang xom chung cua a va b
        for(i = 0; i < cgraph_ivec_size(neis_a); i++) {
          for(j = 0; j < cgraph_ivec_size(neis_b); j++) {
            if(neis_a[i] == neis_b[j]) {
              result[k] = neis_a[i];
              count++;
              k++;
              mark = 1; //Tim thay
            }
          }
        }
        if(mark == 0) { //Khong tim thay
          printf("-1\n");
          break;
        }
        
        /*-----------------------In ra ket qua---------------------*/
        printf("%d\n", count);
        for(i = 0; i < count; i++) {
          for(j = 0; j < num_e; j++) {
            if(strcmp(i2s[result[i]].s, V[j].id) == 0) {
              printf("%s %s\n", V[j].id, V[j].name);
            }
          }
        }
        count = 0;

        cgraph_ivec_free(&neis_a);
        cgraph_ivec_free(&neis_b);
        break;
      }

      case '5':{
        s2i_free(&s2i);
        gtv_free(&i2s);

        cgraph_destroy(&g);
        cgraph_ivec_free(&edges);
        cgraph_rvec_free(&weights);
        
        exit(0);
        break;
      }

    }
  }
  return 0;
}
