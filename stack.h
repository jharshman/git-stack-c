#ifndef _H_STACK_
#define _H_STACK_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/*
 * define stackitem
 */
typedef struct stackitem stackitem;
struct stackitem {
  char *data;
  int length;
};
/*
 * initstack() initializes the memory for the stack.
 */
void initstack();
/*
 * destroystack() performs a deep-free on all remaining stackitems.
 */
void destroystack();
/*
 * stackdepth() returns the depth, or how many stackitems, are on the stack.
 */
int stackdepth();
/*
 * int push(const char *data) adds the input to a global stack
 */
int push(const char *data, int length);
/*
 * char *pop() removes and returns the char *data from the top of the stack. Frees the underlying stackitem and returns its data. It is up to the user to free this after use.
 */
char *pop();
/*
 * char *peek() returns but does not remove the char *data from the top of the stack. It is up to the user to free the data returned after use.
 */
char *peek();
/*
 * char *at(int pos) returns a pointer to the data at the position in the stack specified by the pos argument.
 * If pos is less than zero or greater than the depth of the stack, NULL is returned.
 */
char *at(int pos);
#endif
