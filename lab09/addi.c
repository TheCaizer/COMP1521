// Sample solution for COMP1521 lab exercises
//
// generate the opcode for an addi instruction

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "addi.h"

// return the MIPS opcode for addi $t,$s, i
uint32_t addi(int t, int s, int i) {
    //addi $t, $s, I	t = s + I	001000ssssstttttIIIIIIIIIIIIIIII
    int mask1 = 0b001000;
    int mask2 = 0b00000;
    int mask3 = 0b00000;
    int mask4 = 0x0000;
    uint16_t maskneg = 0b1000000000000000;
    uint16_t maskneg2 = 0b000000000000000;
    int result = 0x00000000;
    mask2 = mask2 | t;
    mask3 = mask3 | s;
    if(i < 0){
        maskneg2 = maskneg2 | i;
        maskneg = maskneg | maskneg2;
        mask4 = mask4 | maskneg;
    }
    else{
        mask4 = mask4 | i;
    }
    result = result | mask1;
    result = result << 5;
    result = result | mask3;
    result = result << 5;
    result = result | mask2;
    result = result << 16;
    result = result | mask4;
    return result;
}
