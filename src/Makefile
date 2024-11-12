CC = gcc
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
    LDFLAGS = -lcheck -lm --coverage
else
    LDFLAGS = -lcheck -lsubunit -lm --coverage
endif



CFLAGS = -std=c11
GCOVFLAGS = -fprofile-arcs -ftest-coverage
POSIX=-D_POSIX_C_SOURCE=200809L

OBJ_FSM = tetris.o fsm.o
OBJ_CLI = main.o cli.o
TESTS=$(wildcard ./unit_test/*.c)
INSTALL_DIR = ./bin

VERSION = 1.0
TARGET = tetris
DIST_DIR = $(TARGET)-$(VERSION)
DIST_SOURCES = ./Makefile ./unit_test ./gui ./brick_game

# HTML report directories
GCOV_REPORT_DIR = gcov_report

all: clean tetris run
# make install
# make test

tetris: tetris.a $(OBJ_CLI)
	$(CC) $(CFLAGS) $(POSIX) $^ -o $@ tetris.a -lncurses

tetris.a: clean $(OBJ_FSM)
	ar -rc tetris.a $(OBJ_FSM)
	ranlib tetris.a
	
fsm.o: brick_game/tetris/fsm.c
	$(CC) $(CFLAGS) $(POSIX) -c $< -o $@

tetris.o: brick_game/tetris/tetris.c
	$(CC) $(CFLAGS) $(POSIX) -c $< -o $@

cli.o: gui/cli/cli.c
	$(CC) $(CFLAGS) $(POSIX) -c $< -o $@

main.o: gui/cli/main.c
	$(CC) $(CFLAGS) $(POSIX) -c $< -o $@

dist: clean 
	mkdir -p $(DIST_DIR)
	cp -r $(DIST_SOURCES) $(DIST_DIR)
	tar -czf $(DIST_DIR).tar.gz $(DIST_DIR)
	rm -rf $(DIST_DIR)

dvi:
	mkdir -p docs
	pandoc info.md -o docs/info.tex
	

test: clean
	$(CC) $(CFLAGS) $(POSIX) $(TESTS) -c
	$(CC) $(CFLAGS) $(POSIX) -o test *.o ./brick_game/tetris/*.c $(LDFLAGS)
	chmod +x test
	./test



install:  uninstall tetris
	mkdir $(INSTALL_DIR)
	cp tetris $(INSTALL_DIR)
	make run

run:
	./tetris

uninstall: clean
	rm -rf $(INSTALL_DIR)

clean:
	rm -rf *.a *.o *.gcno *.gcda test *.css *.html *.gcov tetris *.txt ./doxygen
	rm -rf gcov_report *.info

style:
	clang-format -n ./brick_game/tetris/*.h ./brick_game/tetris/*.c ./gui/cli/*.c ./gui/cli/*.h ./unit_test/*.h ./unit_test/*.c


gcov_report: test
	mkdir -p $(GCOV_REPORT_DIR)
	lcov --capture --directory . --output-file coverage.info
	lcov --remove coverage.info '*/tests/*' '*/usr/*' --output-file coverage.info --ignore-errors unused
	genhtml coverage.info --output-directory $(GCOV_REPORT_DIR)
	make open_report

open_report:
	@if [ "$(UNAME)" = "Darwin" ]; then \
		open $(GCOV_REPORT_DIR)/index.html; \
	elif [ "$(UNAME)" = "Linux" ]; then \
		if grep -iq microsoft /proc/version; then \
			echo "You are using a terminal in Windows OS (WSL)!"; \
			echo "You can open html report using cmd command line enter command 'start gcov_report/index.html' ..."; \
		else \
			xdg-open $(GCOV_REPORT_DIR)/index.html; \
		fi \
	else \
		echo "Unsupported OS"; \
	fi

