#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int b;
  int e;
  int n;
  int s;
  int t;
  int E;
  int T;
  int v;
} Flags;

Flags parse_flags(int argc, char *argv[]);
void read_print(char *filename, Flags options);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: cat [-benstv] [file ...]\n");
    exit(1);
  }
  Flags options = parse_flags(argc, argv);
  for (int i = optind; i < argc; i++) {
    read_print(argv[i], options);
  }
  return 0;
}

Flags parse_flags(int argc, char *argv[]) {
  Flags options = {0, 0, 0, 0, 0, 0, 0, 0};
  const struct option long_options[] = {
      {"number-nonblank", no_argument, NULL, 'b'},
      {"number", no_argument, NULL, 'n'},
      {"squeeze-blank", no_argument, NULL, 's'},
  };

  int opt;
  int option_index;
  while ((opt = getopt_long(argc, argv, "+benstETv", long_options,
                            &option_index)) != -1) {
    switch (opt) {
      case 'b':
        options.b = 1;
        break;
      case 'e':
        options.e = 1;
        options.v = 1;
        break;
      case 'n':
        options.n = 1;
        break;
      case 's':
        options.s = 1;
        break;
      case 't':
        options.t = 1;
        options.v = 1;
        break;
      case 'E':
        options.e = 1;
        break;
      case 'T':
        options.t = 1;
        break;
      case 'v':
        options.v = 1;
        break;
      default:
        printf("Usage: cat [-benstv] [file ...]\n");
    }
  }
  return options;
}

void read_print(char *filename, Flags options) {
  FILE *fp;
  int c;
  fp = fopen(filename, "r");
  if (fp == NULL) {
    fprintf(stderr, "cat: %s: No such file or directory\n", filename);
    exit(1);
  }
  int d = 0;
  char lastC = '\n';

  int count_empty = 0;
  while ((c = fgetc(fp)) != EOF) {
    if (options.b == 1 && options.n == 1) {
      options.b = 1;
      options.n = 0;
    }
    if (options.s == 1) {
      if (c != '\n') count_empty = 0;
      if (c == '\n' && lastC == '\n') count_empty++;
      if (count_empty > 1) continue;
    }
    if (options.b == 1 && c != '\n' && lastC == '\n') {
      d++;
      printf("%6d\t", d);
    }
    if (options.n == 1 && lastC == '\n') {
      d++;
      printf("%6d\t", d);
    }
    if (options.e == 1 && c == '\n') printf("$");
    if (options.t == 1 && c == '\t') {
      c = 'I';
      printf("^");
    }
    if (options.v == 1) {
      if ((c >= 0 && c < 9) || (c > 10 && c < 32)) {
        printf("^");
        c = c + 64;
      }
      // if(c > 127 && c <=160) printf("M-^%c", c - 64);
      if (c == 127)
        printf("^?");
      else
        putchar(c);
    } else
      putchar(c);
    lastC = c;
  }

  fclose(fp);
}
