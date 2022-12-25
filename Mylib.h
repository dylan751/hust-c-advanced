#ifndef MY_LIB_H
#define MY_LIB_H

#include<stdio.h>
#include <string.h>
#include "cgraph/cgen/s2i.h"
#include "cgraph/cgen/svector.h"
#include"cgraph/cgraph.h"

int i2i_value(cgraph_ivec_t i2i,int key){
	int res;
	for(res=0;res<cgraph_ivec_size(i2i);++res){
    	if(key==i2i[res]) return res;
    }
    return k_s2i_invalid;
}

int get_save_id(int key,char *fullstr, cgraph_ivec_t* i2i , bn_tree_t *s2i,vector_t *i2s ) {
    int res;
    if(key==k_s2i_invalid&& fullstr==NULL) return k_s2i_invalid;
    
    if(key!=k_s2i_invalid){ //search
		res = i2i_value(*i2i, key);    //search
	    if(res != k_s2i_invalid) {        //Nếu tìm thấy -> return
	        return res;                 
	    }
    }
    if(fullstr!=NULL){
    	res = s2i_value(*s2i, fullstr);    //search
	    if(res != k_s2i_invalid) {        //Nếu tìm thấy -> return
	        return res;                 
	    }
    }
    
    //Nếu không tìm thấy -> insert
    
    if(i2s!=NULL) {
    	res=gtv_size(*i2s);
	    svec_push_back(i2s, fullstr);
	    s2i_insert(*s2i, fullstr, res);       //Nếu không tìm thấy -> insert
    	// printf("string: %s\n",fullstr );
    	// printf("saved : %s\n",(*i2s)[res].s );
    }
    if(i2i!=NULL){
    	res=cgraph_ivec_size(*i2i);
    	cgraph_ivec_push_back(i2i,key);
    	// printf("key  : %d\n",key );
    	// printf("saved: %d\n\n",(*i2i)[res] );
    }       
    return res;
}

int int_get_save_id(int key, cgraph_ivec_t *i2i ) {

    return get_save_id(key,NULL ,i2i,NULL,NULL);
}

int simple_get_save_id(char *fullstr, bn_tree_t *s2i ,vector_t *i2s ) {
    
    return get_save_id(k_s2i_invalid,fullstr, NULL, s2i , i2s );
}

cgraph_t cgraph_reverse(cgraph_t g){
	cgraph_ivec_t edges=cgraph_ivec_create();
	int i;
	for(i=0;i<cgraph_ivec_size(g->from);++i){
		cgraph_ivec_push_back(&edges,g->to[i]);
		cgraph_ivec_push_back(&edges,g->from[i]);
	}
	return cgraph_create(edges,g->n,g->directed);
}


int  thanh_phan_lien_thong_manh_find(cgraph_t g,CGRAPH_INTEGER find,cgraph_ivec_t* tpltm){
	cgraph_t r = cgraph_reverse(g);
	int count,i,j;

	cgraph_ivec_t order     = cgraph_ivec_create(),
	              order_out = cgraph_ivec_create(),
	              father    = cgraph_ivec_create(),
	              dist      = cgraph_ivec_create();
	if(g->directed) cgraph_dfs(g, 0, CGRAPH_OUT, true, &order, &order_out, &father, &dist);
	else cgraph_dfs(g, 0, CGRAPH_ALL, true, &order, &order_out, &father, &dist);

	bool *visited = calloc(g->n,sizeof(bool));

	for(count=0,i=cgraph_ivec_size(order_out)-1;i>=0;--i){
		if(!visited[order_out[i]]){
			cgraph_ivec_t rorder     = cgraph_ivec_create(),
			              rorder_out = cgraph_ivec_create(),
			              rfather    = cgraph_ivec_create(),
			              rdist      = cgraph_ivec_create();

			cgraph_dfs(r, order_out[i], CGRAPH_OUT, false, &rorder, &rorder_out, &rfather, &rdist);

			if(find>=0&&find<g->n){
				for(j=0;rorder[j]!=CGRAPH_NAN;++j){

					if(rorder[j]==find){					//Tim thay
						for(j=0;rorder[j]!=CGRAPH_NAN;++j){
							if(!visited[rorder[j]]) cgraph_ivec_push_back(tpltm,rorder[j]);
						}

						return 1;
					}

				}
			}

			for(j=0;rorder[j]!=CGRAPH_NAN;++j){				//Danh dau da duyet qua
				if(!visited[rorder[j]]) visited[rorder[j]]=true;
			}

			++count;

			cgraph_ivec_free(&rorder);
			cgraph_ivec_free(&rorder_out);
			cgraph_ivec_free(&rfather);
			cgraph_ivec_free(&rdist);
		}
		
	}

	cgraph_ivec_free(&order);
	cgraph_ivec_free(&order_out);
	cgraph_ivec_free(&father);
	cgraph_ivec_free(&dist);
	free(visited);

	if(find<0) return count;
	else return 0;
}

