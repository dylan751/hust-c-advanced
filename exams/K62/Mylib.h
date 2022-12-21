#ifndef MY_LIB_H
#define MY_LIB_H

#include<stdio.h>
#include <string.h>
#include "cgen/s2i.h"
#include "cgen/svector.h"
#include"cgraph/cgraph.h"

int get_save_id(char *key,char *fullstr, bn_tree_t *s2i ,vector_t *i2s, vector_t *i2f ) {
    int res = s2i_value(*s2i, key);    //search
    if(res != k_s2i_invalid) {        //Nếu tìm thấy -> return
        return res;                 
    }
    res=gtv_size(*i2s);
    svec_push_back(i2s, key);
    if(i2f!=NULL) svec_push_back(i2f,fullstr);
    s2i_insert(*s2i, key, res);       //Nếu không tìm thấy -> insert
    return res;
}

int simple_get_save_id(char *key, bn_tree_t *s2i ,vector_t *i2s ) {
    
    return get_save_id(key,NULL, s2i ,i2s,NULL );
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
	for(i=0,n=cgraph_ivec_size(order);i<n;++i){
		cgraph_ivec_push_back(tplt,order[i]);
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

#endif
