#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

void stat_file(char *pathname);

int main(int argc, char *argv[]) {
    for (int arg = 1; arg < argc; arg++) {
        stat_file(argv[arg]);
    }
    return 0;
}

void stat_file(char *pathname){
    struct stat s;

    if (stat(pathname, &s) != 0) {
        perror(pathname);
        exit(1);
    }
    int mode = s.st_mode;
    //check if it is directory or file
    if(mode/0100000){
        printf("-");
        mode = mode-0100000;
    }
    else{
        printf("d");
        mode = mode-040000;
    }

    if(mode/0700){
        printf("rwx");
        mode = mode-0700;
    }
    else if(mode/0600){
        printf("rw-");
        mode = mode-0600;
    }
    else if(mode/0500){
        printf("r-x");
        mode = mode-0500;
    }
    else if(mode/0400){
        printf("r--");
        mode = mode-0400;
    }
    else if(mode/0300){
        printf("-wx");
        mode = mode-0300;
    }
    else if(mode/0200){
        printf("-w-");
        mode = mode-0200;
    }
    else if(mode/0100){
        printf("--x");
        mode = mode-0100;
    }
    else{
        printf("---");
    }

    if(mode/070){
        printf("rwx");
        mode = mode-070;
    }
    else if(mode/060){
        printf("rw-");
        mode = mode-060;
    }
    else if(mode/050){
        printf("r-x");
        mode = mode-050;
    }
    else if(mode/040){
        printf("r--");
        mode = mode-040;
    }
    else if(mode/030){
        printf("-wx");
        mode = mode-030;
    }
    else if(mode/020){
        printf("-w-");
        mode = mode-020;
    }
    else if(mode/010){
        printf("--x");
        mode = mode-010;
    }
    else{
        printf("---");
    }

    if(mode/07){
        printf("rwx ");
        mode = mode-07;
    }
    else if(mode/06){
        printf("rw- ");
        mode = mode-06;
    }
    else if(mode/05){
        printf("r-x ");
        mode = mode-05;
    }
    else if(mode/04){
        printf("r-- ");
        mode = mode-04;
    }
    else if(mode/03){
        printf("-wx ");
        mode = mode-03;
    }
    else if(mode/02){
        printf("-w- ");
        mode = mode-02;
    }
    else if(mode/01){
        printf("--x ");
        mode = mode-01;
    }
    else{
        printf("--- ");
    }

    printf("%s\n",pathname);
}