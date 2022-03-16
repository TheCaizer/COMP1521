#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    FILE *file = fopen(argv[1], "r");
    FILE *file1 = fopen("delete.tmp", "w+");
    int temp;
    while(1){
        temp = fgetc(file);
        if(temp == EOF){
            break;
        }
        else if(temp <= 127){
            putc(temp, file1);
        }
    }
    fclose(file);
    fclose(file1);
    remove(argv[1]);
    rename("delete.tmp", argv[1]);
    return 0;
}