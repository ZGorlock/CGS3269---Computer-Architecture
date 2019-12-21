//Zachary Gill
//CGS 3269 Spring 2017
//Program 3
//04-17-17

#include "IO.h"
#include "instruction.h"


//Variables

FILE* output;


//Functions

/*
  Loads the instructions from the code.txt file.

  Output:
    0 if there was an error
    1 otherwise
*/
int readInstructions()
{
  FILE* f;
  f = fopen(INPUT_FILE, "r");
  if (f == NULL) {
    printf("Error: Unable to open input file stream!\n");
    return 0;
  }
  
  int op = 0;
  int l = 0;
  int m = 0;

  while (!feof(f)) {
    fscanf(f, "%d %d %d", &op, &l, &m);
    fscanf(f, "\n");

    struct instruction i;
    i.OP = op;
    i.L = l;
    i.M = m;

    addInstruction(i);
  }

  if (fclose(f) != 0) {
    printf("Error: Unable to close input file stream!\n");
    return 0;
  }

  printInstructions();

  return 1;
}

/*
  Reads an int from the user for input.

  Output:
    The user input value.
*/
int read()
{
  int in = 0;
  printf("Input a value: ");
  scanf("%d", &in);
  return in;
}

/*
  Opens the stacktrace.txt output file stream to be used throughout the duration of the simulation.

  Output:
    0 if there was an error
    1 otherwise
*/
int openOutputFile()
{
  output = fopen(OUTPUT_FILE, "w");
  if (output == NULL) {
    printf("Error: Unable to open output file stream!\n");
    return 0;
  }
  return 1;
}

/*
  Closes the stacktrace.txt output file stream.

  Output:
    0 if there was an error
    1 otherwise
*/
int closeOutputFile()
{
  if (fclose(output) != 0) {
    printf("Error: Unable to close output file stream!");
    return 0;
  }
  return 1;
}

/*
  Prints preliminary information to the second section of the output file.
*/
void initializeLog()
{
  fprintf(output, "%26s%6s%6s%10s\n", "pc", "bp", "sp", "stack");
  fprintf(output, "%-24s%-6d%-6d%-6d\n", "Initial values", r.PC, r.BP, r.SP);
}