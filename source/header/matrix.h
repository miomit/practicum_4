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

Matrix* copy_matrix(Matrix* matrix);

Matrix* transform_matrix(Matrix* matrix);

Matrix* mul_matrix(Matrix* matrix1, Matrix* matrix2);
Matrix* add_matrix(Matrix* matrix1, Matrix* matrix2);
Matrix* sub_matrix(Matrix* matrix1, Matrix* matrix2);
Matrix* mul_frac_matrix(Matrix* matrix, Fraction* frac);

void swap_rows_matrix(Matrix* matrix, int row1, int row2);
void swap_columns_matrix(Matrix* matrix, int col1, int col2);

void set_elem_matrix(Matrix* matrix, int row, int col, Fraction* new_elem);

bool is_equal_matrix(Matrix* matrix1, Matrix* matrix2);

void print_matrix(Matrix* matrix);

void destroy_matrix(Matrix* matrix);