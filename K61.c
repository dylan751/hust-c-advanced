#include "cgraph/cgraph.h"

#include <stdio.h>
#include <stdio_ext.h>
#include <string.h>

typedef struct {
    char ten_sp[30];
    int id_sp;      
} san_pham;

typedef struct {
    char ten_kh[30];
    int id_kh;      
    int so_luong[30];
} kho_hang;

int main() {
    char choice;
    int m, n, k;
    int i, j, h;    // Indexes

    san_pham SP[40];
    kho_hang KH[40];

    cgraph_ivec_t edges = cgraph_ivec_create();
    cgraph_ivec_t neis = cgraph_ivec_create();
    cgraph_rvec_t weights = cgraph_rvec_create();
    cgraph_t g;

    while(1){
        printf("           -------------------MENU-----------------\n"
               "|1. In ra cac loai san pham.                                    |\n"
               "|2. In ra khoang cach truc tiep giua kho A va B.                |\n"
               "|3. Kiem ke hang hoa tat ca kho hang.                          |\n"
               "|4. Kiem ke san pham cua kho hang A va cac kho hang lien ke.    |\n"
               "|5. Mua hang hoa.                                               |\n"
               "|6. Thoat.                                                      |\n");

        __fpurge(stdin);
        printf("Input your choice again: ");
        scanf("%c", &choice);

        while(choice > '6' || choice < '1'){
            __fpurge(stdin);
            printf("Ivalid! Input your choice: ");
            scanf("%c", &choice);
        }

        switch(choice) {
        case '1': {
            FILE *fptr1 = fopen("sanpham.txt", "r");
            if(fptr1 == NULL) {
                printf("Cannot open sanpham.txt!\n");
                return -1;
            }
            fscanf(fptr1, "%d", &m);    // So loai san pham
            
            for(i = 0; i < m; i++) {
                fscanf(fptr1, "%s %d", SP[i].ten_sp, &SP[i].id_sp);
            }
            printf("\n");
            for(i = 0; i < m; i++) {
                printf("%s %d\n", SP[i].ten_sp, SP[i].id_sp);
            }
            printf("\n");
            fclose(fptr1);
            break;
        }

        case '2': {
            /*------------------------DOC FILE + TAO DO THI---------------------*/
            int id_tmp, so_luong_tmp;

            FILE* fptr2 = fopen("khohang.txt", "r");
            fscanf(fptr2, "%d", &n);    // So kho hang
            for(i = 0; i < n; i++) {
                fscanf(fptr2, "%s %d", KH[i].ten_kh, &KH[i].id_kh);
                for(j = 0; j < m; j++) {
                    fscanf(fptr2, "%d %d", &id_tmp, &so_luong_tmp);
                    for(h = 0; h < m; h++) {
                        if(SP[h].id_sp == id_tmp) {
                            KH[i].so_luong[h] = so_luong_tmp;
                        }
                    }
                }
            }

            // for(i = 0; i < n; i++) {
            //     printf("Kho hang: %s, id: %d\n", KH[i].ten_kh, KH[i].id_kh);
            //         printf("1: %d, 2: %d, 3: %d\n", KH[i].so_luong[0], KH[i].so_luong[1], KH[i].so_luong[2]);
            // }
            int id1, id2;
            double w;
            fscanf(fptr2, "%d", &k);
            for(i = 0; i < k; i++) {
                fscanf(fptr2, "%d %d %lf", &id1, &id2, &w);
                cgraph_ivec_push_back(&edges, id1);
                cgraph_ivec_push_back(&edges, id2);
                cgraph_rvec_push_back(&weights, w);
            }
            g = cgraph_create(edges, 0, false);
            // cgraph_print(g);
            /*--------------------------------------------------------------------*/
            int mark = 0; // Khong co dap an
            printf("Nhap id kho 1: ");
            scanf("%d", &id1);
            printf("Nhap id kho 2: ");
            scanf("%d", &id2);

            for(i = 0; i < n; i++) {
                if((g->from[i] == id1 && g->to[i] == id2) || (g->from[i] == id2 && g->to[i] == id1)) {
                    printf("%.2lf km\n", weights[i]);
                    mark = 1; // Co dap an
                }
            }

            if(mark == 0) {
                printf("-1\n");
            }
            fclose(fptr2);
            break;
        }

        case '3': {
            for(i = 0; i < n; i++) {
                printf("%s\n", KH[i].ten_kh);
                for(j = 0; j < m; j++) {
                    printf("%s %d\n", SP[j].ten_sp, KH[i].so_luong[j]);
                }
                printf("----\n");
            }
            break;
        }

        case '4': {
            int id_sp_temp;  // id muon kiem ke
            int id_kh_temp; // Kho hang muon kiem ke
            printf("Nhap id san pham muon kiem ke: ");
            scanf("%d", &id_sp_temp);
            printf("Nhap id kho hang muon kiem ke: ");
            scanf("%d", &id_kh_temp);

            for(i = 0; i < n; i++) {
                if(id_kh_temp == KH[i].id_kh) {
                    cgraph_neighbors(g, &neis, KH[i].id_kh, CGRAPH_ALL);
                }
            }

            /*------------------IN RA CAC KHO HANG TRUC TIEP---------------*/
            printf("%s\n", KH[id_kh_temp-1].ten_kh);
            printf("%s %d\n", SP[id_sp_temp-1].ten_sp, KH[id_kh_temp-1].so_luong[id_sp_temp-1]);

            /*-------------------IN RA CAC KHO HANG LIEN KE----------------*/
            printf("--- Cac kho ke la:\n");
            for(i = 0; i < cgraph_ivec_size(neis); i++) {
                for(j = 0; j < n; j++) {
                    if(neis[i] == KH[j].id_kh) {
                        printf("%s\n", KH[j].ten_kh);
                        k = j;  // Luu gia tri cua kho hang dang xet -> xuong duoi dùng đến
                    }
                }
                
                /*---TIM SO LUONG SAN PHAM CUA ID NHAP VAO O MOI KHO HANG---*/
                for(j = 0; j < m; j++) {
                    if(id_sp_temp == SP[j].id_sp) {
                        printf("%s %d\n", SP[j].ten_sp, KH[k].so_luong[j]);
                    }
                }
            }
            break;
        }

        case '5': {
            int id_sp_temp, so_luong_temp, id_kh_temp, id_kh_2;
            printf("Nhap id san pham muon mua: ");
            scanf("%d", &id_sp_temp);
            while(id_sp_temp < 1 || id_sp_temp > 3) {
                printf("0 < ID < 4! Nhap lai: ");
                scanf("%d", &id_sp_temp);
            }
            printf("Nhap so luong muon mua: ");
            scanf("%d", &so_luong_temp);
            while(so_luong_temp < 0) {
                printf("So luong > 0! Nhap lai: ");
                scanf("%d", &so_luong_temp);
            }
            printf("Nhap kho hang gan nhat: ");
            scanf("%d", &id_kh_temp);
            while(id_kh_temp < 1 || id_kh_temp > 3) {
                printf("0 < ID kho hang < 4! Nhap lai: ");
                scanf("%d", &id_kh_temp);
            }
            printf("Nhap kho hang du phong: ");
            scanf("%d", &id_kh_2);
            while(id_kh_2 < 1 || id_kh_2 > 3) {
                printf("0 < ID kho hang < 4! Nhap lai: ");
                scanf("%d", &id_kh_2);
            }

            /*---------------NEU KHO HANG GAN NHAT CO DU SAN PHAM--------------*/
            if(so_luong_temp <= KH[id_kh_temp-1].so_luong[id_sp_temp-1]) {
                printf("Dat hang thanh cong!\nThoi gian giao hang la %d phut\n", 30);
            }
            /*--------------NEU KHO HANG GAN NHAT KHONG DU SAN PHAM------------*/
            else {
                int sum; // Tong so luong cua 2 cua hang
                sum = KH[id_kh_temp-1].so_luong[id_sp_temp-1] + KH[id_kh_2-1].so_luong[id_sp_temp-1];

                /*--------------NEU TONG 2 KHO HANG GAN NHAT DU SAN PHAM------------*/
                if(so_luong_temp <= sum) {
                    /*Tim khoang cach cua 2 cua hang*/
                    for(j = 0; j < m; j++) {
                        if((g->from[j] == id_kh_temp && g->to[j] == id_kh_2) || (g->from[j] == id_kh_2 && g->to[j] == id_kh_temp))
                        printf("Dat hang thanh cong!\nThoi gian giao hang la %.2lf phut\n", (weights[j]/30)*60 + 30);
                    }
                }
                /*-------------NEU TONG 2 KHO HANG GAN NHAT KO DU SAN PHAM-----------*/
                else {
                    printf("Dat hang khong thanh cong!\n");
                }
            }


            break;
        }

        case '6': {
            cgraph_destroy(&g);
            cgraph_ivec_free(&edges);
            cgraph_rvec_free(&weights);
            cgraph_ivec_free(&neis);
            exit(0);
            break;
        }

        }
    }
    return 0;
}