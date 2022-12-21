#include"cgraph/cgraph.h"
#include<stdio.h>
#include <string.h>
#include "cgen/s2i.h"
#include "cgen/svector.h"
#include "NN.h"


bn_tree_t s2i = NULL; //cay chua string -> int
vector_t i2s = NULL;  // vector cac string theo chi so int
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

int cgraph_is_found(cgraph_t g,int IDr,int IDf){
	int i;
	for(i=g->os[IDr];i<g->os[IDr+1];++i){
		// printf("%s %s %s\n",i2s[g->to[g->oi[i]]].s,i2s[IDf].s,i2s[IDr].s);
		if(g->to[g->oi[i]]==IDf){// check
			// printf("1 FOUND!\n");
			return 1;
		}
	}

	for(i=g->is[IDr];i<g->is[IDr+1];++i){
		// printf("%s %s %s\n",i2s[g->from[g->ii[i]]].s,i2s[IDf].s,i2s[IDr].s);
		if(g->from[g->ii[i]]==IDf){// check
			// printf("2 FOUND!\n");
			return 1;
		}
	}
	return 0;
}

int main(){
	s2i = s2i_create();  
	i2s = gtv_create();
	NN *i2n=NULL;
	int i,size,Esize;
	double w;
	cgraph_ivec_t edges=cgraph_ivec_create();
	cgraph_rvec_t weights=cgraph_rvec_create();
	char s1[100],s2[100];

	cgraph_t g;

	for(i=0;;){
		printf("Menu\n1.In danh sach dinh\n2.Tim ban than thiet nhat\n3.Kiem tra quan he bac cau\n4.Tim ban chung\n5. Thoat\nNhap lua chon: ");
		scanf("%d",&i);
		if(i==1){
			FILE *ptr=fopen("data.txt","r");
			if(ptr==NULL){
				printf("cant open input.txt\n");
			}
			else{
				fscanf(ptr,"%d %d",&Esize,&size);
				for(i=0;i<Esize;++i){
					fscanf(ptr,"\n%s %s",s1,s2);
					insertNN(&i2n,s1,s2);
				}
				for(i=0;i<size;++i){
					fscanf(ptr,"\n%s %s %lf",s1,s2,&w);
					cgraph_ivec_push_back(&edges,get_save_id(s1));
					cgraph_ivec_push_back(&edges,get_save_id(s2));
					cgraph_rvec_push_back(&weights,w);
				}
				fclose(ptr);
				g=cgraph_create(edges,size,0);

				printf("Danh sach dinh:\n");
				NN_print(i2n);
			}
		}
		else if(i==2){
			if(i2n==NULL) continue;
			printf("Nhap ID: ");
			scanf("%s", s1);
			int res = s2i_value(s2i, s1);    //search
		    if(res != k_s2i_invalid) {
		    	int* near=(int*)malloc(sizeof(int)*(g->os[res+1]-g->os[res]));
		    	int n=0;
		    	double max=weights[g->oi[g->os[res]]];

				for(i=g->os[res];i<g->os[res+1];++i){
					if(weights[g->oi[i]]>max){// so sanh
						n=0;
						max=weights[g->oi[i]];
					}
					if(weights[g->oi[i]]==max){
						near[n]=g->to[g->oi[i]];//luu ID vao danh sach
						++n;
					}
				}

				for(i=g->is[res];i<g->is[res+1];++i){
					if(weights[g->ii[i]]>max){// so sanh
						n=0;
						max=weights[g->ii[i]];
					}
					if(weights[g->ii[i]]==max){
						near[n]=g->from[g->ii[i]];//luu ID vao danh sach
						++n;
					}
				}

				if(n!=0){
					printf("%-3lf\n",max);
					for(i=0;i<n;++i){
						NN_name_print(NN_search(i2n,i2s[near[i]].s));
					}
				}
				

				free(near);
		    }
		}
		else if(i==3){
			if(i2n==NULL) continue;
			printf("Nhap ID nguoi thu nhat: ");
			scanf("%s", s1);
			printf("Nhap ID nguoi thu hai: ");
			scanf("%s", s2);

			if(cgraph_is_found(g,get_save_id(s1), get_save_id(s2))) printf("-1");
		 	else printf("1");
			printf("\n");
		}
		else if(i==4){
			if(i2n==NULL) continue;
			printf("Nhap ID nguoi thu nhat: ");
			scanf("%s", s1);
			int res1 = s2i_value(s2i, s1);
			printf("Nhap ID nguoi thu hai: ");
			scanf("%s", s2);
			int res2 = s2i_value(s2i, s2);
			if(res1 != k_s2i_invalid&&res1 != k_s2i_invalid) {
		    	int* near=(int*)malloc(sizeof(int)*(g->os[res1+1]-g->os[res1]));
		    	int n=0;

				for(i=g->os[res1];i<g->os[res1+1];++i){
					if(cgraph_is_found(g,res2,g->to[g->oi[i]])){// check
						near[n]=g->to[g->oi[i]];//luu ID vao danh sach
						++n;
					}
					
				}

				for(i=g->is[res1];i<g->is[res1+1];++i){
					if(cgraph_is_found(g,res2,g->from[g->ii[i]])){// check
						near[n]=g->from[g->ii[i]];//luu ID vao danh sach
						++n;
					}
				}

				if(n!=0){
					printf("%d\n",n);
					for(i=0;i<n;++i){
						NN_name_print(NN_search(i2n,i2s[near[i]].s));
					}
				}
				else printf("-1\n");

				free(near);
		    }
		    else printf("-1\n");

		}
		else if(i==5){
			break;
		}
	}

	
	s2i_free(&s2i);
	gtv_free(&i2s);
	NN_free(&i2n);
	return 0;
}
