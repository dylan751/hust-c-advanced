/*
Đọc input.txt và tạo
cây: key - int value: cây - key: int value
kiểm tra (v1, v2) - xem v2 có trong danh sách của v1 hay ko?
*/

#include "libfdr/jrb.h"
#include "libfdr/jval.h"

#include <stdio.h>

int main(){
    JRB r = make_jrb();
    FILE *inp = fopen("../input.txt", "r");
    int n;
    fscanf(inp, "%d", &n); //
    int i;
    for(i = 0; i < n; i++){
        int key, m;
        fscanf(inp, "%d%d", &key, &m);  //Đọc 2 số đầu dòng
        JRB sub = make_jrb();           //Tạo substree
        jrb_insert_int(r, key, (Jval){.v = sub});
        for(int j = 0; j < m; ++j){
            int key;
            fscanf(inp, "%d", &key);
            jrb_insert_int(sub, key, (Jval){.v = NULL});
        }
    }
    int v1, v2;
    scanf("%d %d", &v1, &v2);
    JRB node = jrb_find_int(r, v1);
    if(node){
        //Tìm tiếp
        JRB sub = (JRB)(node->val.v);
        node = jrb_find_int(sub, v2);
        if(node){
            printf("YES\n");
        }
        else{
            printf("NO v2\n");
        }
    }
    else{
        printf("NO v1\n");
    }
    JRB ptr;
    jrb_traverse(ptr, r){
        printf("%d ", ptr->key.i);
        jrb_free_tree(ptr->val.v);
    }
    jrb_free_tree(r);
    return 0;
}