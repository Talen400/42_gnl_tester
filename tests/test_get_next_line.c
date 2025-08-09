#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

static void test_read_file_lines(void **state) {
    (void) state;
    int fd = open("tests/test.txt", O_RDONLY);
    assert_true(fd >= 0);

    char *line;
    int count = 0;

    while ((line = get_next_line(fd)) != NULL) {
        printf("Linha %d: %s", ++count, line);
        free(line);
    }

    close(fd);
    assert_true(count > 0);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_read_file_lines),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
