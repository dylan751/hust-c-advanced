#include"mylib.h"
#include<string.h>
#include<stdio.h>

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
    int i;
    file_info_t files[] = {{"aaaaaaaaaaa", 100},
                           {"ccccccccccccc", 1000}, 
                           {"bbbbbbbbbbbbbbbbb", 1000}};
    int n = sizeof(files)/sizeof(files[0]);

    quickSort(files, n, sizeof(file_info_t), gen_less_fi_t);
    for(i = 0; i < n; i++){
        printf("%d: {%s, %ld}\n", i, files[i].name, files[i].sz);
    }
    return 0;
}