// Comp1521 smips.c 
// 6/08/2020
// By Jackie Cai, z5259449
//
// This program emulates a small simple subset of the MIPS instructions.
// The input smips.c will be the 32-bit instruction codes for MIPS instructions 
// as hexadecimal numbers. And print the MIPS equivalent, output it produces
// and any non-zero registers after the program execution.

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<math.h>

#include"smips.h"

// Define the values needed to check for MIPS instruction
#define add 0b00000100000
#define sub 0b00000100010
#define and 0b00000100100
#define or 0b00000100101
#define slt 0b00000101010
#define mul 0b00000000010
#define beq 0b000100
#define bne 0b000101
#define addi 0b001000
#define slti 0b001010
#define andi 0b001100
#define ori 0b001101
#define lui 0b001111
#define syscall 0x0000000c

//defineing the registers name for syscall
#define v0 2
#define a0 4

// Define MAX number of instruction and number of registers
#define NUM_REGISTER 32
#define MAX_INSTRUCTIONS 1000

int Syscall(int32_t registers[]);
void Add(int d, int s, int t, int32_t registers[]);
void Sub(int d, int s, int t, int32_t registers[]);
void And(int d, int s, int t, int32_t registers[]);
void Or(int d, int s, int t, int32_t registers[]);
void Slt(int d, int s, int t, int32_t registers[]);
void Mul(int d, int s, int t, int32_t registers[]);
int Beq(int I, int s, int t, int32_t registers[], int *i, int counter);
int Bne(int I, int s, int t, int32_t registers[], int *i, int counter);
void Addi(int t, int s, int I, int32_t registers[]);
void Slti(int t, int s, int I, int32_t registers[]);
void Andi(int t, int s, int I, int32_t registers[]);
void Ori(int t, int s, int I, int32_t registers[]);
void Lui(int t, int I, int32_t registers[]);
void print_MIPS(int32_t instructions[], int counter);
void print_output(int32_t registers[], int32_t instructions[], int counter);
void print_registers(int32_t registers[]);
int check_invalid(int32_t instructions[], int counter, char *filename);

int main(int argc, char* argv[]){
    // open the file and store stream
    FILE *file = fopen(argv[1], "r");
    // if there is no file
    if(file == NULL){
        printf("No such file or directory: '%s'\n",argv[1]);
        exit(1);
    }
    // counter that counts the number of lines to print and max instructions
    int counter = 0;
    // variable to store the instructions
    int32_t instructions[MAX_INSTRUCTIONS];
    // array of registers of 32 from register [0 - 31] sets them to 0
    int32_t registers[NUM_REGISTER] = {0};
    // scan all instructions into an array and set counter as max instructions
    while(fscanf(file, "%x", &instructions[counter]) == 1){
        counter++;
    }
    // Checks if there are any invalid hex code if it returns 1, has and exits
    if(check_invalid(instructions, counter, argv[1]) == 1){
        exit(1);
    }
    // Prints out the MIPS instructions to terminal
    print_MIPS(instructions, counter);
    // Prints out the Output if MIPS ran it
    print_output(registers, instructions, counter);
    // close file
    fclose(file);
    //Prints out the Non-Zero registers
    print_registers(registers);
    exit(0);
}

