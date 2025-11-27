CC = gcc
CFLAGS1 = -std=c11 -Wextra -Werror -Wall -g
CFLAGS2 = -c -Iinclude
CLIBS = -lcheck -lm -lsubunit

all: s21_string.a

test:  s21_string.a
	$(CC) $(CFLAGS1) tests.c  s21_string.a  -o test `pkg-config --cflags --libs check` -lm
	./test


s21_string.a: s21_string.o  s21_sprintf.o s21_sscanf.o
	ar rc s21_string.a s21_string.o  s21_sprintf.o s21_sscanf.o

s21_string.o: clean
	$(CC) $(CFLAGS1) $(CFLAGS2) s21_string.c 

s21_sprintf.o:
	$(CC) $(CFLAGS1) $(CFLAGS2) s21_sprintf.c 

s21_sscanf.o:
	$(CC) $(CFLAGS1) $(CFLAGS2) s21_sscanf.c 
clean:
	rm -f *.o *.a *.gcno test *.out *.gcda test2 report.txt main report_main.txt
	rm -rf logs

format:
	clang-format -n *.c *.h
	clang-format -i *.c *.h


gcov_report: test
	mkdir logs
	$(CC) -fprofile-arcs -ftest-coverage s21_string.a tests.c  s21_string.c s21_sprintf.c s21_sscanf.c -o logs/gcov_report `pkg-config --cflags --libs check` -lm
	./logs/gcov_report
	gcovr --html-details -o logs/report.html
	open ./logs/report.html

main: clean
	$(CC) $(CFLAGS1) s21_string.c s21_sprintf.c s21_sscanf.c main.c -o main `pkg-config --cflags --libs check` -lm
	valgrind --tool=memcheck --leak-check=yes ./main 2> report_main.txt

clang:
	clang-format -n *.c *.h
	
valgrind:test
	valgrind --tool=memcheck --leak-check=yes ./test 2> report.txt
