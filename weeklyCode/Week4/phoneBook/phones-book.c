#include"phones-book.h"
#include"mylib.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdio_ext.h>

PhoneBook CreateBook(int max_length){
    PhoneBook book;
    book = (PhoneBook)malloc(sizeof(PhoneBook));
    if(book==NULL){
        printf("Cannot allocate memory\n");
        return book;
    }

    book->data = (PhoneEntry*)malloc(sizeof(PhoneEntry)*max_length);
    if(book->data==NULL){
        printf("Cannot allocate memory\n");
        return book;
    }

    book->max_length = max_length;
    book->length = 0;
    return book;
}

PhoneBook AddEntry(PhoneBook book, char *name, char *number){
    book->data[book->length].name = name;
    book->data[book->length].number = number;   
    book->length += 1; //Update 
    return book;
}

int cmp(void *a, void *b){
  PhoneEntry *p1 = (PhoneEntry*)a;
  PhoneEntry *p2 = (PhoneEntry*)b;
  return (strcmp(p1->name, p2->name) < 0);
}

PhoneBook SortBook(PhoneBook book){
    quickSort(book->data, book->length, sizeof(PhoneEntry), cmp);
    return book;
}

void PrintBook(PhoneBook book){
    int i = 0;
    while(i < book->length){
        printf("%-20s%-20s\n", book->data[i].name, book->data[i].number);
        i++;
    }
}

PhoneEntry SearchBook(PhoneBook book){
    char *x;
    int i, mark = 0;
    x = (char*)malloc(sizeof(char)*100);
    printf("\n\nInput a contact name you want to search: ");
    scanf("%[^\n]s", x);

    for(i = 0; i < book->length; i++){
        if(strcasecmp(x, book->data[i].name) == 0){
            printf("%-20s%-20s\n", book->data[i].name, book->data[i].number);
            mark = 1; //Found
            return book->data[i];
        }
    }
    if(mark == 0){
        printf("Contact doesn't exist!\n");
    }
}

void Delete(PhoneBook book, int i){
    int j; //Index
    if(i == book->length - 1){          //If the contact is at the end of the list
        book->data[i].name = "\0";
        book->data[i].number = "\0";
    }
    else{   //Day len 1 don vi
        for(j = i; j <= book->length - 2; j++){
            book->data[j].name = book->data[j+1].name;
            book->data[j].number = book->data[j+1].number;
        }
        book->data[j].name = "\0";
        book->data[j].number = "\0";
    }
}

PhoneEntry DeleteBook(PhoneBook book){
    char *x;
    int i, mark = 0;
    x = (char*)malloc(sizeof(char)*100);
    __fpurge(stdin);
    printf("\n\nInput a contact name you want to delete: ");
    scanf("%[^\n]s", x);

    for(i = 0; i < book->length; i++){
        if(strcasecmp(x, book->data[i].name) == 0){
            Delete(book, i); //Delete contact of phonebook at position i
            mark = 1; //Found
            return book->data[i];
        }
    }
    if(mark == 0){
        printf("Contact doesn't exist!\n");
    }
}