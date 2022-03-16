//
// Sample solution for COMP1521 lab exercises
//
// Convert string of binary digits to 16-bit signed integer

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define N_BITS 16

int16_t sixteen_in(char *bits);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        printf("%d\n", sixteen_in(argv[arg]));
    }

    return 0;
}

//
// given a string of binary digits ('1' and '0')
// return the corresponding signed 16 bit integer
//
int16_t sixteen_in(char *bits) {
    //sets the first bit as the starting pointer
    char* start = &bits[0];
    //the result or answer
    int result = 0;
    //loops through the bits
    while(*start){
        //if the bits are one it adds one to the answer
        //then in the next loop it doubles for every bit
        result = result << 1;
        if(*start++ == '1'){
            result = result | 1;
        }
    }
    return result;
}

