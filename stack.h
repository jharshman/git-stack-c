#ifndef _H_STACK_
#define _H_STACK_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/*
 * initstack() initializes the memory for the stack.
 */
void initstack();
/*
 * int push(const char *data) adds the input to a global stack
 */
int push(const char *data);
/*
 * char *pop() removes and returns the char *data from the top of the stack.
 */
char *pop();
/*
 * char *peek() returns but does not remove the char *data from the top of the stack.
 */
char *peek();
#endif
