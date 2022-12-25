#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libfdr/jrb.h"

void do_print(JRB dns);
void do_add(JRB dns, char *dn, char *ip);
void do_remove(JRB dns, char *dn);
void do_lookup_ip(JRB dns, char *dn);
void do_lookup_dn(JRB dns, char *ip);

int jval_cmp_str(Jval v1, Jval v2){
    return strcasecmp(v1.s, v2.s);
}


int main(int argc, char **argv) {
  JRB dns = make_jrb();
  if (argc <= 1) {
    printf("Usage: prog print \n       prog add [dn] [ip] \n       prog remove [dn]\n       prog ip [dn]\n       prog dn [ip]\n");
    return 0;
  }

  if (strcmp(argv[1], "print") == 0) {
    if (argc != 2) {
      printf("Invalid paramteers\n");
      return 0;
    }
    do_print(dns);
    return 0;
  }
  if (strcmp(argv[1], "add") == 0) {
    if (argc != 4) {
      printf("Invalid parameters\n");
      return 0;
    }
    do_add(dns, argv[2], argv[3]);
    return 0;
  }
  if (strcmp(argv[1], "remove") == 0) {
    if (argc != 3) {
      printf("Invalid parameters\n");
      return 0;
    }
    do_remove(dns, argv[2]);
    return 0;
  }
  if (strcmp(argv[1], "ip") == 0) {
    if (argc != 3) {
      printf("Invalid parameters\n");
      return 0;
    }
    do_lookup_ip(dns, argv[2]);
    return 0;
  }
  if (strcmp(argv[1], "dn") == 0) {
    if (argc != 3) {
      printf("Invalid parameters\n");
      return 0;
    }
    do_lookup_dn(dns, argv[2]);
    return 0;
  }
  printf("Invalid parameters\n");


  return 0;
}

void print_entry(char *dn, char *ip) {
  printf("%s => %s\n", dn, ip);  
}


void do_print(JRB dns) {
  // TODO
  FILE* fptr = fopen("dns.txt", "r");
  if(fptr == NULL) {
    printf("Error!\n");
  }
  int n, i;
  char dn[40], ip[40];
  fscanf(fptr, "%d", &n);
  for(i = 0; i < n; i++) {
    fscanf(fptr, "%s\n", dn);
    fscanf(fptr, "%s\n", ip);
    jrb_insert_gen(dns, (Jval){.s = strdup(dn)}, (Jval){.s = strdup(ip)}, jval_cmp_str);
  }

  JRB ptr;
  jrb_traverse(ptr, dns) {
    print_entry(ptr->key.s, ptr->val.s);
  }
  jrb_free_tree(dns);
}

void do_add(JRB dns, char *dn, char *ip) {
  // TODO
  // FILE* fptr = fopen("dns.txt", "w");
  JRB r = jrb_find_str(dns, dn);
  if(r != NULL) {
    strcpy(r->val.s, ip);
  }
  else {
    jrb_insert_str(dns, strdup(dn), (Jval){.s = strdup(ip)});
  }

  JRB ptr;
  jrb_traverse(ptr, dns) {
    print_entry(ptr->key.s, ptr->val.s);
  }
  // fclose(fptr);
}

void do_remove(JRB dns, char *dn) {
  // TODO

}

void do_lookup_ip(JRB dns, char *dn) {
  // TODO
}

void do_lookup_dn(JRB dns, char *ip) {
  // TODO
}
