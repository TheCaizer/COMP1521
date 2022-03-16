#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
    FILE *file = fopen(argv[1], "r");
    int counter = 0;
    int temp;
    while((temp = fgetc(file)) != EOF){
        if(temp >= 0 && temp <= 127){
            counter ++;
        }
    }
    printf("%s contains %d ASCII bytes\n",argv[1], counter);
    return 0;
}