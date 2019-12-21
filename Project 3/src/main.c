//Zachary Gill
//CGS 3269 Spring 2017
//Program 3
//04-17-17

#include "global.h"
#include "P.h"
#include "IO.h"
#include "stack.h"
#include "instruction.h"


//Main Function

/*
  The main function for the PM/0 machine. This is called when the program is run.

  Input:
    The inputs are not used.

  Output:
    0 if sucessfully executed
    -1 if there was an error
*/
int main(int argc, const char* argv[])
{
  if (!openOutputFile())
    return -1;

  if (!readInstructions()) //read instructions from file
    return -1;

  pMachine(); //run PM/0

  if (!closeOutputFile())
    return -1;

  //system("pause");
  return 0;
}