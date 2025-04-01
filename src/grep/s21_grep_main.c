#include "s21_grep.h"

int main(int argc, char *argv[]) {
  char pattern[LENGTH] = {0};
  char f_flag_file[LENGTH / 2] = {0};
  int file_count;
  if (argc < 3) {
    printf("Usage: grep [options] template [file_name]");

  } else {
    flags options = parse_flags(argc, pattern, argv, f_flag_file);
    if (!options.e && !options.f) optind++;
    file_count = argc - optind;
    flag_f(options, pattern, f_flag_file);
    for (int i = optind; i < argc; i++) {
      FILE *fp;
      if ((fp = fopen(argv[i], "r")) != NULL) {
        reg_match(options, pattern, argv[i], file_count);
        fclose(fp);
      } else if (!options.s && fp == NULL) {
        fprintf(stderr, "grep: %s: No such file or directory\n", argv[i]);
      }
    }
  }
  return 0;
}