int Syscall(int32_t registers[]){
    // print integer if register[$v0] is 1
    if(registers[v0] == 1){
        printf("%d", registers[a0]);
    }
    // exit if register[$v0] is 10
    else if(registers[v0] == 10){
        return 1;
    }
    // print character if register[$v0] is 11
    else if(registers[v0] == 11){
        //print the lowest 8 bits for $v0 = 11 through masking
        unsigned char c = registers[a0] & 0xFF;
        printf("%c", c);
    }
    else{
        // Error not a MIPS instruction (11, 10 ,1)
        printf("Unknown system call: %d\n", registers[v0]);
        return 1;
    }
    return 0;
}
void Add(int d, int s, int t, int32_t registers[]){
    // If the registers[0] cant be changed
    if(d == 0){
        return;
    }
    registers[d] = registers[s] + registers[t];
    return;
}
void Sub(int d, int s, int t, int32_t registers[]){
    // If the registers[0] cant be changed
    if(d == 0){
        return;
    }
    registers[d] = registers[s] - registers[t];
    return;
}
void And(int d, int s, int t, int32_t registers[]){
    // If the registers[0] cant be changed
    if(d == 0){
        return;
    }
    registers[d] = registers[s] & registers[t];
    return;
}
void Or(int d, int s, int t, int32_t registers[]){
    // If the registers[0] cant be changed
    if(d == 0){
        return;
    }
    registers[d] = registers[s] | registers[t];
    return;
}
void Slt(int d, int s, int t, int32_t registers[]){
    // If the registers[0] cant be changed
    if(d == 0){
        return;
    }
    if(registers[s] < registers[t]){
        registers[d] = 1;
    }
    else{
        registers[d] = 0;
    }
    return;
}
void Mul(int d, int s, int t, int32_t registers[]){
    // If the registers[0] cant be changed
    if(d == 0){
        return;
    }
    registers[d] = registers[s] * registers[t];
    return;
}
int Beq(int I, int s, int t, int32_t registers[], int *i, int counter){
    if(registers[s] == registers[t]){
        // Checks if the instruction array overflows or underflows
        int temp = *i + I;
        if(temp >= counter || temp < 0){
            return 1;
        }
        else{
            // After the function call i increments by one so you have to
            // minus one to offset the increment for the branch
            *i = *i + I - 1;
        }
    }
    return 0;
}
int Bne(int I, int s, int t, int32_t registers[], int *i, int counter){
    if(registers[s] != registers[t]){
        // Checks if the instruction array overflows or underflows
        int temp = *i + I;
        if(temp >= counter || temp < 0){
            return 1;
        }
        else{
            // After the function call i increments by one so you have to
            // minus one to offset the increment for the branch
            *i = *i + I - 1;
        }
    }
    return 0;
}
void Addi(int t, int s, int I, int32_t registers[]){
    // If the registers[0] cant be changed
    if(t == 0){
        return;
    }
    registers[t] = registers[s] + I;
    return;
}
void Slti(int t, int s, int I, int32_t registers[]){
    // If the registers[0] cant be changed
    if(t == 0){
        return;
    }
    if(registers[s] < I){
        registers[t] = 1;
    }
    else{
        registers[t] = 0;
    }
    return;
}
void Andi(int t, int s, int I, int32_t registers[]){
    // If the registers[0] cant be changed
    if(t == 0){
        return;
    }
    registers[t] = registers[s] & I;
    return;
}
void Ori(int t, int s, int I, int32_t registers[]){
    // If the registers[0] cant be changed
    if(t == 0){
        return;
    }
    registers[t] = registers[s] | I;
    return;
}
void Lui(int t, int I, int32_t registers[]){
        // If the registers[0] cant be changed
    if(t == 0){
        return;
    }
    registers[t] = I << 16;
    return;
}
void print_MIPS(int32_t instructions[], int counter){
    // This part prints only prints the MIPS equivlent
    printf("Program\n");
    for(int i = 0; i < counter; i++){
        // d,s,t,I are the registers and variables
        int d = 0b11111 & (instructions[i] >> 11);
        int t = 0b11111 & (instructions[i] >> 16);
        int s = 0b11111 & (instructions[i] >> 21);
        int I = 0xFFFF & instructions[i];
        // Converts I to an negative number if it is suppose to be negative
        // as you need 8 bytes masked to do so.
        if(I & 0x8000){
            I = 0xFFFF0000 | I;
        }
        // The upper and lower bytes to check for Instructions Subset
        // Mask the bits
        int lowerEleven = 0b11111111111 & instructions[i];
        int upperSix = (instructions[i] >> 26);
        // Check all the cases
        if(syscall == instructions[i]){
            printf("%3d: syscall\n",i);
        }
        else if(upperSix == 0b000000 && lowerEleven == add){
            printf("%3d: add  $%d, $%d, $%d\n", i, d, s, t);
        }
        else if(upperSix == 0b000000 && lowerEleven == sub){
            printf("%3d: sub  $%d, $%d, $%d\n", i, d, s, t);
        }
        else if(upperSix == 0b000000 && lowerEleven == and){
            printf("%3d: and  $%d, $%d, $%d\n", i, d, s, t);
        }
        else if(upperSix == 0b000000 && lowerEleven == or){
            printf("%3d: or  $%d, $%d, $%d\n", i, d, s, t);
        }
        else if(upperSix == 0b000000 && lowerEleven == slt){
            printf("%3d: slt  $%d, $%d, $%d\n", i, d, s, t);
        }
        else if(upperSix == 0b011100 && lowerEleven == mul){
            printf("%3d: mul  $%d, $%d, $%d\n", i, d, s, t);
        }
        else if(upperSix == beq){
            printf("%3d: beq  $%d, $%d, %d\n", i, s, t, I);
        }
        else if(upperSix == bne){
            printf("%3d: bne  $%d, $%d, %d\n", i, s, t, I);
        }
        else if(upperSix == addi){
            printf("%3d: addi $%d, $%d, %d\n", i, t, s, I);
        }
        else if(upperSix == slti){
            printf("%3d: slti $%d, $%d, %d\n", i, t, s, I);
        }
        else if(upperSix == andi){
            printf("%3d: andi $%d, $%d, %d\n", i, t, s, I);
        }
        else if(upperSix == ori){
            printf("%3d: ori  $%d, $%d, %d\n", i, t, s, I);
        }
        else if(upperSix == lui && s == 0b00000){
            printf("%3d: lui  $%d, %d\n", i, t , I);
        }
    }
    return;
}
void print_output(int32_t registers[], int32_t instructions[], int counter){
    // This prints the Output and calls the functions
    printf("Output\n");
    for(int i = 0; i < counter; i++){
        // d,s,t,I are the registers and variables
        int d = 0b11111 & (instructions[i] >> 11);
        int t = 0b11111 & (instructions[i] >> 16);
        int s = 0b11111 & (instructions[i] >> 21);
        int I = 0xFFFF & instructions[i];
        // Converts I to an negative number if it is suppose to be negative
        // as you need 8 bytes masked to do so.
        if(I & 0x8000){
            I = 0xFFFF0000 | I;
        }
        // The upper and lower bytes to check for Instructions Subset
        // Mask the bits
        int lowerEleven = 0b11111111111 & instructions[i];
        int upperSix = (instructions[i] >> 26);
        // Check all the cases
        if(syscall == instructions[i]){
            // if it returns 1 it has an error syscall instruction and exits()
            // Or the instruction was 10 and halt program silently
            if(Syscall(registers)){
                break;
            }
        }
        else if(upperSix == 0b000000 && lowerEleven == add){
            Add(d, s, t, registers);
        }
        else if(upperSix == 0b000000 && lowerEleven == sub){
            Sub(d, s, t, registers);
        }
        else if(upperSix == 0b000000 && lowerEleven == and){
            And(d, s, t, registers);
        }
        else if(upperSix == 0b000000 && lowerEleven == or){
            Or(d, s, t, registers);
        }
        else if(upperSix == 0b000000 && lowerEleven == slt){
            Slt(d, s, t, registers);
        }
        else if(upperSix == 0b011100 && lowerEleven == mul){
            Mul(d, s, t, registers);
        }
        else if(upperSix == beq){
            // if it returns 1 it overflow the instruction number and exit()
            if(Beq(I, s, t, registers, &i, counter)){
                break;
            }
        }
        else if(upperSix == bne){
            // if it returns 1 it overflow the instruction number and exit()
            if(Bne(I, s, t, registers, &i, counter)){
                break;
            }
        }
        else if(upperSix == addi){
            Addi(t, s, I, registers);
        }
        else if(upperSix == slti){
            Slti(t, s, I, registers);
        }
        else if(upperSix == andi){
            Andi(t, s, I, registers);
        }
        else if(upperSix == ori){
            Ori(t, s, I, registers);
        }
        else if(upperSix == lui && s == 0b00000){
            Lui(t, I, registers);
        }
    }
    return;
}
void print_registers(int32_t registers[]){
    // prints all Non zero registers
    printf("Registers After Execution\n");
    for(int i = 0; i < NUM_REGISTER; i++){
        if(registers[i] != 0){
            printf("$%-3d= %d\n", i , registers[i]);
        }
    }
}
int check_invalid(int32_t instructions[], int counter, char *filename){
    // This function checks if there are any  inavlid hex codes
    for(int i = 0; i < counter; i++){
        // s are the registers and variables
        int s = 0b11111 & (instructions[i] >> 21);
        // The upper and lower bytes to check for Instructions Subset
        // Mask the bits
        int lowerEleven = 0b11111111111 & instructions[i];
        int upperSix = (instructions[i] >> 26);
        // Check all the cases
        if(syscall == instructions[i]){
            continue;
        }
        else if(upperSix == 0b000000 && lowerEleven == add){
            continue;
        }
        else if(upperSix == 0b000000 && lowerEleven == sub){
            continue;
        }
        else if(upperSix == 0b000000 && lowerEleven == and){
            continue;
        }
        else if(upperSix == 0b000000 && lowerEleven == or){
            continue;
        }
        else if(upperSix == 0b000000 && lowerEleven == slt){
            continue;
        }
        else if(upperSix == 0b011100 && lowerEleven == mul){
            continue;
        }
        else if(upperSix == beq){
            continue;
        }
        else if(upperSix == bne){
            continue;
        }
        else if(upperSix == addi){
            continue;
        }
        else if(upperSix == slti){
            continue;
        }
        else if(upperSix == andi){
            continue;
        }
        else if(upperSix == ori){
            continue;
        }
        else if(upperSix == lui && s == 0b00000){
            continue;
        }
        // else its an error hex prints the file name, line number and hex code
        // and exits
        else{
            printf("%s:%d: invalid instruction code: %08X\n", filename, i+1, instructions[i]);
            return 1;
        }
    }
    return 0;
}