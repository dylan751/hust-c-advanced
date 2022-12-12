#include "cmake-btree/inc/btree.h"

#include<stdio.h>
#include<string.h>

#define NUMBER_LEN 20

void delete_newline(char *s){
    int len = strlen(s);
    while(s[len-1] == '\n' || s[len-1] == '\r'){
        s[len-1] = '\0';
        len--;
    }
}

void add_contact(BTA* root){
    char phone[NUMBER_LEN + 1];
    char name[ZKYLEN + 1];// ZKYLEN = 32
    printf("Name: ");
    fgets(name, ZKYLEN, stdin);
    delete_newline(name);

    printf("phone: ");
    fgets(phone, NUMBER_LEN, stdin);
    delete_newline(phone);   
    
    //printf("\nName: %s\nPhone: %s\n", name, phone);

    int ret = btins(root, name, phone, strlen(phone) + 1);
    if(ret != 0){
        printf("Insert error!\n");
    }
}

void list_contact(BTA *root){
    // Đưa con trỏ về đầu
    btpos(root, ZSTART);

    // Lặp xuất dữ liệu
    char buf[NUMBER_LEN + 1];
    char key[ZKYLEN + 1];
    int status, size;

    printf("All contacts: \n");
    for( ; ; ){
        status = btseln(root, key, buf, NUMBER_LEN, &size);
        if(status == 0){
            buf[size] = '\0';
            printf("Name: '%s' - Number: '%s'\n", key, buf);
        } else{
            break;
        }
    }
}

int main(int argc, char *argv[]){
    if(argc < 2){
        printf("It should be: ./phone-bt book.bt\n");
        return 1;
    }
    //Mở argv[1], nếu không có thì tạo mới
    BTA *root = NULL;
    root = btopn(argv[1], 0/*Cho phép viết + update*/, FALSE/*Ko chia sẻ*/);
    if(!root){
        root = btcrt(argv[1], 0, FALSE);
        if(!root){
            printf("Can not open/create database!\n");
            return 1;
        }
    }
    //1. Thêm
    //2. In
    //3. Thoát

    for( ; ; ){
        printf("1. Thêm\n2. In\n3. Thoát\nLệnh: ");
        int cmd = 0;
        scanf("%d%*c", &cmd);
        if(cmd == 1){
            //Thêm
            add_contact(root);
        } else if(cmd == 2){
            //In
            list_contact(root);
        } else if(cmd == 3){
            break;
        }
    }

    btcls(root);
    return 0;   
}