#include "cgraph/cgraph.h"
#include "cgen/s2i.h"
#include "cgen/gtvector.h"
#include "cgen/svector.h"

#include <stdio_ext.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char url[250];
    char id[10];
    double page_rank;
} webpage;

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

webpage* webpage_init(webpage *WP, int n) {
    int i;
    for(i = 0; i < n; i++) {
        WP[i].page_rank = 1;          //Khoi tao tat ca page rank ban dau = 1
    }    
    return WP;
}

int main() {
    s2i = s2i_create();
    i2s = gtv_create();
    
    cgraph_t g;
    cgraph_ivec_t edges = cgraph_ivec_create();
    cgraph_ivec_t res = cgraph_ivec_create();       // cgraph_degree_all
    cgraph_ivec_t neis = cgraph_ivec_create();      // cgraph_neighbors

    webpage WP[100];
    double page_rank_arr[100];                      // Mang luu tru page rank sau moi lan cap nhat
    int num_v, i, j, k, n;

    char choice;
  
    while(1){
        printf("                    -------------MENU--------------\n"
               "|1.   Doc noi dung tu 2 file.                                             |\n"
               "|2.   In ra url cua webpage co trong so cao nhat va thap nhat.            |\n"
               "|3.   In ra top 3 webpage quan trong nhat sau m lan lap.                  |\n"
               "|4.a) In ra webpage ma chi co lien ket den, khong co lien ket ra ngoai.   |\n"
               "|  b) In ra webpage ma chi co lien ket ra ngoai, khong co lien ket den.   |\n"
               "|5.   Tim khoang cach nho nhat tu id1 -> id2.                             |\n"
               "|6.   Thoat chuong trinh.                                                 |\n");

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
            char s_id[20];
            FILE* fptr_1 = fopen("webpages.txt", "r");
            if(fptr_1 == NULL) {
                printf("Cannot open webpages.txt!\n");
                return -1;
            }
            

            fscanf(fptr_1, "%d", &num_v);
            // WP = webpage_init(num_v);
            for(i = 0; i < num_v; i++) {
                fscanf(fptr_1, "%s %s", WP[i].url, WP[i].id);
            }
            
            /*-------------------In ra so luong webpage va url, id tung webpage------------------*/
            printf("So luong webpage: %d\n", num_v);
            for(i = 0; i < num_v; i++) {
                printf("%s %s\n", WP[i].url, WP[i].id);
            }

            fclose(fptr_1);

            /*--------------------Doc FILE thu 2--------------------*/
            FILE* fptr_2 = fopen("pageConnections.txt", "r");
            if(fptr_2 == NULL) {
                printf("Cannot open pageConnections.txt!\n");
                return -1;
            }
            
            int id1, id2, mark = 1; 
            char c;
            fscanf(fptr_2, "%d\n", &n);
            char s_id1[30], s_id2[30];
            int first = 0; // Bien danh dau xem co phai ID o dau` dong` khong?
            j = 0;
            
            while(1) {
                c = fgetc(fptr_2);

                if(c == ' ') {
                    if(first == 0) {
                        s_id1[j] = '\0';
                        id1 = get_save_id(s_id1);
                        first++;
                        j = 0;
                        // printf("%s: ", s_id1);
                        // printf("%d: ", id1);
                    }
                    else {
                        s_id2[j] = '\0';
                        id2 = get_save_id(s_id2);
                        cgraph_ivec_push_back(&edges, id1);
                        cgraph_ivec_push_back(&edges, id2);
                        j = 0;
                        // printf("%s ", s_id2);         
                        // printf("%d ", id2);
                    }
                }
                else if(c == '\n') {
                    s_id2[j] = '\0';
                    id2 = get_save_id(s_id2);
                    cgraph_ivec_push_back(&edges, id1);
                    cgraph_ivec_push_back(&edges, id2);
                    // printf("%s\n", s_id2);
                    // printf("%d\n", id2);
                    first = 0;              // Khoi tao lai -> dong moi
                    j = 0;
                }
                else {              // Neu c la ki tu binh thuong
                    if(first == 0){ // Neu la ID dau` dong` -> luu vao s_id1
                        s_id1[j] = c;
                        j++;
                    }
                    else {          // Neu ko phai dau` dong` -> luu vao s_id2
                        s_id2[j] = c;
                        j++;
                    }
                }

                if(c == EOF) {
                    if(mark == 1) {     // Neu gap EOF lan 1 -> Push back canh cuoi cung vao edges
                        s_id2[--j] = '\0';  // Vì nêu để s_id2[j] = '\0' thì s_id2 = 1012& (Nó gặp phải kí tự đặc biệt gì đó trước EOF)
                        // printf("%s\n", s_id2);
                        id2 = get_save_id(s_id2);
                        cgraph_ivec_push_back(&edges, id1);
                        cgraph_ivec_push_back(&edges, id2);
                        mark = 0;
                    }
                    else{               //Neu gap EOF lan 2 -> break
                        break;
                    }
                }
            }
            
            // cgraph_ivec_print(edges);

            g = cgraph_create(edges, 0, true);
            // cgraph_print(g);
            fclose(fptr_2);
            /*-----------------------------------------------------------------------------------------*/
            
            cgraph_degree_all(g, &res, CGRAPH_IN, 0);

            int max, min;
            max = res[0];
            min = res[0];

            for(i = 1; i < cgraph_ivec_size(res); i++) {
                max = max > res[i] ? max : res[i];
                min = min < res[i] ? min : res[i];
            }

            
            /*-----------------TIM INDEG LON NHAT----------------*/
            for(i = 0; i < num_v; i++) {
                cgraph_neighbors(g, &neis, i, CGRAPH_IN);
                if(cgraph_ivec_size(neis) == max) {
                    printf("\nWebpage co nhieu lien ket toi nhat: ");
                    /*Co ID i -> chuyen ve string cua i -> so sanh voi tung ID trong mang WP -> in ra url tuong ung*/
                    for(j = 0; j < num_v; j++) {  
                        if(strcmp(i2s[i].s, WP[j].id) == 0) {
                            printf("%s\n", WP[j].url);
                        }
                    }
                }

                /*-----------------TIM INDEG NHO NHAT----------------*/
                if(cgraph_ivec_size(neis) == min) {
                    printf("\nWebpage co it lien ket toi nhat: ");
                    /*Co ID i -> chuyen ve string cua i -> so sanh voi tung ID trong mang WP -> in ra url tuong ung*/
                    for(j = 0; j < num_v; j++) {  
                        if(strcmp(i2s[i].s, WP[j].id) == 0) {
                            printf("%s\n", WP[j].url);
                        }
                    }

                }
            }
            
            
            break;
        }

        case '2':{
            webpage_init(WP, num_v); //Khoi tao tat ca page_rank = 1
            double sum;              //Page rank tam thoi

            cgraph_degree_all(g, &res, CGRAPH_OUT, 0);
            /*--------------------THUAT TOAN PAGE RANK CHO 1 LAN--------------------*/
            for(i = 0; i < num_v; i++) {
                sum = 0;
                cgraph_neighbors(g, &neis, i, CGRAPH_IN);            
                
                for(j = 0; j < cgraph_ivec_size(neis); j++) {                    
                    for(k = 0; k < num_v; k++) {
                        /*----------SUM = PAGE RANK SAU 1 VONG--------*/
                        if(strcmp(i2s[neis[j]].s, WP[k].id) == 0) {
                            sum += WP[k].page_rank / res[neis[j]];
                        }
                    }
                }   
                /*---------LUU TAM THOI CAC PAGE RANK SAU 1 LAN LAP VAO MANG page_rank_arr---------*/
                for(j = 0; j < num_v; j++) {
                    if(strcmp(i2s[i].s, WP[j].id) == 0) {
                        page_rank_arr[j] = sum;
                    }
                }
            
            }

            /*-----------LUU TAT CA PAGE RANK SAU 1 LAN LAP VAO WP[].page_rank-----------*/
            for(j = 0; j < num_v; j++) {
                WP[j].page_rank = page_rank_arr[j];    
            }

            /*-------------------------------IN RA KET QUA-------------------------------*/
            printf("-------Sau lan lap dau tien-------\n");
            double max = WP[0].page_rank;
            double min = WP[0].page_rank;
            for(i = 1; i < num_v; i++) {
                max = max > WP[i].page_rank ? max : WP[i].page_rank;
                min = min < WP[i].page_rank ? min : WP[i].page_rank;
            }
            
            for(i = 0; i < num_v; i++) {
                if(WP[i].page_rank == max) {
                    printf("Webpage co trong so cao nhat: %s\n", WP[i].url);
                }
                if(WP[i].page_rank == min) {
                    printf("Webpage co trong so thap nhat: %s\n", WP[i].url);
                }
            }
            break;
        }

        case '3':{
            int m, mark = 1;
            printf("Nhap so lan muon lap: ");
            scanf("%d", &m);
            while(m < 10 || m > 50) {
                printf("10 <= m <= 50! Nhap lai: ");
                scanf("%d", &m);
            }

            /*----------------THEM 1 VONG FOR VAO PAGE RANK O CAU 2------------*/
            webpage_init(WP, num_v); //Khoi tao tat ca page_rank = 1
            double sum;              //Page rank tam thoi
            cgraph_degree_all(g, &res, CGRAPH_OUT, 0);

            int count = 0;
            while(count < m) {
                /*--------------------THUAT TOAN PAGE RANK CHO 1 LAN--------------------*/
                for(i = 0; i < num_v; i++) {
                    sum = 0;
                    cgraph_neighbors(g, &neis, i, CGRAPH_IN);            
                    
                    for(j = 0; j < cgraph_ivec_size(neis); j++) {                    
                        for(k = 0; k < num_v; k++) {
                            /*----------SUM = PAGE RANK SAU 1 VONG--------*/
                            if(strcmp(i2s[neis[j]].s, WP[k].id) == 0) {
                                sum += WP[k].page_rank / res[neis[j]];
                            }
                        }
                    }   
                    /*---------LUU TAM THOI CAC PAGE RANK SAU 1 LAN LAP VAO MANG page_rank_arr---------*/
                    for(j = 0; j < num_v; j++) {
                        if(strcmp(i2s[i].s, WP[j].id) == 0) {
                            page_rank_arr[j] = sum;
                            // printf("Page_rank_arr[%d] = %lf\n", j, page_rank_arr[j]);
                        }
                    }
                
                }

                /*-----------LUU TAT CA PAGE RANK SAU 1 LAN LAP VAO WP[].page_rank-----------*/
                for(j = 0; j < num_v; j++) {
                    WP[j].page_rank = page_rank_arr[j];    
                }

                count++;
            }
            
            /*------------SAP XEP LAI MANG -> IN RA 3 WEBSITE QUAN TRONG NHAT------------*/
            webpage tmp;
            for(i = num_v - 1; i >= 0; i--) {
                for(j = 0; j < i; j++) {
                    if(WP[j].page_rank < WP[j+1].page_rank) {
                        tmp = WP[j];
                        WP[j]= WP[j+1];
                        WP[j+1] = tmp;
                    }
                }
            }
            /*-------------------------------IN RA KET QUA-------------------------------*/
            printf("-------------Sau %d lan lap------------\n", m);
            printf("-------3 webpage quan trong nhat-------\n\n");
            for(i = 0; i < 3; i++) {
                printf("%s\n", WP[i].url);
            }
            printf("\n");
            break;
        }

        case '4':{
            printf("\n");
            cgraph_ivec_t res_in = cgraph_ivec_create();
            cgraph_ivec_t res_out = cgraph_ivec_create();

            cgraph_degree_all(g, &res_in, CGRAPH_IN, 0);
            cgraph_degree_all(g, &res_out, CGRAPH_OUT, 0);

            /*-----------------TIM NHUNG WEB CO RES_IN != 0 VA` RES_OUT == 0-----------------*/
            int mark = 0;                   //CHUA CO KET QUA
            for(i = 0; i < num_v; i++) {
                if((res_in[i] != 0) && (res_out[i] == 0)) {
                    printf("a) Webpage chi co lien ket den, khong co lien ket ra: ");
                    for(j = 0; j < num_v; j++) {
                        if(strcmp(i2s[i].s, WP[j].id) == 0) {
                            printf("%s\n", WP[j].url);
                        }
                    }
                    mark = 1; //CO KET QUA
                }
            }
            if(mark == 0)   printf("a) Khong co webpage nao thoa man!\n");

            /*-----------------TIM NHUNG WEB CO RES_IN == 0 VA` RES_OUT != 0-----------------*/
            mark = 0;                   //CHUA CO KET QUA
            for(i = 0; i < num_v; i++) {
                if((res_in[i] == 0) && (res_out[i] != 0)) {
                    printf("b) Webpage chi co lien ket ra, khong co lien ket den: ");
                    for(j = 0; j < num_v; j++) {
                        if(strcmp(i2s[i].s, WP[j].id) == 0) {
                            printf("%s\n", WP[j].url);
                        }
                    }
                    mark = 1; //CO KET QUA
                }
            }
            if(mark == 0)   printf("b) Khong co webpage nao thoa man!\n");
            printf("\n");

            cgraph_ivec_free(&res_in);
            cgraph_ivec_free(&res_out);
            break;
        }

        case '5':{
            char id1[10], id2[10];
            printf("Nhap id1 va id2: ");
            scanf("%s %s", id1, id2);

            int i_id1 = atoi(id1);
            int i_id2 = atoi(id2);

            if((i_id1 == i_id2) || (i_id1 < 0) || (i_id2 < 0)) {
                printf("-1\n");
                break;
            }
            /*---------KIEM TRA ID1 VA ID2 CO TRONG DU LIEU DOC VAO KHONG---------*/
            int mark = 0;       //CHUA TIM THAY ID1 VA ID2
            for(i = 0; i < num_v; i++) {
                if(strcmp(i2s[i].s, id1) == 0) {
                    for(j = 0; j < num_v; j++) {
                        if(strcmp(i2s[j].s, id2) == 0) {
                            mark = 1;   //DA TIM THAY ID1, ID2 TRONG DU LIEU 
                        }
                    }
                }
            }
            if(mark == 0) {         //ID1, ID2 KHONG CO TRONG DU LIEU DOC VAO
                printf("-1\n");
                break;
            }


            i_id1 = s2i_value(s2i, id1);
            i_id2 = s2i_value(s2i, id2);
            
            cgraph_ivec_t vpath = cgraph_ivec_create();
            cgraph_ivec_t epath = cgraph_ivec_create();
            cgraph_rvec_t weights = cgraph_rvec_create();

            /*------KHOI TAO TAT CA WEIGHTS = 1 - BAI NAY CO 9 CANH*/
            for(i = 0; i < 9; i++) {
                cgraph_rvec_push_back(&weights, 1);
            }
            int check = cgraph_get_shortest_path_dijkstra(g, &vpath, &epath, i_id1, i_id2, weights, CGRAPH_OUT);
            if(check == -1) {       //NEU KHONG CO DUONG DI -> IN -1
                printf("-1\n");
                break;
            }
            printf("\nKhoang cach nho nhat tu %s den %s = %d\n", id1, id2, cgraph_ivec_size(epath));

            cgraph_ivec_free(&vpath);
            cgraph_ivec_free(&epath);
            cgraph_rvec_free(&weights);
            break; 
        }

        case '6':{
            cgraph_ivec_free(&neis);
            cgraph_ivec_free(&res);
            cgraph_ivec_free(&edges);
            cgraph_destroy(&g);
            s2i_free(&s2i);
            gtv_free(&i2s);
            exit(0);
            break;
        }

    }
  }
  return 0;
}
    