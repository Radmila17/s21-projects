CFLAGS1 = -Wall -Wextra -Werror -std=c11 -g
CFLAGS2 = -c -Iinclude 
CFILES = s21_matrix/*.c

all: s21_matrix.a

s21_matrix.a: files.o
	ar rc s21_matrix.a *.o

files.o:
	gcc $(CFLAGS1) $(CFLAGS2) $(CFILES) 

test: s21_matrix.a
	gcc $(CFLAGS1) tests/*.c s21_matrix.a -o test `pkg-config --cflags --libs check` -g
	./test
	
gcov_report: s21_matrix.a
	rm -rf logs
	mkdir logs
	gcc -fprofile-arcs -ftest-coverage s21_matrix.a tests/*.c  $(CFILES) -o logs/gcov_report `pkg-config --cflags --libs check`
	./logs/gcov_report
	gcovr --html-details  --filter='s21_matrix/'  -o logs/report.html
	open ./logs/report.html
clang:
	clang-format -n */*.c */*.h *.h
	clang-format -i */*.c */*.h 

leaks:test
	leaks -atExit -- ./test
	
rebuild:
	make clean
	make all

main: s21_matrix.a
	gcc $(CFLAGS1) main.c s21_matrix.a -o main
	rm -rf *.o *.a logs *.gcda *.gcno test

clean:
	rm -rf *.o *.a main logs *.gcda *.gcno test

valgrind: test
	valgrind --tool=memcheck --leak-check=yes  ./test -g
