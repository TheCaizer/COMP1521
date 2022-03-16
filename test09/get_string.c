#include <stdio.h>

#include "get_string.h"

// print a line from stream using fgetc (only)
// reads  in at  most one less than size characters from stream and stores them into the
// buffer pointed to by s.  Reading stops after an EOF or a newline.  If a newline is read, it  is
// stored  into  the buffer.  A terminating null byte ('\0') is stored after the last character in the buffer.
void get_string(char *s, int size, FILE *stream) {
    int i = 0;
    int temp;
    while(i <= size - 1){
        temp = fgetc(stdin);
        //new line can only be added if there are 2 free spaces in array
        if(i == size - 1){
            s[i] = '\0';
            break;
        }
        else if(temp == '\n'){
            s[i] = '\n';
            s[i + 1] = '\0';
            break;
        }
        else if(temp == EOF){
            s[i] = '\0';
            break;
        }
        s[i] = temp;
        i++;
    }
}
