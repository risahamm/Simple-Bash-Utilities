#ifndef S21_CAT_H_
#define S21_CAT_H_

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int b;  // --number-nonblank
  int e;  // display end-of-line characters as $
  int n;  // numbers all output lines
  int s;  // --squeeze-blank
  int t;  // display tabs as ^
  int E;  // display end-of-line characters as $, but without implying -v
  int T;  // display tabs as ^, but without implying -v
  int v;  // --show-nonprinting
} Flags;

Flags parse_flags(int argc, char *argv[]);
void read_print(char *filename, Flags options);

#endif  // S21_CAT_H_