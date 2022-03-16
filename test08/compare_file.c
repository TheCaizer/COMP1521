#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    FILE *file1 = fopen(argv[1], "r");
    FILE *file2 = fopen(argv[2], "r");
    int temp1;
    int temp2;
    int counter = 0;
    while(1){
        temp1 = fgetc(file1);
        temp2 = fgetc(file2);
        if(temp1 == EOF && temp2 == EOF){
            printf("Files are identical\n");
            fclose(file1);
            fclose(file2);
            return 0;
        }
        else if(temp1 == EOF){
            printf("EOF on %s\n",argv[1]);
            fclose(file1);
            fclose(file2);
            return 0;
        }
        else if(temp2 == EOF){
            printf("EOF on %s\n",argv[2]);
            fclose(file1);
            fclose(file2);
            return 0;
        }
        else if(temp1 != temp2){
            printf("Files differ at byte %d\n" ,counter);
            fclose(file1);
            fclose(file2);
            return 0;
        }
        counter++;
    }
}