int  thanh_phan_lien_thong_manh_count(cgraph_t g){
	return thanh_phan_lien_thong_manh_find(g,-1,NULL);
}

int thanh_phan_lien_thong_find(cgraph_t g,CGRAPH_INTEGER find,cgraph_ivec_t* tplt){
	int i,n;
	cgraph_ivec_t order     = cgraph_ivec_create(),
	              order_out = cgraph_ivec_create(),
	              father    = cgraph_ivec_create(),
	              dist      = cgraph_ivec_create();
	cgraph_dfs(g, find, CGRAPH_ALL, false, &order, &order_out, &father, &dist);
	for(i=0,n=cgraph_ivec_size(dist);i<n;++i){
		if(dist[i]>=0) cgraph_ivec_push_back(tplt,i);
	}
	cgraph_ivec_free(&order);
	cgraph_ivec_free(&order_out);
	cgraph_ivec_free(&father);
	cgraph_ivec_free(&dist);
	if(i==0) return 0;
	else return 1;
}

int thanh_phan_lien_thong_count(cgraph_t g){
	int count,i;
	cgraph_ivec_t order     = cgraph_ivec_create(),
	              order_out = cgraph_ivec_create(),
	              father    = cgraph_ivec_create(),
	              dist      = cgraph_ivec_create();
	cgraph_dfs(g, 0, CGRAPH_ALL, true, &order, &order_out, &father, &dist);
	for(count=i=0;i<cgraph_ivec_size(father);++i){
		if(father[i]==-1) ++count;
	}
	cgraph_ivec_free(&order);
	cgraph_ivec_free(&order_out);
	cgraph_ivec_free(&father);
	cgraph_ivec_free(&dist);
	return count;
}

int tplt_find(cgraph_t g,CGRAPH_INTEGER find,cgraph_ivec_t* tplt){
	if(find>=g->n||find<0) return 0;
	if(g->directed) thanh_phan_lien_thong_manh_find(g,find,tplt);
	else thanh_phan_lien_thong_find(g,find,tplt);
}

int tplt_count(cgraph_t g){
	if(g->directed) return thanh_phan_lien_thong_manh_count(g);
	else return thanh_phan_lien_thong_count(g);
}

double weight_between_2v(cgraph_t g,cgraph_rvec_t weights,CGRAPH_INTEGER a,CGRAPH_INTEGER b){
	int i;
	double rab;
	cgraph_ivec_t vpath = cgraph_ivec_create(),
               	 epath = cgraph_ivec_create();
 	cgraph_get_shortest_path_dijkstra(g, &vpath, &epath, a, b, weights, CGRAPH_ALL);
 	
 	for(i=0,rab=0;i<cgraph_ivec_size(epath);++i){
 		rab+=weights[epath[i]];
 	}

 	cgraph_ivec_free(&vpath);
	cgraph_ivec_free(&epath);
	return rab;
}

void weight_swap(int *a, int *b){
	int tmp=*a;
	*a=*b;
	*b=tmp;
}

