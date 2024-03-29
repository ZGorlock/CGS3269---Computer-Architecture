//Zachary Gill
//CGS 3269 Spring 2017
//Program 3
//04-17-17

#include "instruction.h"
#include "stack.h"
#include "IO.h"


//Variables

struct instruction code[MAX_CODE_LENGTH];
int codeSize = 0;
int halt = 0;


//Functions

/*
  Retrieves an instruction from the instruction array.

  Input:
    index: The index in the code array to retrieve.

  Output:
    The instruction structure that was retrieved.
*/
struct instruction getInstruction(int index)
{
  if (index > MAX_CODE_LENGTH - 1)
    printf("Error: Attempting to fetch instruction beyond maximum code index!\n");
  else if (index > codeSize - 1)
    printf("Error: Attempting to fetch instruction that doesn't exist!\n");

  return code[index];
}

/*
  Pushes an instruction onto the instruction array.

  Input:
    i: The instruction to add.
*/
void addInstruction(instruction i)
{
  if (codeSize == MAX_CODE_LENGTH - 1)
    printf("Error: Input code is too long!\n");

  code[codeSize] = i;
  codeSize++;
}

/*
  Prints out the loaded instructions to the output file in an organized format.
*/
void printInstructions()
{
  fprintf(output, "Line  OP    L     M\n");
  for (int i = 0; i < codeSize; i++) {
    fprintf(output, "%2d%7s   %-6d%d", i, opCodeName(code[i].OP), code[i].L, code[i].M);
    //if (code[i].OP == 2)
    //  fprintf(output, "  (%s)", oprName(code[i].M));
    fprintf(output, "\n");
  }
  fprintf(output, "\n");
}

/*
  Translates an op code into its instruction name.

  Input:
    op: The op code of the instruction in question.

  Output:
    The 3 character instruction name associated with the op code.
*/
const char* opCodeName(int op)
{
  switch (op) {
    case 1:
      return "LIT";
    case 2:
      return "OPR";
    case 3:
      return "LOD";
    case 4:
      return "STO";
    case 5:
      return "CAL";
    case 6:
      return "INC";
    case 7:
      return "JMP";
    case 8:
      return "JPC";
    case 9:
    case 10:
    case 11:
      return "SIO";
    default:
      return "";
  }
}

/*
  Translates an OPR m code into its instruction name.

  Input:
    m: The m code of the OPR instruction in question.

  Output:
    The 3 character OPR instruction name associated with the m code.
*/
const char* oprName(int m)
{
  switch (m) {
    case 0:
      return "RET";
    case 1:
      return "NEG";
    case 2:
      return "ADD";
    case 3:
      return "SUB";
    case 4:
      return "MUL";
    case 5:
      return "DIV";
    case 6:
      return "ODD";
    case 7:
      return "MOD";
    case 8:
      return "EQL";
    case 9:
      return "NEQ";
    case 10:
      return "LSS";
    case 11:
      return "LEQ";
    case 12:
      return "GTR";
    case 13:
      return "GEQ";
    default:
      return "";
  }
}


//Instruction Functions
/*
  The following functions each perform one of the 23 instructions of the ISA.
*/

void LIT()
{
  (r.SP)++;
  putFrame(r.SP, r.IR.M);
}

void OPR_RET()
{
  r.SP = r.BP - 1;
  r.PC = getFrame(r.SP + PC_OFFSET);
  r.BP = getFrame(r.SP + BP_OFFSET);

  ars[arCount - 1] = 0; //remove activation record after call
  arCount--;
}

void OPR_NEG()
{
  putFrame(r.SP, getFrame(r.SP) * -1);
}

void OPR_ADD()
{
  r.SP--;
  putFrame(r.SP, getFrame(r.SP) + getFrame(r.SP + 1));
}

void OPR_SUB()
{
  r.SP--;
  putFrame(r.SP, getFrame(r.SP) - getFrame(r.SP + 1));
}

void OPR_MUL()
{
  r.SP--;
  putFrame(r.SP, getFrame(r.SP) * getFrame(r.SP + 1));
}

void OPR_DIV()
{
  r.SP--;
  putFrame(r.SP, getFrame(r.SP) / getFrame(r.SP + 1));
}

void OPR_ODD()
{
  putFrame(r.SP, getFrame(r.SP) % 2);
}

void OPR_MOD()
{
  r.SP--;
  putFrame(r.SP, getFrame(r.SP) % getFrame(r.SP + 1));
}

void OPR_EQL()
{
  r.SP--;
  putFrame(r.SP, getFrame(r.SP) == getFrame(r.SP + 1));
}

void OPR_NEQ()
{
  r.SP--;
  putFrame(r.SP, getFrame(r.SP) != getFrame(r.SP + 1));
}

void OPR_LSS()
{
  r.SP--;
  putFrame(r.SP, getFrame(r.SP) < getFrame(r.SP + 1));
}

void OPR_LEQ()
{
  r.SP--;
  putFrame(r.SP, getFrame(r.SP) <= getFrame(r.SP + 1));
}

void OPR_GTR()
{
  r.SP--;
  putFrame(r.SP, getFrame(r.SP) > getFrame(r.SP + 1));
}

void OPR_GEQ()
{
  r.SP--;
  putFrame(r.SP, getFrame(r.SP) >= getFrame(r.SP + 1));
}

void LOD()
{
  r.SP++;
  putFrame(r.SP, getFrame(base(r.IR.L, r.BP) + r.IR.M));
}

void STO()
{
  putFrame(base(r.IR.L, r.BP) + r.IR.M, getFrame(r.SP));
  r.SP--;
}

void CAL()
{
  if (arCount >= MAX_LEXI_LEVELS - 1)
    printf("Error: Lexical depth overflow!\n");

  putFrame(r.SP + FV_OFFSET, 0); //Functional Value (return value)
  putFrame(r.SP + SL_OFFSET, base(r.IR.L, r.BP)); //Static Link
  putFrame(r.SP + DL_OFFSET, r.BP); //Dynamic Link
  putFrame(r.SP + RETA_OFFSET, r.PC); //Return Address
  r.BP = r.SP + 1;
  r.PC = r.IR.M;

  arCount++;
  ars[arCount - 1] = r.BP; //store the start of the new activation record
}

void INC()
{
  r.SP = r.SP + r.IR.M;
}

void JMP()
{
  r.PC = r.IR.M;
}

void JPC()
{
  if (getFrame(r.SP) == 0)
    r.PC = r.IR.M;
  r.SP = r.SP - 1;
}

void SIO_1()
{
  printf("%d\n", getFrame(r.SP));
  r.SP--;
}

void SIO_2()
{
  r.SP++;
  putFrame(r.SP, read());
}

void SIO_3()
{
  halt = 1;
  r.SP = 0;
  r.PC = 0;
  r.BP = 0;
  //fprintf(output, "\nSuccessfully halted.\n");
}