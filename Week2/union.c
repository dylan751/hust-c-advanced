#include<stdio.h>

union value_t{
    int i;
    double d;
    float f;
    char *s;
    void *v;
};

int main(){
    union value_t v;
    return 0;
}