int weight_partition (cgraph_ivec_t arr,cgraph_rvec_t weights, int low, int high)
{
    double pivot = weights[(arr[high])];    // pivot
    int left = low;
    int right = high - 1;
    while(true){
        while(left <= right && weights[arr[left]] < pivot) left++; // Tìm phần tử >= arr[pivot]
        while(right >= left && weights[arr[right]] > pivot) right--; // Tìm phần tử <= arr[pivot]
        if (left >= right) break; // Đã duyệt xong thì thoát vòng lặp
        weight_swap(&(arr[left]), &(arr[right])); // Nếu chưa xong, đổi chỗ.
        left++; // Vì left hiện tại đã xét, nên cần tăng
        right--; // Vì right hiện tại đã xét, nên cần giảm
    }
    weight_swap(&arr[left], &arr[high]);
    return left; // Trả về chỉ số sẽ dùng để chia đổi mảng
}

void weight_quickSort(cgraph_ivec_t arr,cgraph_rvec_t weights, int low, int high)
{
    if (low < high)
    {
        /* pi là chỉ số nơi phần tử này đã đứng đúng vị trí
         và là phần tử chia mảng làm 2 mảng con trái & phải */
        int pi = weight_partition(arr,weights, low, high);
 
        // Gọi đệ quy sắp xếp 2 mảng con trái và phải
        weight_quickSort(arr,weights, low, pi - 1);
        weight_quickSort(arr,weights, pi + 1, high);
    }
}

void cgraph_ivec_convert(cgraph_ivec_t arr,int from, int to){
	int i;
	for(i=0;i<cgraph_ivec_size(arr);++i){
		if(arr[i]==from) arr[i]=to;
	}
}

int cgraph_kruskal(cgraph_t g,cgraph_rvec_t weights,cgraph_ivec_t *kruskal,cgraph_rvec_t *kruskal_weights){
	int i,count;
	bool correct;
	cgraph_ivec_t ws=cgraph_ivec_create();
	for(i=0;i<cgraph_ivec_size(g->from);++i) cgraph_ivec_push_back(&ws,i);
	weight_quickSort(ws,weights, 0, cgraph_ivec_size(ws)-1);

	cgraph_ivec_t group=cgraph_ivec_create();
	cgraph_ivec_init(&group, g->n);
	cgraph_ivec_fill(group, -1);

	for(i=0,count=0;i<cgraph_ivec_size(ws);++i){
		correct=false;

		if(group[g->from[ws[i]]]>group[g->to[ws[i]]]){
			if(group[g->to[ws[i]]]>-1) cgraph_ivec_convert(group, group[g->from[ws[i]]], group[g->to[ws[i]]]);
			else group[g->to[ws[i]]] = group[g->from[ws[i]]];
			correct=true;
		}

		else if(group[g->from[ws[i]]]<group[g->to[ws[i]]]){
			if(group[g->from[ws[i]]]>-1) cgraph_ivec_convert(group, group[g->to[ws[i]]], group[g->from[ws[i]]]);
			else group[g->from[ws[i]]] = group[g->to[ws[i]]];
			correct=true;
		}

		else if(group[g->from[ws[i]]]==-1){
			group[g->from[ws[i]]] = group[g->to[ws[i]]] = count;
			++count;
			correct=true;
		}

		if(correct){
			if(kruskal!=NULL){
				cgraph_ivec_push_back(kruskal,g->from[ws[i]]);
				cgraph_ivec_push_back(kruskal,g->to[ws[i]]);
			}
			if(kruskal_weights!=NULL) cgraph_rvec_push_back(kruskal_weights,weights[ws[i]]);
		}
	}

	correct=true;
	if(count==0) correct=false;
	else{
		for(i=1,count=group[0];i<g->n;++i){
			if(group[i]!=count){
				correct=false;
				break;
			}
		}
	}

	cgraph_ivec_free(&ws);
	cgraph_ivec_free(&group);
	if(correct) return 1;
	else return 0;
}

