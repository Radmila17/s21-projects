PROJECT_NAME = programm
CC = gcc
CC_FLAGS = -Wall -Wextra -Werror -std=c11 -g
LDFLAGS = -lncurses

LIB_SRC = brick_game/tetris/*.c
GUI_SRC = gui/cli/frontend.c

BUILD_DIR = ./build
INSTALL_DIR =$(HOME)/tetris

GET_CURRENT_DIR = $(shell pwd)

VERSION = 1.0
DIST_NAME = tetris-$(VERSION)
DIST_FILE = $(DIST_NAME).tar.gz

DOXYGEN = doxygen
DOXYFILE = docs/Doxyfile
HTML_DIR = docs/html

BROWSER = open
ifeq ($(shell uname -s),Linux)
    BROWSER = xdg-open
endif

all: program

# tetris.a: $(LIB_SRC) $(GUI_SRC)
# 	mkdir -p $(BUILD_DIR)
# 	gcc $(CFLAGS) -c $(LIB_SRC) $(GUI_SRC)
# 	ar rcs build/tetris.a *.o

program: clean 
	mkdir -p $(BUILD_DIR)
	$(CC) $(CC_FLAGS) gui/cli/main.c $(LIB_SRC) $(GUI_SRC) -o $(BUILD_DIR)/program $(LDFLAGS)
	@rm -rf $(BUILD_DIR)/program.dSYM


install: program
	mkdir -p $(INSTALL_DIR)
	cp ./build/program $(INSTALL_DIR)/
	@echo "Установлено в: $(INSTALL_DIR)/$(PROJECT_NAME)"

uninstall:
	rm -rf $(INSTALL_DIR)/$(PROJECT_NAME)
	rm -rf $(INSTALL_DIR)
	rm -rf $(HOME)/tetris_high_scores.dat


dvi:
	doxygen
	$(BROWSER) doxygen/html/index.html


dist: clean
	mkdir -p $(DIST_NAME)
	cp -r brick_game gui tests Makefile Doxyfile $(DIST_NAME)/
	tar -czf $(DIST_FILE) $(DIST_NAME)

	rm -rf $(DIST_NAME)
	
	@echo "========================================"
	@echo "Дистрибутив создан: $(DIST_FILE)"
	@echo "Размер: $(shell du -h $(DIST_FILE) )"
	@echo "========================================"


test: clean program
	gcc $(CC_FLAGS) tests/*.c $(LIB_SRC) $(GUI_SRC) -o test_program `pkg-config --cflags --libs check` $(LDFLAGS)
	./test_program

gcov_report: clean test
	rm -rf logs
	mkdir logs
	gcc -fprofile-arcs -ftest-coverage tests/*.c  $(LIB_SRC) -o logs/gcov_report `pkg-config --cflags --libs check` -lncurses
	./logs/gcov_report
	gcovr --html-details    -o logs/report.html
	$(BROWSER) ./logs/report.html

clean:
	rm -rf $(BUILD_DIR)/$(PROJECT_NAME)
	rm -rf $(BUILD_DIR)
	rm -rf $(GET_CURRENT_DIR)/tetris_high_scores.dat
	rm -rf test_program
	rm -rf test_program.dSYM
	rm -rf logs
	rm -rf *.o
	rm -rf docs
	rm -rf doxygen
	rm -rf tetris-1.0.tar.gz


cppcheck:
	cppcheck --suppress=missingIncludeSystem --suppress=missingInclude --suppress=checkersReport .

