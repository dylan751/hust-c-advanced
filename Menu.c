#include "cgraph/cgraph.h"

#include <stdio.h>
#include <stdio_ext.h>

int main() {
    char choice;
  
    while(1){
        printf("           ---MENU---\n"
               "|1. Import from PhoneDB.dat.  |\n"
               "|2. Display.                  |\n"
               "|3. Add new phone.            |\n"
               "|4. Insert At Position.       |\n"
               "|5. Delete At Position.       |\n"
               "|6. Delete current.           |\n");

        __fpurge(stdin);
        printf("Input your choice: ");
        scanf("%c", &choice);

        while(choice > '6' || choice < '1'){
            __fpurge(stdin);
            printf("Ivalid! Input your choice again: ");
            scanf("%c", &choice);
        }

        switch(choice) {
        case '1': {

            break;
        }

        case '2': {

            break;
        }

        case '3': {

            break;
        }

        case '4': {

            break;
        }

        case '5': {

            break;
        }

        case '6': {
            exit(0);
            break;
        }

        }
    }
    return 0;
}
