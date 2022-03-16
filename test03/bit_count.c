// count bits in a uint64_t

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

// return how many 1 bits value contains
int bit_count(uint64_t value) {
    int result = 0;
    while(value){
        result += value & 1;
        value >>= 1;
    }
    return result;
}
