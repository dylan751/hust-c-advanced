/*
phone book su dung libfdr
*/

#include "libfdr/jrb.h"

#include<stdio.h>
#include <strings.h>
#include <string.h>

int jval_cmp_str(Jval v1, Jval v2){
    return strcasecmp(v1.s, v2.s);
}

void add_contacts(JRB contacts, char *name, char *number){
    jrb_insert_gen(contacts, (Jval){.s = name},
                             (Jval){.s = number},
                             jval_cmp_str);
}

int main(){
    JRB contacts = make_jrb();
    add_contacts(contacts, "Nguyen Van A", "333555999");
    add_contacts(contacts, "Nguyen Van B", "666555999");
    add_contacts(contacts, "Nguyen Van D", "888555999");
    add_contacts(contacts, "Nguyen Van C", "999555999");

    JRB r = jrb_find_gen(contacts, (Jval){.s = "Nguyen Hai Duong"}, jval_cmp_str);
    if(r){
        printf("%s %s\n", r->key.s, r->val.s);
    }
    else{
        printf("Not found\n");
    }
}