int cgraph_prim(cgraph_t g,cgraph_rvec_t weights ,cgraph_ivec_t *prim,cgraph_rvec_t *prim_weights){
	int i,j,Ssize,min;
	cgraph_ivec_t parents=cgraph_ivec_create();
	cgraph_ivec_init(&parents, g->n);
	cgraph_ivec_fill(parents, -1);
	
	cgraph_rvec_t dists = cgraph_rvec_create();
	cgraph_rvec_init(&dists, g->n);
	cgraph_rvec_fill(dists, -1.0);
	
	cgraph_ivec_t S=cgraph_ivec_create();
	cgraph_ivec_push_back(&S,0);
	dists[0]=0;

	bool *visited=calloc(g->n,sizeof(bool));
	visited[0]=true;

	for(min =0;cgraph_ivec_size(S)<g->n&&min!=-1;){
		for(i=0,min=-1,Ssize=cgraph_ivec_size(S);i<Ssize;++i){
			cgraph_ivec_t neis = cgraph_ivec_create();
			cgraph_incident(g, &neis, S[i], CGRAPH_ALL);
			CGRAPH_INTEGER neisize=cgraph_ivec_size(neis);
			for(j=0;j<neisize;++j){
				CGRAPH_INTEGER edge = neis[j];
				CGRAPH_INTEGER tto = CGRAPH_OTHER(g, edge, S[i]);
				if(!visited[tto]){
					CGRAPH_REAL altdist = weights[edge];
					CGRAPH_REAL curdist = dists[tto];
					if (curdist < 0 || altdist < curdist) {
						// Khoảng cách hữu hạn đầu tiên hoặc một đường đi ngắn hơn.
						dists[tto] = altdist;
						parents[tto] = edge;
					}
					if(min<0||dists[tto]<dists[min]){
						min=tto;
					}
				}
			}
			cgraph_ivec_free(&neis);
		}
		if(min!=-1){
			cgraph_ivec_push_back(&S,min);
			visited[min]=true;
		}
	}
	for(i=1;i<g->n;++i){
		if(prim!=NULL){
			cgraph_ivec_push_back(prim,g->from[parents[i]]);
			cgraph_ivec_push_back(prim,g->to[parents[i]]);
		}
		if(prim_weights!=NULL) cgraph_rvec_push_back(prim_weights,weights[parents[i]]);
	}
	free(visited);
	cgraph_ivec_free(&parents);
	cgraph_rvec_free(&dists);
	cgraph_ivec_free(&S);
	if(min!=-1) return 1;
	else return 0;
}

int cgraph_to_prufer(cgraph_t g, cgraph_ivec_t* prufer){
	int i,count;
	if(cgraph_is_directed(g)) return 0;

	if(cgraph_ivec_size(g->from)==g->n-1){
		cgraph_rvec_t w=cgraph_rvec_create();
		cgraph_rvec_init(&w,g->n-1);
		cgraph_rvec_fill(w,1);
		if(!cgraph_kruskal(g,w,NULL,NULL)){
			cgraph_rvec_free(&w);
			return 0;
		}
		cgraph_rvec_free(&w);
	}
	else {
		return 0;
	}


	cgraph_ivec_t deg =cgraph_ivec_create();
	cgraph_degree_all(g,&deg,CGRAPH_ALL,false);

	for(i=1,count=0;i<=g->n&&count<g->n-1;++i){
		if(deg[i]==1){
			deg[i]-=1;
			cgraph_ivec_t neis=cgraph_ivec_create();
			cgraph_neighbors(g, &neis, i,CGRAPH_ALL);
			for(i=0;i<cgraph_ivec_size(neis);++i){
				if(deg[neis[i]]>1) {
					--deg[neis[i]];
					cgraph_ivec_push_back(prufer,neis[i]);
				}
			}
			i=0;
			++count;
		}
	}
	cgraph_ivec_free(&deg);
	return 1;
}


// treetype* PruferCodeNguoc(int* Prufer,int* Bac,int n){
// 	int i,j;
// 	treetype* Canh=(treetype*)malloc(sizeof(treetype)*n);
// 	for(i=0;i<n;++i){
// 		Canh[i].dinh2=Prufer[i];
// 		for(j=0;j<=n;++j){
// 			if(Bac[j]==0){
// 				Canh[i].dinh1=j;
// 				Bac[j]+=1;
// 				break;
// 			}
// 		}
// 		Bac[Prufer[i]]-=1;
// 	}
// 	return Canh;
// }

#endif
