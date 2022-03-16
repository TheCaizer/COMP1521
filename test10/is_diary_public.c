#include<stdio.h>
#include<sys/stat.h>
#include<stdlib.h>

#define MAX_SIZE 1000 

int main(void){
    struct stat s;
    char file[MAX_SIZE];
    char *var = getenv("HOME");
    snprintf(file, MAX_SIZE, "%s/.diary",var);
    if(stat(file, &s) < 0){
    printf("0\n");
    return 1;
    }
    if(s.st_mode & S_IROTH){
        printf("1\n");
    } else{
        printf("0\n");    
    }
    return 0;
}