//
//  r_instructions.c
//  
//
//  Created by Oona Zhou on 4/21/24.
//

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "cpu.h"
//#include "r_instructions.h"
//#include "syscall.c"

#define RS(instruction) ((instruction >> 53) & 0x1F)
#define RT(instruction) ((instruction >> 48) & 0x1F)
#define RD(instruction) ((instruction >> 43) & 0x1F)
#define SHAMT(instruction) ((instruction >> 6) & 0x3F)
#define FUNCT(instruction) (instruction & 0x3F)

void add(uint64_t instruction) {
    int64_t rs = (int64_t)registers[RS(instruction)];
    int64_t rt = (int64_t)registers[RT(instruction)];
    uint64_t rd = RD(instruction);
    registers[rd] = (uint64_t)(rs + rt);
}

void sub(uint64_t instruction) {
    int64_t rs = (int64_t)registers[RS(instruction)];
    int64_t rt = (int64_t)registers[RT(instruction)];
    uint64_t rd = RD(instruction);
    registers[rd] = (uint64_t)(rs - rt);
}

void mult(uint64_t instruction) {
    int64_t rs = (int64_t)registers[RS(instruction)];
    int64_t rt = (int64_t)registers[RT(instruction)];
    uint64_t rd = RD(instruction);
    registers[rd] = (uint64_t)(rs * rt);
}

void div(uint64_t instruction) {
    int64_t rs = (int64_t)registers[RS(instruction)];
    int64_t rt = (int64_t)registers[RT(instruction)];
    uint64_t rd = RD(instruction);
    registers[rd] = (uint64_t)(rs / rt);
}

void mod(uint64_t instruction)  {
    int64_t rs = (int64_t)registers[RS(instruction)];
    int64_t rt = (int64_t)registers[RT(instruction)];
    uint64_t rd = RD(instruction);
    registers[rd] = (uint64_t)(rs % rt);
}

void and(uint64_t instruction) {
    int64_t rs = (uint64_t)registers[RS(instruction)];
    int64_t rt = (uint64_t)registers[RT(instruction)];
    uint64_t rd = RD(instruction);
    registers[rd] = (uint64_t)(rs & rt);
}

void or(uint64_t instruction) {
    int64_t rs = (int64_t)registers[RS(instruction)];
    int64_t rt = (int64_t)registers[RT(instruction)];
    uint64_t rd = RD(instruction);
    registers[rd] = (uint64_t)(rs | rt);
}

void xor(uint64_t instruction) {
    int64_t rs = (int64_t)registers[RS(instruction)];
    int64_t rt = (int64_t)registers[RT(instruction)];
    uint64_t rd = RD(instruction);
    registers[rd] = (uint64_t)(rs ^ rt);
}

void nor(uint64_t instruction)  {
    int64_t rs = (int64_t)registers[RS(instruction)];
    int64_t rt = (int64_t)registers[RT(instruction)];
    uint64_t rd = RD(instruction);
    registers[rd] = (uint64_t)(~(rs | rt));
}

//Logical left shift
void sll(uint64_t instruction) {
    int64_t rt = (int64_t)registers[RT(instruction)];
    uint64_t rd = RD(instruction);
    uint64_t shamt = SHAMT(instruction);
   // registers[rd] = (uint64_t)(rt << (int64_t)shamt);
    if (shamt >= 64) {
        registers[rd] = 0;
    } else {
        registers[rd] = rt << shamt;
    }
}

//Logical left shift variable
void sllv(uint64_t instruction) {
    int64_t rs = (int64_t)registers[RS(instruction)];
    int64_t rt = (int64_t)registers[RT(instruction)];
    uint64_t rd = RD(instruction);
    if (rt < 0 || rt >= 64) {
        registers[rd] = 0;
    } else {
        registers[rd] = (uint64_t)(rs << rt);
    }
}

//Logical right shift
void srl(uint64_t instruction) {
    uint64_t rt = registers[RT(instruction)];
    uint64_t shamt = SHAMT(instruction);
    uint64_t rd = RD(instruction);
    if (shamt >= 64) {
        registers[rd] = 0;
    } else {
        registers[rd] = rt >> shamt;
    }
}

//Logical right shift variable
void srlv(uint64_t instruction) {
    int64_t rs = (int64_t)registers[RS(instruction)];
    int64_t rt = (int64_t)registers[RT(instruction)];
    uint64_t rd = RD(instruction);
    if (rt < 0 || rt >= 64) {
            registers[rd] = 0;
    } else {
        registers[rd] = (uint64_t)(rs >> rt);
    }
}

//Logical right arithmetic
void sra(uint64_t instruction) {
    int64_t rt = (int64_t)registers[RT(instruction)];
    uint64_t rd = RD(instruction);
    uint64_t shamt = SHAMT(instruction) & 0x3F;
    registers[rd] = (uint64_t)(rt >> shamt);
}

//Logical right arithmetic variable
void srav(uint64_t instruction) {
    int64_t rs = (int64_t)registers[RS(instruction)];
    int64_t rt = (int64_t)registers[RT(instruction)];
    uint64_t rd = RD(instruction);
    registers[rd] = (uint64_t)(rs >> (rt & 0x3F));
}

void slt(uint64_t instruction) {
    int64_t rs = (int64_t)registers[RS(instruction)];
    int64_t rt = (int64_t)registers[RT(instruction)];
    uint64_t rd = RD(instruction);
    if(rs < rt){
        registers[rd] = 1;
    }
    else{
        registers[rd] = 0;
    }
}

void sltu(uint64_t instruction)  {
    uint64_t rs = registers[RS(instruction)];
    uint64_t rt = registers[RT(instruction)];
    uint64_t rd = RD(instruction);
    if(registers[rs] < registers[rt]){
        registers[rd] = 1;
    }
    else{
        registers[rd] = 0;
    }
}

void jr(uint64_t instruction) {
    npc = registers[RS(instruction)];
}

void jalr(uint64_t instruction) {
    registers[31] = pc + 8;
    npc = registers[RS(instruction)];
}

void syscall(uint64_t instruction);
