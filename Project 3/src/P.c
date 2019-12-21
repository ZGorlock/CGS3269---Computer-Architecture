//Zachary Gill
//CGS 3269 Spring 2017
//Program 3
//04-17-17

#include "P.h"
#include "instruction.h"
#include "stack.h"
#include "IO.h"


//Variables

struct registers r;


//Functions

/*
  Runs the pMachine simulation.
*/
void pMachine()
{
  initializeRegisters();
  initializeLog();

  do {
    fetch();
    logFetch();
    execute();
    logExecute();
  } while (!halt && r.PC != 0);
}

/*
  Fetches the next instruction from the instruction array.
*/
void fetch()
{
  r.IR = getInstruction(r.PC);
  r.PC++;
}

/*
  Executes the current instruction in the simulation.
*/
void execute()
{
  switch (r.IR.OP) {
    case 1 : //LIT
      LIT();
      break;
    case 2 : //OPR
      switch (r.IR.M) {
        case 0: //RET
          OPR_RET();
          break;
        case 1: //NEG
          OPR_NEG();
          break;
        case 2: //ADD
          OPR_ADD();
          break;
        case 3: //SUB
          OPR_SUB();
          break;
        case 4: //MUL
          OPR_MUL();
          break;
        case 5: //DIV
          OPR_DIV();
          break;
        case 6: //ODD
          OPR_ODD();
          break;
        case 7: //MOD
          OPR_MOD();
          break;
        case 8: //EQL
          OPR_EQL();
          break;
        case 9: //NEQ
          OPR_NEQ();
          break;
        case 10: //LSS
          OPR_LSS();
          break;
        case 11: //LEQ
          OPR_LEQ();
          break;
        case 12: //GTR
          OPR_GTR();
          break;
        case 13: //GEQ
          OPR_GEQ();
          break;
      }
      break;
    case 3: //LOD
      LOD();
      break;
    case 4: //STO
      STO();
      break;
    case 5: //CAL
      CAL();
      break;
    case 6: //INC
      INC();
      break;
    case 7: //JMP
      JMP();
      break;
    case 8: //JPC
      JPC();
      break;
    case 9: //SIO
      switch (r.IR.M) {
        case 1: //SIO 1
          SIO_1();
          break;
        case 2: //SIO 2
          SIO_2();
          break;
        case 3: //SIO 3
          SIO_3();
          break;
      }
  }
}

/*
  Prints information about the fetched instruction to the output file.
*/
void logFetch()
{
  fprintf(output, "%2d%7s   %-6d%-6d", r.PC - 1, opCodeName(r.IR.OP), r.IR.L, r.IR.M);
}

/*
  Prints information about the current register and stack state to the output file.
*/
void logExecute()
{
  //if (r.IR.OP == 9 && r.IR.M == 3) //dont print if halted
  //  return;

  fprintf(output, "%-6d%-6d%-6d", r.PC, r.BP, r.SP);
  printStack();
  fprintf(output, "\n");
}

/*
  Initializes the registers to their default values at the start of the simulation.
*/
void initializeRegisters()
{
  r.SP = 0; //Stack Pointer
  r.BP = 1; //Base Pointer
  r.PC = 0; //Program Counter

  r.IR.OP = 0; //Instruction Register
  r.IR.L = 0;  //Instruction Register
  r.IR.M = 0;  //Instruction Register
}