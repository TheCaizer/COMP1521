#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

// given a uint32_t value,
// return 1 iff the least significant (bottom) byte
// is equal to the 2nd least significant byte; and
// return 0 otherwise
int final_q2(uint32_t value) {
    int bottom_byte = 0xff & value;
    value = value >> 8;
    int bottom_byte2 = 0xff & value;
    if(bottom_byte == bottom_byte2){
        return 1;
    }
    return 0;
}
