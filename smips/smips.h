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

/////////////////////// Functions of SMIPS.c /////////////////////////////////

// Syscall simulates syscall, if register[2] = 1, 11 or 10 exits or prints
// from registers[4]. If Syscall returns 1 it breaks loops and exit() program
// due to invalid syscall instruction
int Syscall(int32_t registers[]);

// Add register[d] = register[s] + register[t]
void Add(int d, int s, int t, int32_t registers[]);

// Sub registers[d] = registers[s] - registers[t]
void Sub(int d, int s, int t, int32_t registers[]);

// And registers[d] = registers[s] & registers[t]
void And(int d, int s, int t, int32_t registers[]);

// Or registers[d] = registers[s] | registers[t]
void Or(int d, int s, int t, int32_t registers[]);

// Slt registers[d] = 1 if registers[s] < registers[t] else registers[d] = 0
void Slt(int d, int s, int t, int32_t registers[]);

// Mul registers[d] = registers[s] * registers[t]
void Mul(int d, int s, int t, int32_t registers[]);

// Beq if (registers[s] == registers[t]) {*i += I} where i is the instruction 
// number and I is the offset. Counter is the maximum amount of instruction.
// If I is greater than counter or less than zero return 1 and exit program.
// Uses pointer i as we need to change the value.
int Beq(int I, int s, int t, int32_t registers[], int *i, int counter);

// Bne if (registers[s] != registers[t]) {*i += I} where i is the instruction 
// number and I is the offset. Counter is the maximum amount of instruction.
// If I is greater than counter or less than zero return 1 and exit program.
// Uses pointer i as we need to change the value.
int Bne(int I, int s, int t, int32_t registers[], int *i, int counter);

// Addi registers[t] = registers[s] + I 
void Addi(int t, int s, int I, int32_t registers[]);

// Slti registers[t] = (registers[s] < I) if true registers[t] = 1 else = 0
void Slti(int t, int s, int I, int32_t registers[]);

// Andi registers[t] = registers[s] & I 
void Andi(int t, int s, int I, int32_t registers[]);

// Ori registers[t] = registers[s] | I 
void Ori(int t, int s, int I, int32_t registers[]);

// Lui registers[t] = I << 16
void Lui(int t, int I, int32_t registers[]);

// Prints out the MIPS instructions into terminal, 
void print_MIPS(int32_t instructions[], int counter);

// This prints out the output the mips code woudld've produce if it was executed
void print_output(int32_t registers[], int32_t instructions[], int counter);

// This prints out the non-zero registers after execution of code
void print_registers(int32_t registers[]);

// Checks if there are any invalid hex code in the file
// if it return one there is an invalid hex and exits program in main
int check_invalid(int32_t instructions[], int counter, char *filename);