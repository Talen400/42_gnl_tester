CC = gcc

PROJECT_DIR = ../

CFLAGS = -Wall -Wextra \
         -Icmocka/include \
         -I. \
         -D_POSIX_C_SOURCE=200809L \
         -DHAVE_SIGNAL_H=1 \
         -DHAVE_STRINGS_H=1 \
         -DHAVE_MALLOC_H=1 \
         -DHAVE_INTTYPES_H=1

SRC = get_next_line.c get_next_line_utils.c
TESTS = tests/test_get_next_line.c
CMOCKA_SRC = cmocka/src/cmocka.c

LDLIBS = -ldl -lrt -pthread

all: prepare test clean

prepare:
	@echo "Preparing test environment..."
	if [ -f "$(PROJECT_DIR)/get_next_line.c" ]; then \
		cp $(PROJECT_DIR)/get_next_line.c .; \
	fi
	if [ -f "$(PROJECT_DIR)/get_next_line_utils.c" ]; then \
		cp $(PROJECT_DIR)/get_next_line_utils.c .; \
	fi
	if [ -f "$(PROJECT_DIR)/get_next_line.h" ]; then \
		cp $(PROJECT_DIR)/get_next_line.h .; \
	fi
	if [ -f "$(PROJECT_DIR)/get_next_line_bonus.c" ]; then \
		cp $(PROJECT_DIR)/get_next_line_bonus.c .; \
	fi
	if [ -f "$(PROJECT_DIR)/get_next_line_utils_bonus.c" ]; then \
		cp $(PROJECT_DIR)/get_next_line_utils_bonus.c .; \
	fi
	if [ -f "$(PROJECT_DIR)/get_next_line_bonus.h" ]; then \
		cp $(PROJECT_DIR)/get_next_line_bonus.h .; \
	fi
	cp tests/*.txt .
	touch empty.txt

test: $(SRC) $(TESTS) $(CMOCKA_SRC)
	$(CC) $(CFLAGS) -o test_runner $(TESTS) $(SRC) $(CMOCKA_SRC) $(LDLIBS)
	./test_runner

clean:
	rm -f test_runner
	rm -f get_next_line.c get_next_line_utils.c get_next_line.h
	rm -f get_next_line_bonus.c get_next_line_utils_bonus.c get_next_line_bonus.h
	rm -f *.txt

.PHONY: all clean prepare test
