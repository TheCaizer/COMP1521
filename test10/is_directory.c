#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char *temp = argv[1];
    if (chdir(temp) != 0) {
        printf("0\n");
    } else {
        printf("1\n");
    }
    return 0;
}