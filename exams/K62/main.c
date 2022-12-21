#include "Mylib.h"

int main(){
	char x[10],y[10];
	bn_tree_t s2i = s2i_create();  
	vector_t i2s = gtv_create();
	int i,j,Vsize,Esize;
	double w;
	cgraph_ivec_t edges=cgraph_ivec_create();
	cgraph_rvec_t weights=cgraph_rvec_create();

	FILE *ptr=fopen("dothi.txt","r");
	if(ptr==NULL){
		printf("cant open input.txt\n");
		return -1;
	}
	fscanf(ptr,"%d %d",&Vsize,&Esize);
	for(i=0;i<Esize;++i){
		fscanf(ptr,"\n%s %s %lf",x,y,&w);
		cgraph_ivec_push_back(&edges,simple_get_save_id(x, &s2i ,&i2s ));
		cgraph_ivec_push_back(&edges,simple_get_save_id(y, &s2i ,&i2s ));
		cgraph_rvec_push_back(&weights,w);
	}

	fclose(ptr);
	cgraph_t g=cgraph_create(edges,Vsize,0);

	for(;;){
		printf("Menu\n1. Ma tran ke\n2. Danh sach ke\n3. Dua ra\n4. Duong di ngan nhat\n5. Duong di bo ngan nhat\n6. Thoat\nLua chon cua ban: ");
		scanf("%d",&i);
		switch(i){
			case(1):{
				int *MT=calloc(sizeof(int),Vsize* Vsize);
				for(i=0;i<Esize;++i){
					// printf("%s %s\n",i2s[g->from[i]].s,i2s[g->to[i]].s);
					MT[(atoi(i2s[g->from[i]].s)-1)*Vsize+(atoi(i2s[g->to[i]].s)-1)]=1;
					MT[(atoi(i2s[g->to[i]].s)-1)*Vsize+(atoi(i2s[g->from[i]].s)-1)]=1;
				}
				for(i=0;i<Vsize*Vsize;++i){
					if(i%Vsize==0) printf("\n");
					printf("%d ",MT[i]);

				}
				printf("\n");
				free(MT);
				break;
			}
			case(2):{
				for(i=1;i<=Vsize;++i){
					printf("Castle %d: ",i );
					sprintf(x,"%d",i);
					int res = s2i_value(s2i, x);
					cgraph_ivec_t neis=cgraph_ivec_create();
					cgraph_neighbors(g,&neis,res,CGRAPH_ALL);
					for(j=0;j<cgraph_ivec_size(neis);++j){
						printf("%s ",i2s[neis[j]].s );
					}
					cgraph_ivec_free(&neis);
					printf("\n");
				}
				break;
			}
			case(3):{
				printf("1. Danh sach thanh tri chi co the den bang cach di bo\n2. Danh sach thanh tri co nhieu duong di nhat\nLua chon cua ban: ");
				scanf("%d",&i);
				switch(i){
					case(1):{
						for(i=0;i<Vsize;++i){
							cgraph_ivec_t neis=cgraph_ivec_create();
							cgraph_neighbors(g,&neis,i,CGRAPH_ALL);
							for(j=0;j<cgraph_ivec_size(neis);++j){
								if(weight_between_2v(g,weights,i,neis[j])<50) break;
							}
							if(j==cgraph_ivec_size(neis)) printf("%s ", i2s[i].s);
							cgraph_ivec_free(&neis);
						}
						break;
					}
					case(2):{
						cgraph_ivec_t deg=cgraph_ivec_create();
						cgraph_degree_all(g,&deg,CGRAPH_ALL,false);
						int max;
						for(i=0,max=0;i<cgraph_ivec_size(deg);++i){
							if(deg[i]>max) max=deg[i];
						}
						for(i=0;i<cgraph_ivec_size(deg);++i){
							if(deg[i]==max) printf("%s ",i2s[i].s);
						}
						cgraph_ivec_free(&deg);
						break;
					}
				}
				printf("\n");
				break;
			}
			case(4):{
				printf("Nhap thanh xuat phat: ");
				scanf("%s",x);
				int res1 = s2i_value(s2i, x);    //search
			    if(res1 == k_s2i_invalid) { 
			        printf("Khong tim thay thanh tri da nhap\n");
			        break;                
			    }
				printf("Nhap thanh dich: ");
				scanf("%s",x);
				int res2 = s2i_value(s2i, x);    //search
			    if(res2 == k_s2i_invalid) { 
			        printf("Khong tim thay thanh tri da nhap\n");
			        break;                
			    }
			    cgraph_ivec_t vpath = cgraph_ivec_create(),
               	 			  epath = cgraph_ivec_create();
 				cgraph_get_shortest_path_dijkstra(g, &vpath, &epath, res1, res2, weights, CGRAPH_ALL);
	 			if(cgraph_ivec_size(vpath)>0){
	 				int sum;
	 				for(i=0,sum =0;i<cgraph_ivec_size(epath);++i){
	 					sum+=weights[epath[i]];
	 				}
	 				printf("Do dai duong di: %d\nDanh sach thanh tri di qua: ",sum );
	 				for(i=0;i<cgraph_ivec_size(vpath);++i){
	 					printf("%s ",i2s[vpath[i]].s);
	 				}
	 			}
	 			else printf("ROUTE NOT FOUND");
 				printf("\n" );
 				cgraph_ivec_free(&vpath);
 				cgraph_ivec_free(&epath);

			}
			case(5):{
				cgraph_ivec_t v=cgraph_ivec_create();
				cgraph_rvec_t ws=cgraph_rvec_create();
				for(i=0,j=0;i<Esize;++i){
					if(weights[i]>=50){
						cgraph_ivec_push_back(&v,g->from[i]);
						cgraph_ivec_push_back(&v,g->to[i]);
						cgraph_rvec_push_back(&ws,weights[i]);
					}
				}
				cgraph_t g1=cgraph_create(v,0,0);

				printf("Nhap thanh xuat phat: ");
				scanf("%s",x);
				int res1 = s2i_value(s2i, x);    //search
			    if(res1 == k_s2i_invalid) { 
			        printf("Khong tim thay thanh tri da nhap\n");
			        break;                
			    }
				printf("Nhap thanh dich: ");
				scanf("%s",x);
				int res2 = s2i_value(s2i, x);    //search
			    if(res2 == k_s2i_invalid) { 
			        printf("Khong tim thay thanh tri da nhap\n");
			        break;                
			    }
			    cgraph_ivec_t vpath = cgraph_ivec_create(),
               	 			  epath = cgraph_ivec_create();
 				cgraph_get_shortest_path_dijkstra(g1, &vpath, &epath, res1, res2, ws, CGRAPH_ALL);
	 			if(cgraph_ivec_size(vpath)>0){
	 				int sum;
	 				for(i=0,sum =0;i<cgraph_ivec_size(epath);++i){
	 					sum+=ws[epath[i]];
	 				}
	 				printf("Do dai duong di: %d\nDanh sach thanh tri di qua: ",sum );
	 				for(i=0;i<cgraph_ivec_size(vpath);++i){
	 					printf("%s ",i2s[vpath[i]].s);
	 				}
	 			}
	 			else printf("ROUTE NOT FOUND");
 				printf("\n" );
 				cgraph_ivec_free(&vpath);
 				cgraph_ivec_free(&epath);
 				cgraph_ivec_free(&v);
 				cgraph_rvec_free(&ws);
 				cgraph_destroy(&g1);

				printf("\n");
				break;
			}
			case(6):{
				s2i_free(&s2i);
				gtv_free(&i2s);
				cgraph_ivec_free(&edges);
				cgraph_rvec_free(&weights);
				cgraph_destroy(&g);
				printf("\n");
				return 0;
				break;
			}
		}
	}
}