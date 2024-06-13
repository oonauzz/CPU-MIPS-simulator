# MIPS Simulator Implementation

## Description

This programming assignment focuses on implementing a MIPS simulator in C. The goal is to develop a fully functional CPU emulator capable of executing MIPS assembly instructions. The simulator should support basic arithmetic, logical, memory access, branching, and system call instructions.

## Files Structure

- cpu.h: Header file containing global variables, constants, and function declarations for CPU operations.
- cpu.o: Compiled version of cpu.c, implementing core CPU functionality.
- r_instructions.h: Header file declaring procedures for R-instructions (excluding syscall).
- r_instructions.o: Compiled version of r_instructions.c, implementing R-instructions.
- i_instructions.h: Header file declaring procedures for I-instructions.
- i_instructions.o: Compiled version of i_instructions.c, implementing I-instructions.
- j_instructions.h: Header file declaring procedures for J-instructions.
- j_instructions.o: Compiled version of j_instructions.c, implementing J-instructions.
- syscall.c: Implementation of the syscall instruction.
- Makefile: Allows easy compilation of the project using make command.
- test_programs.c: Contains main function and test cases for CPU operations.
- utilities.h, utilities.c: Utility functions for printing 64-bit integers.
- register_names.h, programming.h: Auxiliary code for testing the CPU.
- ben_cpu: Working version of the MIPS simulator for reference.

## Project Structure

- Part 1: Implement R-instructions (r_instructions.c).
- Part 2: Implement I-instructions and J-instructions (i_instructions.c, j_instructions.c).
- Part 3: Implement CPU operations (cpu.c).
