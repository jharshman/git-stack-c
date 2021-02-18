#include "stack.h"

const int MAXFRAMES = 10;
char **stack;
int depth;

/*
 * init() initializes the memory for the stack.
 */
void initstack() {
  stack = (char **)malloc(sizeof(char *) * MAXFRAMES); 
  depth = 0;
}

/*
 * int push(const char *data) adds the input to a global stack
 */
int push(const char *data) {

  // navigate to next position in stack.
  // bottom of stack + depth (number of frames added).
  *(stack + depth) = (char *)malloc(sizeof(char) * strlen(data));

  // copy data into the stack
  strcpy(*(stack + depth), data);

  // increment the stack depth
  depth++;
  return 0;
}

/*
 * char *pop() removes and returns the char *data from the top of the stack.
 */
char *pop() {
  char *data = (char *)malloc(sizeof(char) * sizeof(*(stack + (depth-1))));
  strcpy(data, *(stack + (depth - 1)));
  free(*(stack + (depth-1)));
  depth--;
  return data;
}

/*
 * char *peek() returns but does not remove the char *data from the top of the stack.
 */
char *peek() {
  return *(stack + (depth - 1));
}
