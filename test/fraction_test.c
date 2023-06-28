#include "./header/fraction_test.h"
#include "../source/header/fraction.h"

void fraction_test()
{
    printf("Run Fraction Test...\n");

    cut_test();
    pow_test();
    add_test();
    sub_test();
    mul_test();
    div_test();

    new_new_fraction_str_test();
}

void new_new_fraction_str_test()
{
    Fraction* l = new_fraction_str("1/1");
    Fraction* r = new_fraction_num(1);

    assert(is_equal_fraction(l, r));

    l = new_fraction_str("-123/87");
    r = new_fraction(-123, 87);

    assert(is_equal_fraction(l, r));

    l = new_fraction_str("1");
    r = new_fraction_num(1);

    assert(is_equal_fraction(l, r));

    l = new_fraction_str("-1");
    r = new_fraction_num(-1);

    assert(is_equal_fraction(l, r));
}

void cut_test()
{
    Fraction* l = cut_fraction(new_fraction(2, 2));
    Fraction* r = new_fraction_num(1);

    assert(is_equal_fraction(l, r));
    printf("Test passed: 2/2 == 1");

    l = cut_fraction(new_fraction(18, 6));
    r = new_fraction_num(3);

    assert(is_equal_fraction(l, r));
    printf("Test passed: 18/6 == 3\n");
}

void pow_test()
{
    Fraction* l = pow_fraction(new_fraction_num(2), 3);
    Fraction* r = new_fraction_num(8);

    assert(is_equal_fraction(l, r));
    printf("Test passed: 2^3 == 8");

    l = pow_fraction(new_fraction(2, 3), 2);
    r = new_fraction(4, 9);

    assert(is_equal_fraction(l, r));
    printf("Test passed: (2/3)^2 == 4/9\n");
}

void add_test()
{
    Fraction* a = new_fraction(2, 3);
    Fraction* b = new_fraction(3, 2);

    Fraction* res = new_fraction(13, 6);

    assert(is_equal_fraction(add_fraction(a, b), res));
    printf("Test passed: 2/3 + 3/2 == 13/6\n");
}

void sub_test()
{
    Fraction* a = new_fraction(2, 3);
    Fraction* b = new_fraction(3, 2);

    Fraction* res = new_fraction(-5, 6);

    assert(is_equal_fraction(sub_fraction(a, b), res));
    printf("Test passed: 2/3 - 3/2 == 5/6\n");
}

void mul_test()
{
    Fraction* a = new_fraction(2, 3);
    Fraction* b = new_fraction(3, 2);

    Fraction* res = new_fraction_num(1);

    assert(is_equal_fraction(mul_fraction(a, b), res));
    printf("Test passed: 2/3 * 3/2 == 1\n");
}

void div_test()
{
    Fraction* a = new_fraction(2, 3);
    Fraction* b = new_fraction(3, 2);

    Fraction* res = new_fraction(4, 9);

    assert(is_equal_fraction(div_fraction(a, b), res));
    printf("Test passed: 2/3 / 3/2 == 4/9\n");
}