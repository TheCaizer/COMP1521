// Multiply a float by 2048 using bit operations only

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

// float_2048 is given the bits of a float f as a uint32_t
// it uses bit operations and + to calculate f * 2048
// and returns the bits of this value as a uint32_t
//
// if the result is too large to be represented as a float +inf or -inf is returned
//
// if f is +0, -0, +inf or -int, or Nan it is returned unchanged
//
// float_2048 assumes f is not a denormal number
//
uint32_t float_2048(uint32_t f) {
    int shifted = f;
    float_components_t comp = float_bits(shifted);
    if(is_nan(comp) == 1 || is_positive_infinity(comp) == 1 || is_zero(comp) == 1 || is_negative_infinity(comp) == 1){
        return f;
    }
    if(comp.exponent > 0xF9){
        if(comp.sign == 1){
            return 0xFF800000;
        }
        else if(comp.sign == 0){
            return 0x7F800000;
        }
    }
    comp.exponent = comp.exponent + 11;
    uint32_t new = 0x00000000;
    new = (new | comp.sign);
    new = new << 8;
    new = (new | comp.exponent);
    new = new << 23;
    new = (new | comp.fraction);
    return new;
}
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