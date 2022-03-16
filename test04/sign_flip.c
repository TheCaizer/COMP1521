#include "sign_flip.h"

// given the 32 bits of a float return it with its sign flipped
uint32_t sign_flip(uint32_t f) {
    int mask = 0x80000000;
    mask = mask ^ f;
    return mask;
}
