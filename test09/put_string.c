#include <stdio.h>

#include "put_string.h"

// print s to stdout with a new line appended using fputc (only)

void put_string(char *s) {
    int counter = 0;
    while(s[counter] != '\0'){
        fputc(s[counter], stdout);
        counter++;
    }
    fputc('\n', stdout);
}
