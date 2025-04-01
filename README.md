# Simple Bash Utils

Implementation of Bash text utilities: cat, grep. Study project.

- The program is developed in C language of C11 standard using gcc compiler.
- The program code of the cat and grep is located on the develop branch in the src/cat/ and src/grep/ folders, respectively
- The code of the program is written in accordance with Google style
- The program represents files with command line arguments
- The program is built with Makefile with appropriate targets: s21_cat, s21_grep
- Integration tests cover all flag variants and input values, based on a comparison with the behavior of real Bash utilities
- The program is developed according to the principles of structured programming

### cat Usage

Cat is one of the most frequently used commands on Unix-like operating systems. It has three related functions with regard to text files: displaying them, combining copies of them and creating new ones.

`cat [OPTION] [FILE]...`

### cat Options

| No.   | Options                                                        | Description                                  |
|-------|----------------------------------------------------------------|----------------------------------------------|
| 1     | -b (GNU: --number-nonblank)                                    | numbers only non-empty lines                 |
| 2     | -e implies -v (GNU only: -E the same, but without implying -v) | but also display end-of-line characters as $ |
| 3     | -n (GNU: --number)                                             | number all output lines                      |
| 4     | -s (GNU: --squeeze-blank)                                      | squeeze multiple adjacent blank lines        |
| 5     | -t implies -v (GNU: -T the same, but without implying -v)      | but also display tabs as ^I                  |

### grep Usage

`grep [options] template [file_name]`

### grep Options

| No.   | Options   | Description                                                    |
|-------|-----------|----------------------------------------------------------------|
| 1     | -e        | pattern                                                        |
| 2     | -i        | Ignore uppercase vs. lowercase.                                |
| 3     | -v        | Invert match.                                                  |
| 4     | -c        | Output count of matching lines only.                           |
| 5     | -l        | Output matching files only.                                    |
| 6     | -n        | Precede each matching line with a line number.                 |
| 7     | -h        | Output matching lines without preceding them by file names.    |
| 8     | -s        | Suppress error messages about nonexistent or unreadable files. |
| 9     | -f file   | Take regexes from a file.                                      |
| 10    | -o        | Output the matched parts of a matching line.                   |