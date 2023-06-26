#include "./header/test.h"
#include "./header/algebra_test.h"
#include "./header/fraction_test.h"

void test() 
{
    printf("RUN Test....\n");
    algebra_test();
    fraction_test();
}