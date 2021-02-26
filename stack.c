#include "stack.h"

const int MAXFRAMES = 10;
stackitem **root;
int depth;

/*
 * init() initializes the memory for the stack.
 */
void initstack() {
  root = (stackitem **)malloc(sizeof(stackitem*) * MAXFRAMES); 
  depth = 0;
}

/*
 * destroystack() performs a deep-free on all remaining stackitems.
 */
void destroystack() {
  // set depth at current instead of 1 past
  depth = depth-1;
  while(depth > 0) {
    free((*(root + depth))->data);
    free(*(root + depth));
    depth--;
  }
}

/*
 * stackdepth() returns the depth, or how many stackitems, are on the stack.
 */
int stackdepth() {
  // depth-1 is the actual number of stackitems.
  // The depth value is always equal to the next position on the stack.
  return depth-1;
}

/*
 * int push(const char *data) adds the input to a global stack
 */
int push(const char *data, int length) {

  // check if depth has reached MAXFRAMES
  if (depth > MAXFRAMES)
    return -1;

  // create new stackitem
  stackitem *newitem = (stackitem *)malloc(sizeof(stackitem));
  newitem->length = length;
  newitem->data = (char *)malloc(sizeof(char) * length);
  strcpy(newitem->data, data);

  // navigate to next position in stack.
  // bottom of stack + depth (number of frames added).
  *(root + depth) = newitem;

  // increment the stack depth
  depth++;
  return 0;
}

/*
 * char *pop() removes and returns the char *data from the top of the stack. Frees the underlying stackitem and returns its data. It is up to the user to free this after use.
 */
char *pop() {
  if (depth == 0)
    return NULL;
  char *data = (char *)malloc(sizeof(char) * 256);
  strcpy(data, (*(root + (depth - 1)))->data);
  // deep free on stackitem
  free((*(root + (depth-1)))->data);
  free(*(root + (depth-1)));
  depth--;
  return data;
}

/*
 * char *peek() returns but does not remove the char *data from the top of the stack. It is up to the user to free the data returned after use.
 */
char *peek() {
  if (depth == 0)
    return NULL;
  char *si_data = (char *)malloc(sizeof(char) * 256);
  stackitem *top = *(root + (depth - 1));
  strcpy(si_data, top->data);
  return si_data;
}

/*
 * char *at(int pos) returns a pointer to the data at the position in the stack specified by the pos argument.
 * If pos is less than zero or greater than the depth of the stack, NULL is returned.
 */
char *at(int pos) {
  if (pos > (depth-1) || pos < 0)
    return NULL;
  return (*(root + pos))->data;
}
