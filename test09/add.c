#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "add.h"

// return the MIPS opcode for add $d, $s, $t
uint32_t add(uint32_t d, uint32_t s, uint32_t t) {
//add $d, $s, $t	add	d = s + t	000000ssssstttttddddd00000100000
    int mask5 = 0b00000;
    int mask4 = 0b0000;
    int maskLast = 0b00000100000;
    int maskneg = 0b1;
    int result = 0x00000000;

    if(s < 0){
        result = result | maskneg;
        result = result << 4;
        mask4 = mask4 | s;
        result = result | mask4;
        result = result << 5;
        mask4 = 0b0000;
    }
    else{
        mask5 = mask5 | s;
        result = result | mask5;
        result = result << 5;
        mask5 = 0b00000;
    }
    if(t < 0){
        result = result | maskneg;
        result = result << 4;
        mask4 = mask4 | t;
        result = result | mask4;
        result = result << 5;
        mask4 = 0b0000;
    }
    else{
        mask5 = mask5 | t;
        result = result | mask5;
        result = result << 5;
        mask5 = 0b00000;
    }
    if(d < 0){
        result = result | maskneg;
        result = result << 4;
        mask4 = mask4 | d;
        result = result | mask4;
        result = result << 11;
        mask4 = 0b0000;
    }
    else{
        mask5 = mask5 | d;
        result = result | mask5;
        result = result << 11;
        mask5 = 0b00000;
    }
    result = result | maskLast;
    return result;
}
