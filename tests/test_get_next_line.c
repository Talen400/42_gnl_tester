#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "get_next_line.h"

static void test_normal_file(void **state) {
    (void)state;
    
    int fd = open("test.txt", O_RDONLY);
    assert_true(fd >= 0);
    
    char *line;
    int line_count = 0;
    
    while ((line = get_next_line(fd)) != NULL) {
        line_count++;
        free(line);
    }
    
    close(fd);
    assert_true(line_count > 0);
}

static void test_empty_file(void **state) {
    (void)state;
    
    int fd = open("empty.txt", O_RDONLY);
    assert_true(fd >= 0);
    
    char *line = get_next_line(fd);
    assert_null(line);
    
    close(fd);
}

static void test_one_line_no_nl(void **state) {
    (void)state;
    
    int fd = open("one_line_no_nl.txt", O_RDONLY);
    assert_true(fd >= 0);
    
    char *line = get_next_line(fd);
    assert_non_null(line);
    assert_string_equal(line, "abcdefghijklmnopqrstuvwxyz");
    free(line);
    
    line = get_next_line(fd);
    assert_null(line);
    
    close(fd);
}

static void test_only_nl(void **state) {
    (void)state;
    
    int fd = open("only_nl.txt", O_RDONLY);
    assert_true(fd >= 0);
    
    char *line;
    int line_count = 0;
    
    while ((line = get_next_line(fd)) != NULL) {
        line_count++;
        assert_string_equal(line, "\\n\n");
        free(line);
    }
    
    close(fd);
    assert_true(line_count == 5);
}

static void test_invalid_fd(void **state) {
    (void)state;
    
    char *line;
    
    line = get_next_line(-1);
    assert_null(line);
    
    line = get_next_line(100);
    assert_null(line);
    
    int fd = open("test.txt", O_RDONLY);
    close(fd);
    line = get_next_line(fd);
    assert_null(line);
}

static void test_memory_leaks(void **state) {
    (void)state;
    
    int fd = open("test.txt", O_RDONLY);
    assert_true(fd >= 0);
    
    char *line;
    int line_count = 0;
    
    while ((line = get_next_line(fd)) != NULL) {
        line_count++;
        free(line);
    }
    
    close(fd);
    
    line = get_next_line(fd);
    assert_null(line);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_normal_file),
        cmocka_unit_test(test_empty_file),
        cmocka_unit_test(test_one_line_no_nl),
        cmocka_unit_test(test_only_nl),
        cmocka_unit_test(test_invalid_fd),
        cmocka_unit_test(test_memory_leaks),
    };
    
    return cmocka_run_group_tests(tests, NULL, NULL);
}
