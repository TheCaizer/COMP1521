#include<stdio.h>
#include<stdlib.h>

#define BYTE10 0b10000000
#define BYTE110 0b11000000
#define BYTE1110 0b11100000
#define BYTE11110 0b11110000
#define BYTE0 0b01111111


int main(int argc, char *argv[]){
    FILE *file = fopen(argv[1], "r");
    int counter = 0;
    int utf8[4];
    while(1){
        utf8[0] = fgetc(file);
        printf("%d",utf8[0]);
        if(utf8[0] == EOF){
            printf("%s: %d UTF-8 characters\n",argv[1], counter);
            break;;
        }
        if((utf8[0]&BYTE11110)){
            if((utf8[1] = fgetc(file)) != EOF){
                if((utf8[1]&BYTE10)){
                    continue;
                }
                else{
                    printf("%s: invalid UTF-8 after %d valid UTF-8 characters\n",argv[1], counter);
                    break;
                }
            }
            else{
                printf("%s: invalid UTF-8 after %d valid UTF-8 characters\n",argv[1], counter);
                break;
            }
            if((utf8[2] = fgetc(file)) != EOF){
                if((utf8[2]&BYTE10)){
                    continue;
                }
                else{
                    printf("%s: invalid UTF-8 after %d valid UTF-8 characters\n",argv[1], counter);
                    break;
                }
            }
            else{
                printf("%s: invalid UTF-8 after %d valid UTF-8 characters\n",argv[1], counter);
                break;
            }
            if((utf8[3] = fgetc(file)) != EOF){
                if((utf8[3]&BYTE10)){
                    counter++;
                }
                else{
                    printf("%s: invalid UTF-8 after %d valid UTF-8 characters\n",argv[1], counter);
                    break;
                }
            }
            else{
                printf("%s: invalid UTF-8 after %d valid UTF-8 characters\n",argv[1], counter);
                break;
            }
        }
        else if((utf8[0]&BYTE1110) == BYTE1110){
            if((utf8[1] = fgetc(file)) != EOF){
                if((utf8[1]&BYTE10) == BYTE10){
                    continue;
                }
                else{
                    printf("%s: invalid UTF-8 after %d valid UTF-8 characters\n",argv[1], counter);
                    break;
                }
            }
            else{
                printf("%s: invalid UTF-8 after %d valid UTF-8 characters\n",argv[1], counter);
                break;
            }
            if((utf8[2] = fgetc(file)) != EOF){
                if((utf8[2]&BYTE10) == BYTE10){
                    counter++;
                }
                else{
                    printf("%s: invalid UTF-8 after %d valid UTF-8 characters\n",argv[1], counter);
                    break;
                }
            }
            else{
                printf("%s: invalid UTF-8 after %d valid UTF-8 characters\n",argv[1], counter);
                break;
            }
        }
        else if((utf8[0]&BYTE110) == BYTE110){
            if((utf8[1] = fgetc(file)) != EOF){
                if((utf8[1]&BYTE10) == BYTE10){
                    counter++;
                }
                else{
                    printf("%s: invalid UTF-8 after %d valid UTF-8 characters\n",argv[1], counter);
                    break;
                }
            }
            else{
                printf("%s: invalid UTF-8 after %d valid UTF-8 characters\n",argv[1], counter);
                break;
            }
        }
        else if((utf8[0]|BYTE0) == BYTE0){
            counter++;
        }
        else{
            printf("%s: invalid UTF-8 after %d valid UTF-8 characters\n",argv[1], counter);
            break;
        }
    }
    return 0;
}