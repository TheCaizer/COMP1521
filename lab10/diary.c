#include <stdio.h>
#include <stdlib.h>
#include <spawn.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    char path[1000]; 
    int i = 1;  
    char *value = getenv("HOME");
    snprintf(path, 1000, "%s/.diary",value);
    FILE * file;
    file = fopen(path, "a");
    while (i < argc){
        fprintf(file, "%s ", argv[i]);
        i++;
    }
    fprintf(file, "%s", "\n");
    return 0;
}