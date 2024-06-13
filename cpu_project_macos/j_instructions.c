//
//  j_instructions.c
//  
//
//  Created by Oona Zhou on 5/3/24.
//

#include <stdio.h>
#include "cpu.h"

//#define OPCODE(instruction) ((instruction >> 64) & 0x3F)
#define OFFSET(instruction) ((int64_t)(instruction & 0xFFFFFFFFFFFFULL))
#define RETURN(instruction) ((instruction >> 31) & 0x1F)

void j(uint64_t instruction){
    int64_t offset = OFFSET(instruction);
    if (offset & (0x800000000000UL)){
        offset |= (0xFFFFULL << 48);
    }
    npc = (pc + 8) + offset;
}

void jal(uint64_t instruction){
    int64_t offset = OFFSET(instruction);
    int64_t return_address = RETURN(instruction);
    if (offset & (0x800000000000UL)){
        offset |= (0xFFFFULL << 48);
    }
    registers[return_address] = pc + 8;
    npc = (pc + 8) + offset;
}
