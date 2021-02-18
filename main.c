#include "stack.h"

const char *DOTFILE = ".git-stack";

void usage();
int loadfromfile(const char *filename);
int writetofile(const char *filename);

void usage() {
  printf("usage: ./git-stack push|pop|peek <branchname>\n");
}

int loadfromfile(const char *filename) {
  FILE *fin;
  char buf[256];
  int retcode = 0;

  // check if file exists.
  // if it doesn't, that's okay, return 0.
  // if it does, read it and load the stack.
  if (!access(filename, F_OK)) {
    return 0;
  }

  // open the file for reading.
  fin = fopen(filename, "r");
  if (fin == NULL) {
    perror("err fopen");
    return 1;
  }

  // read the contetns fo the file line by line.
  // this is perfect because the structure of the file is
  // a branch per line.
  while(fgets(buf, sizeof(buf), fin)) {
    if (strlen(buf) == 0) {
      retcode = 1;
      break;
    }
    push(buf); // call to stack.h's push() to load the stack with the read value.
    memset(buf, 0, sizeof(buf));
  }

  fclose(fin); // Do i care about an error here? Probably not.
  return retcode;
}

int writetofile(const char *filename) {
  int retcode = 0;

  // todo:
  // write contents of stack to file

  return retcode;
}

int main(int argc, char *argv[]) {

  // todo:
  // do operation 
  // write file
  
  if (argc <= 1) {
    usage();
    return 1;
  }

  char *operation = argv[1];
  char *branch;
  if (argc > 1)
    branch = argv[2];

  initstack();

  loadfromfile(DOTFILE);

  // perform operation
  char *data;
  if (strcmp(operation, "push") == 0) {
    push(branch);
  } else if (strcmp(operation, "pop") == 0) {
    data = pop();
    printf("%s\n", data);
    free(data);
  } else if (strcmp(operation, "peek") == 0) {
    data = peek();
    printf("%s\n", data);
  }

  // write modified stack to DOTFILE
  // writetofile(DOTFILE);

  // todo: free stack memory
  return 0;
}
