CFLAGS1 = -Wall -Wextra -Werror -std=c11
CFLAGS2 = -c -Iinclude 

all: s21_decimal.a


s21_decimal.a: files.o
	ar rc s21_decimal.a *.o
	
files.o:
	gcc $(CFLAGS1) $(CFLAGS2)  s21_decimal/base_helpers/*.c  s21_decimal/bitwise_operations/*.c s21_decimal/conversion/*.c  s21_decimal/comparison/*.c  s21_decimal/normalization/*.c s21_decimal/arithmetic/*.c s21_decimal/other/*.c s21_decimal/print_helpers/*.c

test: s21_decimal.a
	gcc $(CFLAGS1) tests/*.c s21_decimal.a -o test `pkg-config --cflags --libs check` -g
	./test
	
gcov_report: test
	rm -rf logs
	mkdir logs
	gcc -fprofile-arcs -ftest-coverage s21_decimal.a tests/*.c ./s21_decimal/*/*.c  -o logs/gcov_report `pkg-config --cflags --libs check`
	./logs/gcov_report
	gcovr --html-details -o logs/report.html
	open ./logs/report.html
clang:
	clang-format -n */*.c */*/*.c

rebuild:
	make clean
	make all

main: s21_decimal.a
	gcc $(CFLAGS1) main.c s21_decimal.a -o main
clean:
	rm -rf *.o *.a test main logs *.gcda *.gcno
gitadd:
	git add */*.c */*.h */*/*.c */*/*.h Makefile *.h *.c
