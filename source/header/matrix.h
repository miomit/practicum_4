#include "./fraction.h"

typedef struct {
    int row, col;
    Fraction*** elems;
} Matrix;

Matrix* new_matrix(int row, int col);

Matrix* new_matrix_default(int row, int col);

void print_matrix(Matrix* matrix);

void destroy_matrix(Matrix* matrix);