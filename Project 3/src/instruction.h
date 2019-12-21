//Zachary Gill
//CGS 3269 Spring 2017
//Program 3
//04-17-17

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "global.h"


//Function Prototypes

struct instruction getInstruction(int index);
void addInstruction(instruction i);
void printInstructions();
const char* opCodeName(int op);
const char* oprName(int m);

void LIT();
void OPR_RET();
void OPR_NEG();
void OPR_ADD();
void OPR_SUB();
void OPR_MUL();
void OPR_DIV();
void OPR_ODD();
void OPR_MOD();
void OPR_EQL();
void OPR_NEQ();
void OPR_LSS();
void OPR_LEQ();
void OPR_GTR();
void OPR_GEQ();
void LOD();
void STO();
void CAL();
void INC();
void JMP();
void JPC();
void SIO_1();
void SIO_2();
void SIO_3();


#endif