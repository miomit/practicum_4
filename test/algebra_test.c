#include "./header/algebra_test.h"
#include "../source/header/algebra.h"

void algebra_test()
{
    printf("Run Agebra Test...\n");
    nod_test();
    powi_test();
}

void nod_test()
{
    int result = nod(3, 2);
    assert(result == 1);
    printf("Test passed: nod(3, 2) = %d\n", result);

    result = nod(6, 8);
    assert(result == 2);
    printf("Test passed: nod(6, 8) = %d\n", result);
}

void powi_test()
{
    int result = powi(3, 4);
    assert(result == 81);
    printf("Test passed: powi(3, 4) = %d\n", result);

    result = powi(4, 0);
    assert(result == 1);
    printf("Test passed: powi(4, 0) = %d\n", result);

    result = powi(2, 4);
    assert(result == 16);
    printf("Test passed: powi(2, 4) = %d\n", result);
}