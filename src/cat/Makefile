CFL= -Wall -Wextra -Werror
all: check s21_cat
s21_cat: clean
	gcc $(CFL) cat.c -o s21_cat
check:
	clang-format -i *.c
clean: