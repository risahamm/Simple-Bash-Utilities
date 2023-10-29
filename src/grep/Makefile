all: check s21_grep
s21_grep: clean
	gcc -Wall -Wextra -Werror grep.c -o s21_grep

check:
	clang-format -i *.c
clean:
	