#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]){
    int x = 2;
    char temp;
    FILE* file = fopen(argv[1], "w");
    while(x < argc){
        temp = atoi(argv[x]);
        fputc(temp, file);
        x++;
    }
    return 0;
}