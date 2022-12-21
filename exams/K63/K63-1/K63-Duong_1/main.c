#include <stdio.h>
#include <string.h>
#include "cgen/gtvector.h"
#include "cgen/gtype.h"
#include "cgraph/cgraph.h"
#include "cgen/s2i.h"
#include "cgen/svector.h"
int main(int argc, char const *argv[])
{
	FILE *f = fopen("../data.txt","r");
	vector_t vertexs = gtv_create();//luu ten dinh
	cgraph_ivec_t i_vertexs = cgraph_ivec_create();//luu id dinh
	cgraph_ivec_t edges = cgraph_ivec_create();//luu canh
	cgraph_rvec_t weights = cgraph_rvec_create();//luu trong so canh
	cgraph_ivec_t neis = cgraph_ivec_create();//luu dinh ke
	int i_temp,temp1,temp2,m,n; // doc id dinh
	char s_temp[10];//doc ten dinh
	int ds[m*2];// mang luu from va to cua graph
	float weight;// doc trong so
	int flag,first,second,count=0,chung[6];
	int chose;// bien lua chon
	int id_for_search;
	double max = 0;
	int max_index=0;
	//doc file
	fscanf(f,"%d %d",&m,&n);
	for (int i = 0; i < 6; ++i)
	{
		fscanf(f,"%d %s\n",&i_temp,s_temp);
		svec_push_back(&vertexs, s_temp);
		cgraph_ivec_push_back(&i_vertexs, i_temp);
	}
	while(fscanf(f,"%d %d %f\n",&temp1, &temp2, &weight)>0){
		//printf("%d %d %f\n",temp1,temp2,weight );
		cgraph_ivec_push_back(&edges, temp1);
		cgraph_ivec_push_back(&edges, temp2); 
		cgraph_rvec_push_back(&weights, weight);
	}
	//tao do thi
	cgraph_t g = cgraph_create(edges, 0, CGRAPH_UNDIRECTED);
	//menu chay
	while(chose != 5){
		printf("------------Menu------------\n");
		printf("1. In danh sach dinh\n");
		printf("2. Tim ban than nhat\n");
		printf("3. Kiem tra quan he bac cau\n");
		printf("4. Tim ban chung\n");
		printf("5. Thoat\n");
		printf("Nhap lua chon cua ban: ");scanf("%d%*c",&chose);
		switch(chose){
			case 1:
				// in danh sach dinh cua do thi
				printf("Danh sach dinh: \n");
				for (int i = 0; i < m; ++i)
				{
					ds[i] = g->from[i];
				}
				for (int i = m; i < m*2; ++i)
				{
					ds[i] = g->to[i-m];
				}
				for (int i = 0; i < m*2; ++i)
				{
					flag = 1;
					for (int j = 0; j < i; ++j)
					{
						if(ds[j] == ds[i]) flag = 0;
					}
					if(flag ==1 ){
						for (int j = 0; j < cgraph_ivec_size(i_vertexs); ++j)
						{
							if (ds[i] == i_vertexs[j])
							{
								printf("%d: %s\n",i_vertexs[j],vertexs[j].s  );
								break;
							}
						}
						
					} 
				}
				break;
			case 2: 
				printf("Nhap id: ");scanf("%d",&id_for_search);
				cgraph_neighbors(g,&neis,id_for_search,CGRAPH_ALL);
				if(cgraph_ivec_size(neis)==0){
					printf("-1\n");
					break;
				}
				cgraph_ivec_print(neis);
				cgraph_rvec_print(weights);
				flag = 0;
				for (int i = 0; i < m; ++i)
				{
					if(g->from[i]==neis[flag]){
						flag++;
						if(max < weights[i]){
							max_index = i;
							max = weights[max_index];
						}
					}
				}
				printf("%.1lf\n",max);
				for (int i = 0; i < cgraph_ivec_size(neis); ++i)
				{
					for (int j = 0; j < cgraph_ivec_size(i_vertexs); ++j)
						{
							if (neis[i] == i_vertexs[j])
							{
								printf("%d %s\n",i_vertexs[j],vertexs[j].s  );
								break;
							}
						}
				}
				break;
			case 3:
				printf("Nhap id thu nhat: ");scanf("%d",&first);
				printf("Nhap id thu hai: ");scanf("%d",&second);
				cgraph_ivec_t father = cgraph_ivec_create(), 
				  				dist = cgraph_ivec_create();
				cgraph_simple_bfs(g,first,CGRAPH_ALL, false, &father, &dist);
				//cgraph_ivec_print(dist);
				flag = 0;
				for (int i = 0; i < cgraph_ivec_size(dist); ++i)
				{
					if(second == i_vertexs[i-1] && dist[i]>1){
						printf("1\n");
						flag = 1;
						break;
						
					}	
				}
				if(flag == 0) printf("-1\n");
				break;
			case 4:
				printf("Nhap id thu nhat: ");scanf("%d",&first);
				printf("Nhap id thu hai: ");scanf("%d",&second);
				cgraph_ivec_t neis_f = cgraph_ivec_create();
				cgraph_ivec_t neis_s = cgraph_ivec_create();
				cgraph_neighbors(g,&neis_f,first,CGRAPH_ALL);
				cgraph_neighbors(g,&neis_s,second,CGRAPH_ALL);
				//cgraph_ivec_print(neis_f);
				//cgraph_ivec_print(neis_s);
				for (int i = 0; i < cgraph_ivec_size(neis_s); ++i)
				{
					for (int j = 0; j < cgraph_ivec_size(neis_f); ++j)
					{
						if(neis_s[i]==neis_f[j]){
							//printf("%d %d\n", neis_s[i],neis_f[j]);
							chung[count] = neis_f[j];
							count++;
						}
					}
				}
				if (count == 0)
				{
					printf("-1\n");
					break;
				}
				printf("%d\n",count);
				for (int i = 0; i < count; ++i)
				{
					for (int j = 0; j < cgraph_ivec_size(i_vertexs); ++j)
					{
						if (chung[i] == i_vertexs[j])
						{
								printf("%d %s\n",i_vertexs[j],vertexs[j].s  );
								break;
						}
					}
				}
				break;
			default: break;
		}
	}
	return 0;
}