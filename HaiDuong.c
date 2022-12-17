
#include "cgraph/cgraph.h"
#include "cgen/s2i.h"
#include "cgen/svector.h"

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>

typedef struct {
  char *station;
  char *route;
} BStop;

bn_tree_t s2i = NULL; 
vector_t i2s = NULL; 
vector_t route_list = NULL;
cgraph_ivec_t edges = NULL; 

cgraph_rvec_t weights = NULL;//vector chua cac trong so canh

const int kNext = 1;   // mac dinh trong so canh la 1 
int g_id = 0;     

int get_save_id(char *key) {
    int res = s2i_value(s2i, key);    
    if(res != k_s2i_invalid) {        
        return res;                 
    }                   
    s2i_insert(s2i, key, g_id);   
    svec_push_back(&i2s, key);
    res = g_id;
    ++g_id;
    return res;
}

void remove_trailing(char *s) {
  int len = strlen(s);
  while (len > 0 && isspace(s[len - 1])) {
    s[len - 1] = '\0';
    --len;
  }
}


void store_edge(int f, int t, int wt) {
  cgraph_ivec_push_back(&edges, f);
  cgraph_ivec_push_back(&edges, t);
  cgraph_rvec_push_back(&weights, wt);
  printf("Edge(%d, %d):%d\n", f, t, wt);
}

char *tao_dinh(char *station, char* route)
{
    strcat(station,"+");
    strcat(station,route);
    return station;
}
char * tach_station_route(char *dinh)
{
    //char* tmp = strdup(dinh);
    for(int i = 0;;i++)
    {
        if(dinh[i] == '+')
        {
            dinh[i] = '\0';
            return dinh;
        }
    }
}
void connect(int route_count, int uid, char *name)
{
    for (int i = 0; i < route_count; i++)
      {
        tao_dinh(name,route_list[i].s);
        int res = s2i_value(s2i, name);
            if( res != k_s2i_invalid)
            {
                store_edge(res,uid,kNext);
                store_edge(uid,res,kNext);
                printf("bug\n");
            }
      }

}
int loadFile() {
    s2i = s2i_create();
    i2s = gtv_create();
    route_list = gtv_create();
    edges = cgraph_ivec_create();
    weights = cgraph_rvec_create();
  char station[100000];
  char route[100000];
  FILE *fptr = fopen("bus.txt", "r");
  int id = 0;
  int route_count = 0;
  while(!feof(fptr)) {
    fscanf(fptr, "%[^:]%*[:]", route);
    svec_push_back(&route_list, route);
    int prev = -1;
    while (fscanf(fptr, " %[^>\n]", station) > 0) {
      remove_trailing(station);
      tao_dinh(station, route); //ghep ten ben va ten chuyen
      int uid = get_save_id(station); 
      
      if (prev >= 0) {
        store_edge(prev, id, kNext);
      }
      tach_station_route(station);
      printf("(%s):%d\n", station, id);
      connect(route_count, uid, station);
      prev = id++;
      fscanf(fptr, "%*[>]");
      if (fscanf(fptr, "%[\n]", station) > 0) {
        break;
      }
    }
    route_count ++;
  }
  gtv_free(&route_list);
  fclose(fptr);
  g_id = id;
  return 0;
}

int main(int argc, char const *argv[])
{
    loadFile();
    cgraph_t g = cgraph_create(edges, 0, CGRAPH_DIRECTED);
    cgraph_rvec_t weights = cgraph_rvec_create();
    cgraph_ivec_t vpath = cgraph_ivec_create(),
                  epath = cgraph_ivec_create();

    char start[100000];
    char end[100000];
    printf("Input starting point:");
    scanf("%[^\n]s", start); 
    printf("%s\n", start);
    
    __fpurge(stdin);
    printf("Input ending point:");
    scanf("%[^\n]s", end);
    printf("%s\n", end);
    
    cgraph_get_shortest_path_dijkstra(g, &vpath, &epath, start, end, weights, CGRAPH_OUT);
    return 0;
}