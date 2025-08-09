#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// Função do projeto principal
extern char *get_next_line(int fd);

static void test_read_file_lines(void **state) {
    int fd = open("test.txt", O_RDONLY);
    assert_true(fd >= 0);

    char *line;
    int count = 0;

    while ((line = get_next_line(fd)) != NULL) {
        printf("Linha %d: %s", ++count, line);
        free(line);
    }

    close(fd);
    assert_true(count > 0); // ou qualquer outra verificação
}
