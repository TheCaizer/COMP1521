// Extract the 3 parts of a float using bit operations only

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

// separate out the 3 components of a float
float_components_t float_bits(uint32_t f) {
    int mask23 = 0b11111111111111111111111;
    int mask8 = 0xff;
    float_components_t result;
    result.fraction = mask23 & f;
    f = f >> 23;
    result.exponent = mask8 & f;
    f = f >> 8;
    result.sign = f;
    return result;
}

// given the 3 components of a float
// return 1 if it is NaN, 0 otherwise
int is_nan(float_components_t f) {
    if(f.exponent == 0xff && f.fraction != 0b00000000000000000000){
        return 1;
    }
    else{
        return 0;
    }
}

// given the 3 components of a float
// return 1 if it is inf, 0 otherwise
int is_positive_infinity(float_components_t f) {
    if(is_nan(f) == 0 && f.sign == 0 && f.exponent == 0xff){
        return 1;
    }
    else{
        return 0;
    }
}

// given the 3 components of a float
// return 1 if it is -inf, 0 otherwise
int is_negative_infinity(float_components_t f) {
    if(is_nan(f) == 0 && f.sign == 1 && f.exponent == 0xff){
        return 1;
    }
    else{
        return 0;
    }
}

// given the 3 components of a float
// return 1 if it is 0 or -0, 0 otherwise
int is_zero(float_components_t f) {
    if(f.exponent == 0x00 && f.fraction == 0b00000000000000000000){
        return 1;
    }
    else{
        return 0;
    }
}
