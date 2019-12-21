//Zachary Gill
//CGS 3269 Spring 2017
//Program 3
//04-17-17

#include "stack.h"


//Variables

int stack[MAX_STACK_HEIGHT + 1];
int ars[MAX_LEXI_LEVELS];
int arCount = 0;


//Functions

/*
  Sets the value of a frame in the stack.

  Input:
    index: The index of the stack frame to write.
    frame: The information to store on the stack.
*/
void putFrame(int index, int frame)
{
  if (index > MAX_STACK_HEIGHT)
    printf("Error: Stack overflow!\n");

  stack[index] = frame;
}

/*
  Retrieves a frame from the stack.

  Input:
    index: The index of the stack frame to read.

  Output:
    The value of the frame that was read.
*/
int getFrame(int index)
{
  if (index > MAX_STACK_HEIGHT)
    printf("Error: Attempting to access a stack index that doesn't exist!\n");

  return stack[index];
}

/*
  Prints the contents of the stack to the output file.
*/
void printStack()
{
  int ar = 0;
  for (int i = 1; i <= r.SP; i++) {
    if (i == ars[ar]) {
      fprintf(output, " |");
      ar++;
    }

    fprintf(output, " %d", stack[i]);
  }
}

/*
  Finds the base in the stack some levels down.

  Input:
    l: The L value in the instruction format
    base: The base we are looking for.

  Output:
    The location in the stack of the base.
*/
int base(int l, int base) // l stand for L in the instruction format
{
  int b1; //find base L levels down
  b1 = base;
  while (l > 0)
  {
    b1 = stack[b1 + 1];
    l--;
  }
  return b1;
}