#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

int bcd(int bcd_value);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= 0 && l <= 0x0909);
        int bcd_value = l;

        printf("%d\n", bcd(bcd_value));
    }

    return 0;
}

// given a  BCD encoded value between 0 .. 99
// return corresponding integer
int bcd(int bcd_value){
    int result=0;
    int i=1;
    int k;
    while(bcd_value > 0){
        result += (bcd_value & 0x0F)*i;
        bcd_value >>= 4;       
        i=i*10;       
    }
    k = result % 10;
    result = result/10;
    result = k + result;
    return result;
}

  

