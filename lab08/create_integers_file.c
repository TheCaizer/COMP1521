#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if(argc != 4){
        perror("Need 4 arguments");
        return 0;
    }
    FILE *output_stream = fopen(argv[1], "w");
    int start = atoi(argv[2]);
    int end = atoi(argv[3]);

    if(start > end){
        perror("invalid arguments");
        return 0;
    }
    while(start != end + 1){
        fprintf(output_stream, "%d\n", start);
        start++;
    }

    return 0;
}