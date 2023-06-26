#include "header/algebra.h"

int nod(int a, int b)
{
    while (b != 0)
    {
        int tmp = b;
        b = a % b;
        a = tmp;
    }

    return abs(a);
}

int nok(int a, int b)
{
    return abs((a/ nod(a, b)) * b);
}

int abs(int a)
{
    return a < 0 ? -a : a;
}

int powi(int num, int exp)
{
    if (exp == 0) return 1;

    int res = num;

    for (int i = 1; i < exp; i++) res *= num; 

    return res;
}