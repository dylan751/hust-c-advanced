#include "cgraph/cgraph.h"

cgraph_ivec_t v = NULL;

void free_v(){
    cgraph_ivec_free(&v);
}

int push_back(int value){
    cgraph_ivec_push_back(&v, value);
    return 0;
}

void print_v(){
    cgraph_ivec_print(v);
}

void input_number(){
    printf("Nhập 1 số: ");
    int v;
    scanf("%d", &v);
    push_back(v);
}

int main(){
    v = cgraph_ivec_create();
    for( ; ; ){
        printf("|1. Thêm 1 phần tử.          |\n"
               "|2. Xem các phần tử đã nhập. |\n"
               "|3. Thoát.                   |\n");
        printf("Lựa chọn của bạn: ");
        int c = 0;
        scanf("%d", &c);
        if(c == 1){
            input_number();
        }
        else if(c == 2){
            print_v();
        }
        else if(c == 3){
            break;
        }
    }
    free_v();
    return 0;
}