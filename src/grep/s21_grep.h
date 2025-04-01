#ifndef S21_GREP_H_
#define S21_GREP_H_

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 1024

typedef struct {
  int e;  // pattern
  int i;  // Ignore uppercase vs. lowercase
  int v;  // Invert match
  int c;  // Output count of matching lines only
  int l;  // Output matching files only
  int n;  // Precede each matching line with a line number
  int h;  // Output matching lines without preceding them by file names
  int s;  // Suppress error messages about nonexistent or unreadable files
  int f;  // Take regexes from a file
  int o;  // Output the matched parts of a matching line
} flags;

flags parse_flags(int argc, char *pattern, char *argv[], char *f_flag_file);
void flag_f(flags options, char *pattern, char *f_flag_file);
void reg_match(flags options, char *pattern, char *filename, int file_count);
void print(flags options, char *buffer, int file_count, char *filename,
           int start, int end, int count_lines);

#endif  // S21_GREP_H_