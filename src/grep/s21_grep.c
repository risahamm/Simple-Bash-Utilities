#include "s21_grep.h"

flags parse_flags(int argc, char *pattern, char *argv[], char *f_flag_file) {
  flags options = {0};
  const struct option long_options[] = {{NULL, 0, NULL, 0}};
  int ch;
  int option_index;
  while ((ch = getopt_long(argc, argv, "e:ivclnhsf:o", long_options,
                           &option_index)) != -1) {
    switch (ch) {
      case 'e':
        options.e = 1;
        strcat(pattern, optarg);
        char bar[2] = "|";
        strcat(pattern, bar);
        break;
      case 'i':
        options.i = 1;
        break;
      case 'v':
        options.v = 1;
        break;
      case 'c':
        options.c = 1;
        break;
      case 'l':
        options.l = 1;
        break;
      case 'n':
        options.n = 1;
        break;
      case 'h':
        options.h = 1;
        break;
      case 's':
        options.s = 1;
        break;
      case 'f':
        options.f = 1;
        strcat(f_flag_file, optarg);
        break;
      case 'o':
        options.o = 1;
        break;
      default:
        fprintf(stderr, "Usage: grep [options] template [file_name]\n");
    }
  }
  if (!options.e && !options.f) {
    strcat(pattern, argv[optind]);
    char bar[2] = "|";
    strcat(pattern, bar);
  }
  return options;
}

void reg_match(flags options, char *pattern, char *filename, int file_count) {
  int len = strlen(pattern);
  if (pattern[len - 1] == '|') pattern[len - 1] = '\0';
  char buffer[LENGTH];
  int count_lines = 0;
  int match_count = 0;
  FILE *fp;
  fp = fopen(filename, "r");
  regex_t regex;
  regmatch_t match;
  int regflags = REG_EXTENDED;
  if (options.i) regflags = REG_EXTENDED | REG_ICASE;
  int comp = regcomp(&regex, pattern, regflags);
  int template = 0;
  if (comp == 0) {
    while ((fgets(buffer, LENGTH, fp)) != NULL) {
      template = regexec(&regex, buffer, 1, &match, 0);
      count_lines++;
      if (template == 0) match_count++;
      if ((template == 0 && !options.v) || (template == 1 && options.v))
        print(options, buffer, file_count, filename, match.rm_so, match.rm_eo,
              count_lines);
    }
    if (file_count == 1) {
      if (options.c && !options.l) printf("%d\n", match_count);
      if (!options.c && options.l && match_count >= 1) printf("%s\n", filename);
      if (options.c && options.l) {
        if (match_count > 1) match_count = 1;
        printf("%d\n", match_count);
        printf("%s\n", filename);
      }
    } else {
      if (options.c && !options.l && !options.h)
        printf("%s:%d\n", filename, match_count);
      if (options.c && !options.l && options.h) printf("%d\n", match_count);
      if (!options.c && options.l && match_count >= 1) printf("%s\n", filename);
      if (options.c && options.l && !options.h) {
        if (match_count > 1) match_count = 1;
        printf("%s:%d\n%s\n", filename, match_count, filename);
      }
      if (options.c && options.l && options.h) {
        printf("1\n%s\n", filename);
      }
    }
    fclose(fp);
    regfree(&regex);
  }
}

void flag_f(flags options, char *pattern, char *f_flag_file) {
  if (options.f) {
    FILE *fp;
    fp = fopen(f_flag_file, "r");
    int ch;
    int i = 0;
    if (fp != NULL) {
      while ((ch = fgetc(fp)) != EOF) {
        if (ch == 10 || ch == 13) {
          ch = '|';
        }
        pattern[i] = ch;
        i++;
      }
      fclose(fp);
    }
  }
}

void print(flags options, char *buffer, int file_count, char *filename,
           int start, int end, int count_lines) {
  if (!options.c && !options.l && buffer[0] != '\n') {
    if (buffer[strlen(buffer) - 1] == '\n') buffer[strlen(buffer) - 1] = 0;

    if (file_count > 1 && !options.h) printf("%s:", filename);

    if (options.n) printf("%d:", count_lines);

    if (options.o && !options.v) {
      printf("%.*s", end - start, &buffer[start]);

    } else
      printf("%s", buffer);
    printf("\n");
  }
}