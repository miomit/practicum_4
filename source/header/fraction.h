#include <stdbool.h>

typedef struct {
    int numerator;
    int denominator;
} Fraction;

Fraction* new_fraction(int numerator, int denominator);
Fraction* new_fraction_num(int numerator);
Fraction* new_fraction_default();
Fraction* new_fraction_str(const char* str);

Fraction* copy_fraction(Fraction* frac);

Fraction* cut_fraction(Fraction* frac);

Fraction* neg_fraction(Fraction* frac);

Fraction* pow_fraction(Fraction* frac, int exp);

Fraction* inv_fraction(Fraction* frac);

double result_fraction(Fraction* frac);

int get_numerator_fraction(Fraction* frac);
int get_denominator_fraction(Fraction* frac);

void set_fraction(Fraction* old_frack, Fraction* new_frack);

bool is_zero_fraction(Fraction* frac);

void destroy_fraction(Fraction* frac);

void print_fraction(Fraction* frac);

bool is_equal_fraction(Fraction* frac1, Fraction* frac2);

Fraction* add_fraction(Fraction* frac, Fraction* other);
Fraction* sub_fraction(Fraction* frac, Fraction* other);
Fraction* mul_fraction(Fraction* frac, Fraction* other);
Fraction* div_fraction(Fraction* frac, Fraction* other);