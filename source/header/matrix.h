#include "./fraction.h"

typedef struct {
    int row, col;
    Fraction*** elems;
} Matrix;

Matrix* new_matrix(int row, int col);
Matrix* new_matrix_square(int size);
Matrix* new_matrix_default(int row, int col);
Matrix* new_matrix_square_default(int size);
Matrix* new_matrix_square_scalar(int size, Fraction* frac);
Matrix* new_matrix_square_identity(int size);

void print_matrix(Matrix* matrix);

void destroy_matrix(Matrix* matrix);