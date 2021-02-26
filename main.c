#include "stack.h"

char *DOTFILE = ".git-stack";
void usage();
void chomp(char *in, int length);
int loadfromfile(const char *filename);
int writetofile(const char *filename);

void usage() {
  printf("usage: ./git-stack push|pop|peek <branchname>\n");
}

void chomp(char *in, int length) {
  if (in[length-1] == '\n')
    in[length-1] = '\0';
}

int loadfromfile(const char *filename) {
  FILE *fin;
  char buf[256];
  int retcode = 0;

  // check if file exists.
  // if it doesn't, that's okay, return 0.
  // if it does, read it and load the stack.
  if (access(filename, F_OK) == -1) {
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
    // Actually important that strlen() is called twice here.
    // This is because the length could be changed after calling chomp()
    chomp(buf, strlen(buf));
    if(push(buf, strlen(buf)) == -1); // call to stack.h's push() to load the stack with the read value.
    memset(buf, 0, 256);
  }

  fclose(fin); // Do i care about an error here? Probably not.
  return retcode;
}

int writetofile(const char *filename) {
  FILE *fout;
  int retcode = 0;

  // open the file for writing
  fout = fopen(filename, "w");
  if (fout == NULL) {
    perror("err fopen");
    return 1;
  }

  // Loop until stack is empty.
  // Important to read stack in reverse order to write into file.
  for(int i = 0; i <= stackdepth(); i++) {
    char *item = at(i);
    if (item == NULL)
      break;

    // todo: write to file...
    fprintf(fout, "%s\n", item);
  }

  return retcode;
}

int main(int argc, char *argv[]) {

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
    push(branch, strlen(branch));
  } else if (strcmp(operation, "pop") == 0) {
    data = pop();
    if (data != NULL) {
      printf("%s", data);
      free(data);
    }
  } else if (strcmp(operation, "peek") == 0) {
    data = peek();
    if (data != NULL) {
      printf("%s", data);
      free(data);
    }
  }

  int ret = 0;
  ret = writetofile(DOTFILE);
  if(ret == -1) {
    printf("error writing to dotfile: %s\n", DOTFILE);
  }

  destroystack();
  return ret;
}
