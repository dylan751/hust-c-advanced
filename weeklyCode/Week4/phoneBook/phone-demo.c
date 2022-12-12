#include"phones-book.h"
#include<stdlib.h>
int main(){
    PhoneBook book = CreateBook(1000000);
    AddEntry(book, "Nguyen Hai Duong", "(+84)339410781");
    AddEntry(book, "Nguyen Hoang Anh", "(+84)916313317");
    AddEntry(book, "Hoang Van Hien", "(+84)963356841");
    AddEntry(book, "Tran Anh Tu", "(+84)362925068");
    AddEntry(book, "Le Thi Khanh Hoa", "(+84)338977984");
    AddEntry(book, "Dinh Thi Ngoc Anh", "(+84)868856227");
    AddEntry(book, "Tran Tuan Anh", "(+84)962633688");

    SortBook(book);
    PrintBook(book);
    SearchBook(book);
    DeleteBook(book);

    PrintBook(book);
    free(book);
}