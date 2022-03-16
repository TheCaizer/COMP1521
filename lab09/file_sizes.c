#include <stdio.h>

long int find_file_size(char *filename);

int main(int argc, char *argv[]){
    int counter = 1;
    long int size;
    long int total = 0;
    while(counter < argc){
        size = find_file_size(argv[counter]);
        printf("%s: %ld bytes\n",argv[counter], size);
        total = total + size;
        counter++;
    }
    printf("Total: %ld bytes\n",total);
    return 0;
}

long int find_file_size(char *filename){
   FILE* file = fopen(filename, "r");
   if (file == NULL){
      printf("File Not Found!\n");
      return -1;
   }
   fseek(file, 0L, SEEK_END);
   long int size = ftell(file);
   fclose(file);
   return size;
}