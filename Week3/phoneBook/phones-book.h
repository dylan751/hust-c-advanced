#ifndef PHONES_BOOK_H_
#define PHONES_BOOK_H_

typedef struct {
    char *name;
    char *number;
} PhoneEntry;

typedef struct {
    PhoneEntry *data;
    int length;         //The CURRENT number of contacts saved to phonebook
    int max_length;     //The MAX number of contacts can be saved to phonebook
} *PhoneBook;

PhoneBook CreateBook(int max_length);
PhoneBook AddEntry(PhoneBook book, char *name, char *number);  //Add to tail
PhoneBook SortBook(PhoneBook book);  //Use Quicksort
void PrintBook(PhoneBook book);
PhoneEntry SearchBook(PhoneBook book);
PhoneEntry DeleteBook(PhoneBook book);

#endif // PHONES_BOOK_H_