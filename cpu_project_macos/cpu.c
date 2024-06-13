//
//  cpu.c
//  
//
//  Created by Oona Zhou on 5/6/24.
//

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "cpu.h"
#include "r_instructions.h"
#include "i_instructions.h"
#include "j_instructions.h"

/* Word size */
#define MAX_NUMBER_OF_OPCODES 64
#define OPCODE(instruction) ((instruction >> 58) & 0x3F)
#define FUNCT(instruction) (instruction & 0x3F)

#define WORD_SIZE_IN_BITS 64

/* The Registers */

#define NUM_REGISTERS 32

#define MEMORY_SIZE_IN_BYTES (1 << 20)

#define CODE_STARTING_ADDRESS ((uint64_t) 100)
#define DATA_STARTING_ADDRESS ((uint64_t) 1 << 16)

#define ADD_FUNCT (0x20)
#define SUB_FUNCT (0x22)
#define MULT_FUNCT (0x18)
#define DIV_FUNCT (0x1a)
#define MOD_FUNCT (0x1b)
#define AND_FUNCT (0x24)
#define OR_FUNCT (0x25)
#define XOR_FUNCT (0x26)
#define NOR_FUNCT (0x27)
#define SLT_FUNCT (0x2a)
#define SLTU_FUNCT (0x2b)
#define SLL_FUNCT (0x00)
#define SLLV_FUNCT (0x04)
#define SRL_FUNCT (0x02)
#define SRLV_FUNCT (0x06)
#define SRA_FUNCT (0x03)
#define SRAV_FUNCT (0x07)
#define JR_FUNCT (0x08)
#define JALR_FUNCT (0x09)
#define SYSCALL_FUNCT (0x0c)

#define ADDI_OPCODE (0x08)
#define ADDIU_OPCODE (0x09)
#define LW_OPCODE (0x23)
#define LH_OPCODE (0x21)
#define LHU_OPCODE (0x25)
#define LB_OPCODE (0x20)
#define LBU_OPCODE (0x24)
#define SW_OPCODE (0x2b)
#define SH_OPCODE (0x29)
#define SB_OPCODE (0x28)
#define LUI_OPCODE (0x0f)
#define ORI_OPCODE (0x0d)
#define ANDI_OPCODE (0x0c)
#define XORI_OPCODE (0x0e)
#define SLTI_OPCODE (0x0a)
#define SLTIU_OPCODE (0x0b)
#define BEQ_OPCODE (0x04)
#define BNE_OPCODE (0x05)

#define J_OPCODE (0x02)
#define JAL_OPCODE (0x03)

uint64_t registers[NUM_REGISTERS];
uint8_t memory[MEMORY_SIZE_IN_BYTES];
uint64_t pc;
uint64_t npc;

int all_execution = FALSE;

void cpu_initialize(){
    pc = CODE_STARTING_ADDRESS;
    npc = CODE_STARTING_ADDRESS;
    registers[29] = STACK_STARTING_ADDRESS;
    registers[0] = 0;
    all_execution = FALSE;
}

void r_functions(uint64_t instruction){
    uint8_t func = FUNCT(instruction);
    
    switch(func){
        case ADD_FUNCT:
            add(instruction);
            break;
        case SUB_FUNCT:
            sub(instruction);
            break;
        case MULT_FUNCT:
            mult(instruction);
            break;
        case DIV_FUNCT:
            div(instruction);
            break;
        case MOD_FUNCT:
            mod(instruction);
            break;
        case AND_FUNCT:
            and(instruction);
            break;
        case OR_FUNCT:
            or(instruction);
            break;
        case XOR_FUNCT:
            xor(instruction);
            break;
        case NOR_FUNCT:
            nor(instruction);
            break;
        case SLL_FUNCT:
            sll(instruction);
            break;
        case SRL_FUNCT:
            srl(instruction);
            break;
        case SRA_FUNCT:
            sra(instruction);
            break;
        case SLT_FUNCT:
            slt(instruction);
            break;
        case SLTU_FUNCT:
            sltu(instruction);
            break;
        case JR_FUNCT:
            jr(instruction);
            break;
        case JALR_FUNCT:
            jalr(instruction);
            break;
        case SYSCALL_FUNCT:
            syscall(instruction);
            break;
        case SLLV_FUNCT:
            sllv(instruction);
            break;
        case SRLV_FUNCT:
            srlv(instruction);
            break;
        case SRAV_FUNCT:
            srav(instruction);
            break;
    }
}

void cpu_execute(){
    while (all_execution==FALSE){
        pc = npc;
        npc += 8;
        uint64_t instruction = *((uint64_t *)&memory[pc]);
        uint8_t opcode = OPCODE(instruction);
//        switch(opcode){
//            case ADDI_OPCODE:
//                addi(instruction);
//                break;
//            default:
//                cpu_exit(1);
        switch(opcode){
            case 0: r_functions(instruction);
                break;
            case ADDI_OPCODE: addi(instruction);
                break;
            case ADDIU_OPCODE: addiu(instruction);
                break;
            case LW_OPCODE: lw(instruction);
                break;
            case LH_OPCODE: lh(instruction);
                break;
            case LHU_OPCODE: lhu(instruction);
                break;
            case LB_OPCODE: lb(instruction);
                break;
            case LBU_OPCODE: lbu(instruction);
                break;
            case SW_OPCODE: sw(instruction);
                break;
            case SH_OPCODE: sh(instruction);
                break;
            case SB_OPCODE: sb(instruction);
                break;
            case LUI_OPCODE: lui(instruction);
                break;
            case ORI_OPCODE: ori(instruction);
                break;
            case ANDI_OPCODE: andi(instruction);
                break;
            case XORI_OPCODE: xori(instruction);
                break;
            case SLTI_OPCODE: slti(instruction);
                break;
            case SLTIU_OPCODE: sltiu(instruction);
                break;
            case BEQ_OPCODE: beq(instruction);
                break;
            case BNE_OPCODE: bne(instruction);
                break;
            case J_OPCODE: j(instruction);
                break;
            case JAL_OPCODE: jal(instruction);
                break;
        }
    }
}

void cpu_exit(int errorcode){
    if (errorcode == 0){
        printf("Program terminated normally.\n");
    }
    else{
        printf("Program terminated with error.\n");
    }
    all_execution = TRUE;
}
