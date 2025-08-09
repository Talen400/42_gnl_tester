CC = gcc

PROJECT_DIR ?= .

CFLAGS = -Wall -Wextra \
         -Icmocka/include \
         -I$(PROJECT_DIR) \
         -D_POSIX_C_SOURCE=200809L \
         -DHAVE_SIGNAL_H=1 \
         -DHAVE_STRINGS_H=1 \
         -DHAVE_MALLOC_H=1 \
         -DHAVE_INTTYPES_H=1

SRC = $(PROJECT_DIR)/*.c
TESTS = tests/*.c
CMOCKA_SRC = cmocka/src/cmocka.c

LDLIBS = -ldl -lrt -pthread

.PHONY: all clean

all: test

test:
	$(CC) $(CFLAGS) -o test_runner $(TESTS) $(SRC) $(CMOCKA_SRC) $(LDLIBS)

clean:
	rm -f test_runner
