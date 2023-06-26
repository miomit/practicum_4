#include <stdio.h>

#ifdef RUN_TESTS_ON_MAKE
#include "../test/header/test.h"
#endif

int main()                      
{
    #ifdef RUN_TESTS_ON_MAKE
        test();
        return 0;
    #endif

    return 0;                       
}        