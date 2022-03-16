#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
int main(int argc, char *argv[]) {
    FILE *file = fopen(argv[1], "r");
    int counter = 0;
    int temp;
    while(1){
        temp = fgetc(file);
        if(temp > 127){
            printf("%s: byte %d is non-ASCII\n",argv[1], counter);
            fclose(file);
            return 0;
        }
        if(temp == EOF){
            printf("%s is all ASCII\n",argv[1]);
            fclose(file);
            return 0;
        }
        counter++;
    }
}