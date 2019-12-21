//Zachary Gill
//CGS 3269 Spring 2017
//Program 3
//04-17-17

#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <stdlib.h>


//Constants

static const char* INPUT_FILE = "code.txt";
static const char* OUTPUT_FILE = "stacktrace.txt";


//Enums

//Constants
typedef enum SizeConstants {
  MAX_STACK_HEIGHT = 2000,
  MAX_CODE_LENGTH = 500,
  MAX_LEXI_LEVELS = 3
}SizeConstants;

//Offsets
typedef enum RegisterOffset{
  BP_OFFSET = 3,
  PC_OFFSET = 4
}RegisterOffset;

typedef enum AROffset{
  FV_OFFSET = 1,
  SL_OFFSET = 2,
  DL_OFFSET = 3,
  RETA_OFFSET = 4
}AROffset;


//Structs

//Instruction Structure
typedef struct instruction {
  int OP; //opcode
  int L;  //L
  int M;  //M
}instruction;

//Register Structure
typedef struct registers {
  int SP; //Stack Pointer
  int BP; //Base Pointer
  int PC; //Program Counter
  struct instruction IR; //Instruction Register
}registers;


//Variables

extern struct registers r; //stores the registers of the simulation

extern int stack[MAX_STACK_HEIGHT + 1]; //stores the stack for the running simulation
extern int ars[MAX_LEXI_LEVELS]; //stores the location of activation records in the stack
extern int arCount; //stores the number of current activation records

extern struct instruction code[MAX_CODE_LENGTH]; //stores the code from code.txt
extern int codeSize; //stores the length of the code being executed
extern int halt; //flag to halt the execution of the simulation

extern FILE* output; //a pointer to the stacktrace.txt output file stream


#endif