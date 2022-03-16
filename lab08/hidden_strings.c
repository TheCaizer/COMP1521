#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char* argv[]){
    FILE* file = fopen(argv[1],"r");
    int counter = 0;
    int y = 0;
    int temp;
    char array[1000];
    while(1){
        temp = fgetc(file);
        if(isprint(temp) != 0){
            array[y] = temp;
            y++;
            counter++;
        }
        else{
            if(counter >= 4){
                y = 0;
                while(y < counter){
                    printf("%c",array[y]);
                    y++;
                }
                printf("\n");
            }
            y = 0;
            counter = 0;
        }
        if(temp == EOF){
            break;
        }
    }
    return 0;
}