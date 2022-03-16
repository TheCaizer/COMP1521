#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *var = getenv(argv[1]);

    if (var == NULL) {
        printf("0\n");
    } else if (strcmp(var, "") == 0) {
        printf("0\n");
    } else {
        printf("1\n");
    }

    return 0;
}