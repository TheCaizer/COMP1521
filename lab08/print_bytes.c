#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    FILE *file = fopen(argv[1], "r");
    int temp;
    long int count = 0;
    while(1){
        temp = fgetc(file);
        if(temp == EOF){
            break;
        }
        if(isprint(temp) != 0){
            printf("byte %4ld: %3u 0x%02x '%c'\n",count, temp, temp, temp);
        }
        else{
            printf("byte %4ld: %3u 0x%02x\n",count, temp, temp);
        }
        count++;
    }

    fclose(file);

    return 0;
}