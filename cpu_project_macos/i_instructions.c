//
//  i_instructions.c
//  
//
//  Created by Oona Zhou on 4/26/24.
//

#include <stdio.h>
#include "cpu.h"
//#include "i_instructions.h"
//#include "syscall.c"

//#define OPCODE(instruction) ((instruction >> 58) & 0x3F)
#define RS_I(instruction) ((instruction >> 53) & 0x1F)
#define RT_I(instruction) ((instruction >> 48) & 0x1F)
#define IMM(instruction) ((int64_t)(instruction & 0xFFFFFFFFFFFFULL))


void addi(uint64_t instruction){
    int64_t rs = (int64_t)registers[RS_I(instruction)];
    int64_t imm = (int64_t)IMM(instruction);
    uint64_t rt = RT_I(instruction);
    if (imm & (0x800000000000ULL)){
        imm |= (0xFFFFULL << 48);
    }
    registers[rt] = (rs + imm);
}

void addiu(uint64_t instruction){
    int64_t rs = (int64_t)registers[RS_I(instruction)];
    int64_t imm = (int64_t)IMM(instruction);
    uint64_t rt = RT_I(instruction);
    registers[rt] = (uint64_t)(rs + imm);
}


void andi(uint64_t instruction) {
    int64_t rs = (int64_t)registers[RS_I(instruction)];
    int64_t imm = (int64_t)IMM(instruction);
    uint64_t rt = RT_I(instruction);
    registers[rt] = rs & imm;
}

void ori(uint64_t instruction) {
    int64_t rs = (int64_t)registers[RS_I(instruction)];
    int64_t imm = (int64_t)IMM(instruction);
    uint64_t rt = RT_I(instruction);
    registers[rt] = rs | imm;
}

void xori(uint64_t instruction) {
    int64_t rs = (int64_t)registers[RS_I(instruction)];
    int64_t imm = (int64_t)IMM(instruction);
    uint64_t rt = RT_I(instruction);
    registers[rt] = rs ^ imm;
}

void slti(uint64_t instruction){
    int64_t rs = (int64_t)registers[RS_I(instruction)];
    int64_t imm = (int64_t)IMM(instruction);
    uint64_t rt = RT_I(instruction);
    if (imm & (0x800000000000ULL)){
        imm |= (0xFFFFULL << 48);
    }
    if (rs < imm){
        registers[rt] = 1;
    }
    else{
        registers[rt] = 0;
    }
}

void sltiu(uint64_t instruction){
    uint64_t rs = registers[RS_I(instruction)];
    int64_t imm = (int64_t)IMM(instruction);
    uint64_t rt = RT_I(instruction);
    if (rs < imm){
        registers[rt] = 1;
    }
    else{
        registers[rt] = 0;
    }
}

void beq(uint64_t instruction) {
    uint64_t rs = RS_I(instruction);
    int64_t imm = (int64_t)IMM(instruction);
    uint64_t rt = registers[RT_I(instruction)];
    if (imm & (0x800000000000ULL)){
        imm |= (0xFFFFULL << 48);
    }
    if (rs == rt){
        npc = pc + 8 + imm;
    }
}

void bne(uint64_t instruction) {
    int64_t rs = (int64_t)registers[RS_I(instruction)];
    uint64_t rt = registers[RT_I(instruction)];
    int64_t imm = (int64_t)IMM(instruction);
    if (imm & (0x800000000000ULL)){
        imm |= (0xFFFFULL << 48);
    }
    if (rs != rt) {
        npc = pc + 8 + imm;
    }
}

void lb(uint64_t instruction) {
    uint64_t rs = RS_I(instruction);
    int64_t imm = (int64_t)IMM(instruction);
    if (imm & (0x800000000000ULL)){
        imm |= (0xFFFFULL << 48);
    }
    uint64_t rt = RT_I(instruction);
    uint64_t mem = (registers[rs]) + imm;
    int8_t val1 = *((int8_t *)& memory[mem]);
    int64_t val2 = (int64_t)val1;
    if (val2 & 0x80000000) {
        val2 |= 0xFFFFFFFF00000000;
    }
    registers[rt] = val2;
}

