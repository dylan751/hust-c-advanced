#include"mylib.h"
#include<string.h>

typedef struct {
    char* name;
    long sz;
} file_info_t;

int gen_less_fi_t(void *a, void *b){
    file_info_t *p1 = (file_info_t*)a,
                *p2 = (file_info_t*)b;
    if(p1->sz == p2->sz){
        return strcmp(p1->name, p2->name) < 0;
    }
    return p1->sz < p2->sz;
}

int main(){
    file_info_t files[] = {{"a", 100}, {"c", 1000}, {"b", 1000}};
    int n = sizeof(files)/sizeof(file[0]);
    
    quick_sort();

    return 0;
}