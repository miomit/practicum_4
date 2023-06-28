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
void mul_frac_row_matrix(Matrix* matrix, int row, Fraction* frac);
void mul_frac_column_matrix(Matrix* matrix, int col, Fraction* frac);
void row_add_row_mul_frac_matrix(Matrix* matrix, int row1, int row2, Fraction* frac);
void column_add_column_mul_frac_matrix(Matrix* matrix, int col1, int col2, Fraction* frac);

Matrix* inv_matrix(Matrix* matrix);
Matrix* inv_block_matrix(Matrix* matrix);
Fraction* det_matrix(Matrix* matrix);
Fraction* det_block_matrix(Matrix* matrix);

Matrix* append_v_matrix(Matrix* matrix1, Matrix* matrix2);
Matrix* append_h_matrix(Matrix* matrix1, Matrix* matrix2);

Matrix* block_4_4(Matrix* matrix, int row_d, int col_d, int index);

Fraction* get_elem_matrix(Matrix* matrix, int row, int col);
void set_elem_matrix(Matrix* matrix, int row, int col, Fraction* new_elem);

bool is_equal_matrix(Matrix* matrix1, Matrix* matrix2);

void print_matrix(Matrix* matrix);

void destroy_matrix(Matrix* matrix);