void lbu(uint64_t instruction) {
    uint64_t rs = RS_I(instruction);
    int64_t imm = (int64_t)IMM(instruction);
    uint64_t rt = RT_I(instruction);
    if (imm & (0x800000000000ULL)){
        imm |= (0xFFFFULL << 48);
    }
    uint64_t mem = (registers[rs]) + imm;
    uint8_t val = *((uint8_t *)& memory[mem]);
    registers[rt] = val;
}

void lh(uint64_t instruction) {
    uint64_t rs = RS_I(instruction);
    int64_t imm = (int64_t)IMM(instruction);
    if (imm & (0x8000)) {
        imm |= 0xFFFFFFFFFFFF0000;
    }
    uint64_t rt = RT_I(instruction);
    
    uint64_t mem = (registers[rs]) + imm;
    int32_t val1 = *((int32_t *) &memory[mem]);
    int64_t val2 = (int64_t)val1;
    if (val2 & 0x80000000) {
        val2 |= 0xFFFFFFFF00000000;
    }
    registers[rt] = val2;
}

void lhu(uint64_t instruction) {
    uint64_t rs = RS_I(instruction);
    int64_t imm = (int64_t)IMM(instruction);
    if (imm & (0x8000)) {
        imm |= 0xFFFFFFFFFFFF0000;
    }
    uint64_t rt = RT_I(instruction);
    uint64_t mem = (registers[rs]) + imm;
    uint32_t val = *((uint32_t *) &memory[mem]);
    registers[rt] = val;
}
 
void lw(uint64_t instruction) {
    uint64_t rs = RS_I(instruction);
    int64_t imm = (int64_t)IMM(instruction);
    if (imm & (0x800000000000ULL)){
        imm |= (0xFFFFULL << 48);
    }
    uint64_t rt = RT_I(instruction);
    int64_t mem = (int64_t)(registers[rs]) + imm;
    registers[rt] = *((uint64_t *) &memory[mem]);
}


void lui(uint64_t instruction){
    uint64_t rs = RS_I(instruction);
    int64_t imm = (int64_t)IMM(instruction);
    uint64_t rt = RT_I(instruction);
    if (imm >> 32) {
        imm &= 0x0000FFFFFFFFFFFF;
    }
    registers[rt] = imm << 32;
}


void sb(uint64_t instruction){
    int64_t rs = (int64_t)RS_I(instruction);
    int64_t imm = (int64_t)IMM(instruction);
    if (imm & (0x800000000000ULL)){
        imm |= 0xFFFF000000000000;
    }
    uint64_t rt = RT_I(instruction);
    int64_t mem_address = registers[rs] + imm;
    *((uint8_t *)& memory[mem_address]) = (uint8_t)registers[rt]& 0xFF;
}

void sh(uint64_t instruction){
    int64_t rs = (int64_t)RS_I(instruction);
    int64_t imm = (int64_t)IMM(instruction);
    if (imm & (0x800000000000ULL)){
        imm |= 0xFFFF000000000000;
    }
    uint64_t rt = RT_I(instruction);
    int64_t mem = registers[rs] + imm;
    *((uint32_t *) & memory[mem]) = (uint32_t)registers[rt] & 0xFFFFFFFF;
}

void sw(uint64_t instruction) {
    uint64_t rs = RS_I(instruction);
    uint64_t imm = IMM(instruction);
    if (imm & (0x800000000000ULL)){
        imm |= (0xFFFFULL << 48);
    }
    uint64_t rt = RT_I(instruction);
    int64_t mem = registers[rs] +imm;
    *((uint64_t *) & memory[mem]) = registers[rt];
}
