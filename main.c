#include "Mylib.h"

int main(){
	char str[100];
	bn_tree_t s2i = s2i_create();
	bn_tree_t f2i = s2i_create();
	vector_t i2s = gtv_create();
	vector_t i2f = gtv_create();

	int i,j,Vsize,Esize,stusize;
	double w;
	cgraph_ivec_t edges=cgraph_ivec_create();
	cgraph_rvec_t weights=cgraph_rvec_create();
	cgraph_ivec_t stu=cgraph_ivec_create();

	cgraph_t g=NULL;

	for(;;){
		printf("Menu\n1. Nhap hoc phan\n2. Thoat\nLua chon cua ban: ");
		scanf("%d",&i);
		switch(i){
			case(1):{
				if(cgraph_ivec_size(edges)<=0){
					FILE *ptr=fopen("../hocphan.txt","r");
					if(ptr==NULL){
						printf("cant open hocphan.txt\n");
						break;
					}
					for(i=1,Vsize=Esize=0;fscanf(ptr,"%s",str)!=EOF;){
						if(i==1){
							if(strcmp(str,"0000")==0) i=2;
							else{
								simple_get_save_id(str, &s2i ,&i2s );
								fgets(str,80,ptr);
								str[strlen(str)-1]='\0';
								simple_get_save_id(str, &f2i ,&i2f );
								Vsize+=2;
							}
						}
						else{
							cgraph_ivec_push_back(&edges,s2i_value(s2i, str));
							fscanf(ptr,"%s",str);
							cgraph_ivec_push_back(&edges,s2i_value(s2i, str));
							Esize+=2;
						}
					}
					fclose(ptr);
					ptr=fopen("../passed.txt","r");
					if(ptr==NULL){
						printf("cant open passed.txt\n");
						break;
					}
					for(stusize=0;fscanf(ptr,"%s",str)!=EOF;){
						cgraph_ivec_push_back(&stu,s2i_value(s2i, str));
						stusize+=1;
					}
					fclose(ptr);
					g=cgraph_create(edges,Vsize,true);
				}
				printf("Nhap mot ma hoc phan: ");
				scanf("%s",str);
				j=s2i_value(s2i, str);
				if(j==k_s2i_invalid){
					printf("Khong tim thay ma hoc phan.\n");
				}
				else{

					if(i2i_value(stu,j)!=k_s2i_invalid) printf("Da hoan thanh hoc phan");
					else{
						for(i=0;i<cgraph_ivec_size(g->to);++i){
							if(j==g->to[i]) break;
						}
						if(i2i_value(g->to,j)!=k_s2i_invalid){
							cgraph_ivec_t neis=cgraph_ivec_create();
							cgraph_neighbors(g,&neis,j,CGRAPH_IN);
							for(i=0,j=0;i<cgraph_ivec_size(neis);++i){
								if(i2i_value(stu,neis[i])==k_s2i_invalid){
									if(j==0){
										printf("Khong dang ky duoc, can phai hoan thanh %s %s",i2s[neis[i]].s,i2f[neis[i]].s);
										j=1;
									}
									else printf(", %s %s",i2s[neis[i]].s,i2f[neis[i]].s);
								}
							}
							if(j==0) printf("Du dieu kien dang ky");
						}
						else printf("Du dieu kien dang ky");
					}
				}
				
				
				break;
			}
			case(2):{
				s2i_free(&s2i);
				gtv_free(&i2s);
				gtv_free(&i2f);
				cgraph_ivec_free(&edges);
				if(g!=NULL) cgraph_destroy(&g);
				printf("\n");
				return 0;
				break;
			}
		}
	}
}