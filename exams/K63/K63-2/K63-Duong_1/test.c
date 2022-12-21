#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE* ptr = fopen("pageConnections.txt", "r");
    int n, v1, v2;
    char c, num[20];
    for(n = 0, v1 = -1; (c = fgetc(ptr)) != EOF; ) {
        if(c == '\n') {
            num[n] = '\0';
            n = 0;
            v1 = -1;
            v2 = atoi(num);
            printf("%d\n", v2);
        }
        else if(c == ' ') {
            num[n] = '\0';
            n = 0;
            if(v1 == -1) {
                v1 = atoi(num);
                printf("%d: ", v1);
            }
            else {
                v2 = atoi(num);
                printf("%d ", v2);
            }
        }
        else{
            num[n] = c;
            ++n;
        }
    }

    return 0;
}