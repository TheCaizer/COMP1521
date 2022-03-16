#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char* argv[]){
    char *var1 = getenv(argv[1]);
    char *var2 = getenv(argv[2]);
    if(var1 == NULL || var2 == NULL){
        printf("0\n");
        return 0;
    }
    if(strcmp(var1, var2) == 0){
        printf("1\n");
        return 1;
    }
    else{
        printf("0\n");
        return 0;
    }
}