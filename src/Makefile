CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11

s21_cat:
	$(CC) $(CFLAGS) cat/*.c -o s21_cat

test_cat: s21_cat
	sh cat/test_func_cat.sh

s21_grep:
	$(CC) $(CFLAGS) grep/*.c -o s21_grep

test_grep: s21_grep
	sh grep/test_func_grep.sh

clean:
	rm -rf s21_cat
	rm -rf s21_grep
	rm -rf *.log

check_style:
	clang-format -style=Google -n cat/*.c cat/*.h
	clang-format -style=Google -n grep/*.c grep/*.h

fix_style:
	clang-format -style=Google -i cat/*.c cat/*.h
	clang-format -style=Google -i grep/*.c grep/*.h