#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "../cmocka/include/cmocka.h"
#include "soma.h"  // do projeto original, em src/

// Função declarada no projeto principal
extern int soma(int a, int b);

static void test_soma_positivos(void **state) {
    assert_int_equal(soma(2, 3), 5);
}

static void test_soma_negativos(void **state) {
    assert_int_equal(soma(-1, -1), -2);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_soma_positivos),
        cmocka_unit_test(test_soma_negativos),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
