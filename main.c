#include "Mylib.h"

int main(){
	char str[100],c;
	bn_tree_t s2i = s2i_create();
	vector_t i2s = gtv_create();

	int i,j,Vsize,Esize,x,y;
	double w;
	cgraph_ivec_t edges=cgraph_ivec_create();

	cgraph_t g=NULL;

	for(;;){
		printf("Menu\n1. Doc file\n2. Danh sach tiep xuc gan\n3. Kiem tra tiep xuc gan\n4. Danh sach tiep xuc gan cua 1 nguoi\n5. Danh sach nhung nguoi tiep xuc gan nhieu nhat\n6. Danh sach F1, F2\n7. Cap nhat danh sach\n8. Cap nhat tiep xuc gan\n9. In ra file\n10. Thoat\nLua chon cua ban: ");
		scanf("%d",&i);
		if(cgraph_ivec_size(edges)<=0&&i>1&&i<10) continue;
		switch(i){
			case(1):{
				if(cgraph_ivec_size(edges)<=0){
					FILE *ptr=fopen("tiepXucGan.txt","r");
					if(ptr==NULL){
						printf("cant open tiepXucGan.txt\n");
						break;
					}
					fscanf(ptr,"%d",&Vsize);
					for(i=0,str[1]='\0';i<Vsize;++i){
						str[0]='A'+i;
						simple_get_save_id(str, &s2i ,&i2s );
					}
					for(i=1;(c=fgetc(ptr))!=EOF;){
						if(c==' '||c=='\n'){
							if(i==1){
								x=simple_get_save_id(str, &s2i ,&i2s );
								i=2;
							}
							else{
								y=simple_get_save_id(str, &s2i ,&i2s );
								if(y>x){
									cgraph_ivec_push_back(&edges,x);
									cgraph_ivec_push_back(&edges,y);
									Esize++;
								}

							}
							if(c=='\n') i=1;
						}
						else{
							str[0]=c;
						}
						
					}
					fclose(ptr);
					g=cgraph_create(edges,Vsize,0);
					cgraph_ivec_print(edges);
					cgraph_print(g);
				}
				
				
				break;
			}
			case(2):{
				for(i=0;i<Vsize;++i){
					cgraph_ivec_t neis=cgraph_ivec_create();
					if(cgraph_neighbors(g,&neis,i,CGRAPH_ALL)!=-1){
						printf("%s ",i2s[i].s );
						for(x=0,y=cgraph_ivec_size(neis);x<y;++x){
							printf("%s ",i2s[neis[x]].s );
						}
					}
					printf("\n");
					cgraph_ivec_free(&neis);
				}
				
				break;
			}
			case(3):{
				printf("Nhap nguoi thu nhat: ");
				scanf("%s",str);
				x=s2i_value(s2i,str);
				for(;x==k_s2i_invalid;){
					printf("Nguoi ban vua nhap khong ton tai. Nhap lai nguoi thu nhat: ");
					scanf("%s",str);
					x=s2i_value(s2i,str);
				}
				printf("Nhap nguoi thu hai: ");
				scanf("%s",str);
				y=s2i_value(s2i,str);
				for(;y==k_s2i_invalid;){
					printf("Nguoi ban vua nhap khong ton tai. Nhap lai nguoi thu hai: ");
					scanf("%s",str);
					y=s2i_value(s2i,str);
				}
				cgraph_ivec_t neis=cgraph_ivec_create();
				if(cgraph_neighbors(g,&neis,x,CGRAPH_ALL)!=-1){
					for(i=0,j=cgraph_ivec_size(neis);i<j;++i){
						if(neis[i]==y) break;
					}
					if(i<j) printf("Hai nguoi co tiep xuc gan\n");
					else printf("Hai nguoi khong co tiep xuc gan\n");
				}
				else printf("Hai nguoi khong co tiep xuc gan\n");
				cgraph_ivec_free(&neis);
				break;
			}
			case(4):{
				printf("Nhap nguoi muon kiem tra: ");
				scanf("%s",str);
				i=s2i_value(s2i,str);
				for(;i==k_s2i_invalid;){
					printf("Nguoi ban vua nhap khong ton tai. Nhap lai: ");
					scanf("%s",str);
					i=s2i_value(s2i,str);
				}
				printf("Danh sach tiep xuc gan cua %s la: ",str);
				cgraph_ivec_t neis=cgraph_ivec_create();
				if(cgraph_neighbors(g,&neis,i,CGRAPH_ALL)!=-1){
					for(x=0,y=cgraph_ivec_size(neis);x<y;++x){
						printf("%s ",i2s[neis[x]].s );
					}
				}
				printf("\n");
				cgraph_ivec_free(&neis);
				break;
			}
			case(5):{
				cgraph_ivec_t deg=cgraph_ivec_create();
				printf("Danh sach nhung nguoi tiep xuc gan nhieu nhat la: ");
				if(cgraph_degree_all(g,&deg,CGRAPH_ALL,false)!=-1){
					for(i=1,j=cgraph_ivec_size(deg),x=deg[0];i<j;++i){
						if(x<deg[i]) x=deg[i];
					}
					for(i=0;i<j;++i){
						if(deg[i]==x) printf("%s ",i2s[i].s);
					}
				}
				printf("\n");
				cgraph_ivec_free(&deg);
				break;
			}
			case(6):{
				cgraph_ivec_t F0=cgraph_ivec_create();
				cgraph_ivec_init(&F0,Vsize);
				cgraph_ivec_fill(F0,-1);
				printf("Nhap nguoi la F0: ");
				scanf("%s",str);
				i=s2i_value(s2i,str);
				for(;i==k_s2i_invalid;){
					printf("Nguoi ban vua nhap khong ton tai. Nhap lai: ");
					scanf("%s",str);
					i=s2i_value(s2i,str);
				}
				F0[i]=0;
				
				cgraph_ivec_t neis=cgraph_ivec_create();
				if(cgraph_neighbors(g,&neis,i,CGRAPH_ALL)!=-1){
					for(x=0,y=cgraph_ivec_size(neis);x<y;++x){
						if(F0[neis[x]]==-1) F0[neis[x]]=1;
					}
					for(x=0;x<y;++x){
						cgraph_ivec_t neis2=cgraph_ivec_create();
						if(cgraph_neighbors(g,&neis2,neis[x],CGRAPH_ALL)!=-1){
							for(i=0,j=cgraph_ivec_size(neis2);i<j;++i){
								if(F0[neis2[i]]==-1) F0[neis2[i]]=2;
							}
						}
						cgraph_ivec_free(&neis2);
					}
				}
				cgraph_ivec_free(&neis);

				printf("Danh sach F1 la: ");
				for(i=0;i<Vsize;++i){
					if(F0[i]==1) printf("%s ",i2s[i].s);
				}

				printf("\nDanh sach F2 la: ");
				for(i=0;i<Vsize;++i){
					if(F0[i]==2) printf("%s ",i2s[i].s);
				}
				printf("\n");

				cgraph_ivec_free(&F0);
				break;
			}
			case(7):{
				printf("Nhap nguoi muon them: ");
				scanf("%s",str);
				x=simple_get_save_id(str,&s2i,&i2s);
				for(;x<Vsize;){
					printf("Nguoi ban vua nhap da ton tai. Nhap lai: ");
					scanf("%s",str);
					x=simple_get_save_id(str,&s2i,&i2s);
				}
				cgraph_add_vertices(g,x);
				Vsize+=1;
				for(i=0;i<Vsize-1;++i){
					printf("Ban co muon cap nhat tiep xuc cho %s,1. Co\t2. Khong\nLua chon cua ban: ",i2s[i].s);
					scanf("%d",&j);
					for(;j!=1&&j!=2;){
						printf("Nhap lai: ");
						scanf("%d",&j);
					}
					if(j==1){
						cgraph_ivec_t ed=cgraph_ivec_create();
						cgraph_ivec_push_back(&ed,x);
						cgraph_ivec_push_back(&ed,i);
						cgraph_add_edges(g,ed);
						printf("Cap nhat thanh cong\n");
						cgraph_ivec_free(&ed);
					}
				}
				break;
			}
			case(8):{
				printf("Nhap nguoi thu nhat: ");
				scanf("%s",str);
				x=s2i_value(s2i,str);
				for(;x==k_s2i_invalid;){
					printf("Nguoi ban vua nhap khong ton tai. Nhap lai nguoi thu nhat: ");
					scanf("%s",str);
					x=s2i_value(s2i,str);
				}
				printf("Nhap nguoi thu hai: ");
				scanf("%s",str);
				y=s2i_value(s2i,str);
				for(;y==k_s2i_invalid;){
					printf("Nguoi ban vua nhap khong ton tai. Nhap lai nguoi thu hai: ");
					scanf("%s",str);
					y=s2i_value(s2i,str);
				}
				cgraph_ivec_t neis=cgraph_ivec_create();
				if(cgraph_neighbors(g,&neis,x,CGRAPH_ALL)!=-1){
					for(i=0,j=cgraph_ivec_size(neis);i<j;++i){
						if(neis[i]==y) break;
					}
					if(i<j) printf("Hai nguoi da co tiep xuc gan\n");
					else{
						cgraph_ivec_t ed=cgraph_ivec_create();
						cgraph_ivec_push_back(&ed,x);
						cgraph_ivec_push_back(&ed,y);
						cgraph_add_edges(g,ed);
						printf("Cap nhat thanh cong\n");
						cgraph_ivec_free(&ed);
					}
				}
				cgraph_ivec_free(&neis);
				break;
			}
			case(9):{
				FILE *ptr=fopen("ketQua.txt","w");
				if(ptr==NULL){
					printf("cant open ketQua.txt\n");
					break;
				}
				fprintf(ptr,"%d",Vsize);
				for(i=0;i<Vsize;++i){
					fprintf(ptr,"\n");
					cgraph_ivec_t neis=cgraph_ivec_create();
					if(cgraph_neighbors(g,&neis,i,CGRAPH_ALL)!=-1){
						fprintf(ptr,"%s ",i2s[i].s );
						for(x=0,y=cgraph_ivec_size(neis);x<y;++x){
							fprintf(ptr,"%s ",i2s[neis[x]].s );
						}
					}
					cgraph_ivec_free(&neis);
				}
				fclose(ptr);
				break;
			}
			case(10):{
				s2i_free(&s2i);
				gtv_free(&i2s);
				cgraph_ivec_free(&edges);
				if(g!=NULL) cgraph_destroy(&g);
				printf("\n");
				return 0;
				break;
			}
		}
	}
}