//Tự xây dựng vector của mình

/*
Menu:
1. Nhập 1 số nguyên
2. Xuất các số đã nhập
3. Thoát

Ghi chú: Lưu tât cả các số  đã nhập vào 1 vector
]
*/
#include<stdio.h>
#include<stdlib.h>

int *v = NULL;

// Cấu trúc: |size|capacity|    |     |     |
// size: Số  ô đã sử dụng
// capacity: Dung lượng (số ô)

//                  v
//-------- -------- ............

int init_v(size_t cap){
    void *p = malloc(2 * sizeof(size_t) + cap * sizeof(int));
    v = (int*)(p + 2 * sizeof(size_t)); //Vì 2 ô nhớ đầu lưu size và capacity
    size_t *tmp = (size_t*)p;
    tmp[0] = 0;     //Size = 0: Chưa làm việc với ô nhớ nào
    tmp[1] = cap;   //Capacity: Dung lượng max người dùng nhập vào
    return 0;
}

void free_v(){
    void *p = ((size_t*)v - 2);
    free(p);
}

size_t get_size(){
    size_t *tmp = (size_t*)v;
    return tmp[-2];
}

size_t get_cap(){
    size_t *tmp = (size_t*)v;
    return tmp[-1];
}

void print_v(){
    int i;
    printf("size = %d, capacity = %d: ", get_size(), get_cap());
    for(i = 0; i < get_size(); ++i){
        printf("%d ", v[i]);
    }
    printf("\n");
}

int push_back(int value){
    size_t sz = get_size();
    size_t cap = get_cap();

    if(sz < cap){//Chưa đầy
        v[sz] = value;
        ++sz;
        size_t *tmp = (size_t*)v;
        tmp[-2] = sz;
    }
    else{  //Đầy bộ nhớ
        //Tăng capacity
        cap  *= 2;   //Tăng bao nhiêu tùy vào mình thiết lập. Quy luật tăng là tham số của vector. Ở đây VD nhân 2 lên
        size_t *tmp = (size_t*)v;
        char *p = tmp - 2;  //p = v[-2]
        p = realloc(p, 2 * sizeof(size_t) + cap * sizeof(int)); //Gấp đôi capacity
        v = (int*)(p + 2 * sizeof(size_t));                     //Bỏ qua 2 ô nhớ đầu tiên -> size và capacity
        tmp = (size_t*)v;
        tmp[-1] = cap;

        //Cập nhật giá trị
        v[sz] = value;
        ++sz;
        tmp[-2] = sz; 
    }
}

void input_number(){
    printf("Nhập 1 số: ");
    int v;
    scanf("%d", &v);
    push_back(v);
}

int main(){
    //Khởi tạo bộ nhớ cho v
    init_v(3);
    // print_v();
    // for(int i = 0; i < 10; ++i){
    //     printf("%d: ", i);
    //     push_back(i);
    //     print_v();
    // }

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