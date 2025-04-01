#include "s21_cat.h"

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
