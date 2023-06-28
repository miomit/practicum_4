#include "./header/matrix.h"
#include <stdlib.h>
#include <stdio.h>

Matrix* new_matrix(int row, int col)
{
    Matrix* matrix = (Matrix*)malloc(sizeof(Matrix));

    if (matrix != NULL)
    {
        matrix->row = row;
        matrix->col = col;

        matrix->elems = (Fraction***)calloc(row, sizeof(Fraction**));

        for (int r = 0; r < matrix->row; r++)
            matrix->elems[r] = (Fraction**)calloc(col, sizeof(Fraction*));
    }

    return matrix;
}

Matrix* new_matrix_square(int size)
{
    return new_matrix(size, size);
}

Matrix* new_matrix_default(int row, int col)
{
    Matrix* matrix = new_matrix(row, col);

    for (int i = 0; i < matrix->row; i++)
        for (int j = 0; j < matrix->col; j++)
            matrix->elems[i][j] = new_fraction_default();

    return matrix;
}

Matrix* new_matrix_square_default(int size)
{
    return new_matrix_default(size, size);
}

Matrix* new_matrix_square_scalar(int size, Fraction* frac)
{
    Matrix* matrix = new_matrix_square(size);

    for (int i = 0; i < matrix->row; i++)
        for (int j = 0; j < matrix->col; j++)
            if (i == j)
                matrix->elems[i][j] = copy_fraction(frac);
            else
                matrix->elems[i][j] = new_fraction_default();

    return matrix;
}

Matrix* new_matrix_square_identity(int size)
{
    return new_matrix_square_scalar(size, new_fraction_num(1));
}

Matrix* copy_matrix(Matrix* matrix)
{
    Matrix* matrix_copy = new_matrix_default(matrix->row, matrix->col);

    for (int i = 0; i < matrix->row; i++)
        for (int j = 0; j < matrix->col; j++)
            set_elem_matrix(matrix_copy,
                            i,
                            j,
                            copy_fraction(matrix->elems[i][j]));

    return matrix_copy;
}

Matrix* transform_matrix(Matrix* matrix)
{
    Matrix* matrix_res = new_matrix(matrix->col, matrix->row);

    for (int i = 0; i < matrix->row; i++)
        for (int j = 0; j < matrix->col; j++)
            matrix_res->elems[j][i] = get_elem_matrix(matrix, i, j);

    destroy_matrix(matrix);

    return matrix_res;
}

Matrix* mul_matrix(Matrix* matrix1, Matrix* matrix2)
{
    Matrix* matrix_res = new_matrix_default(matrix1->row, matrix2->col);

    for (int i = 0; i < matrix_res->row; i++)
        for (int j = 0; j < matrix_res->col; j++)
            for (int k = 0; k < matrix1->col; k++)
                set_elem_matrix(matrix_res, i, j,
                                add_fraction(
                                        get_elem_matrix(matrix_res, i, j),
                                        mul_fraction(
                                                get_elem_matrix(matrix1, i, k),
                                                get_elem_matrix(matrix2, k, j)
                                                )
                                        ));

    destroy_matrix(matrix1);
    destroy_matrix(matrix2);

    return matrix_res;
}

Matrix* add_matrix(Matrix* matrix1, Matrix* matrix2)
{
    Matrix* matrix_res = new_matrix(matrix1->row, matrix1->col);

    for (int i = 0; i < matrix_res->row; i++)
        for (int j = 0; j < matrix_res->col; j++)
            matrix_res->elems[i][j] = add_fraction(
                    get_elem_matrix(matrix1, i, j),
                    get_elem_matrix(matrix2, i, j)
            );

    destroy_matrix(matrix1);
    destroy_matrix(matrix2);

    return matrix_res;
}

Matrix* sub_matrix(Matrix* matrix1, Matrix* matrix2)
{
    Matrix* matrix_res = new_matrix(matrix1->row, matrix1->col);

    for (int i = 0; i < matrix_res->row; i++)
        for (int j = 0; j < matrix_res->col; j++)
            matrix_res->elems[i][j] = sub_fraction(
                    get_elem_matrix(matrix1, i, j),
                    get_elem_matrix(matrix2, i, j)
            );

    destroy_matrix(matrix1);
    destroy_matrix(matrix2);

    return matrix_res;
}

Matrix* mul_frac_matrix(Matrix* matrix, Fraction* frac)
{
    Matrix* matrix_res = new_matrix(matrix->row, matrix->col);

    for (int i = 0; i < matrix_res->row; i++)
        for (int j = 0; j < matrix_res->col; j++)
            matrix_res->elems[i][j] = mul_fraction(
                    get_elem_matrix(matrix, i, j),
                    copy_fraction(frac)
            );

    destroy_fraction(frac);
    destroy_matrix(matrix);

    return matrix_res;
}

void swap_rows_matrix(Matrix* matrix, int row1, int row2)
{
    for (int col = 0; col < matrix->col; col++)
    {
        Fraction* tmp = copy_fraction(matrix->elems[row1][col]);
        set_elem_matrix(matrix, row1, col, matrix->elems[row2][col]);
        matrix->elems[row2][col] = tmp;
    }
}

void swap_columns_matrix(Matrix* matrix, int col1, int col2)
{
    for (int row = 0; row < matrix->row; row++)
    {
        Fraction* tmp = copy_fraction(matrix->elems[row][col1]);
        set_elem_matrix(matrix, row, col1, matrix->elems[row][col2]);
        matrix->elems[row][col2] = tmp;
    }
}

void mul_frac_row_matrix(Matrix* matrix, int row, Fraction* frac)
{
    for (int col = 0; col < matrix->col; col++)
    {
        set_elem_matrix(matrix, row, col,
                        mul_fraction(
                                get_elem_matrix(matrix, row, col),
                                copy_fraction(frac)
                                ));
    }

    destroy_fraction(frac);
}

void mul_frac_column_matrix(Matrix* matrix, int col, Fraction* frac)
{
    for (int row = 0; row < matrix->row; row++)
    {
        set_elem_matrix(matrix, row, col,
                        mul_fraction(
                                get_elem_matrix(matrix, row, col),
                                copy_fraction(frac)
                        ));
    }

    destroy_fraction(frac);
}

void row_add_row_mul_frac_matrix(Matrix* matrix, int row1, int row2, Fraction* frac)
{
    for (int col = 0; col < matrix->col; col++)
    {
        set_elem_matrix( matrix, row1, col, add_fraction(
                get_elem_matrix(matrix, row1, col),
                mul_fraction(
                        get_elem_matrix(matrix, row2, col),
                        copy_fraction(frac)
                        )
                ));
    }

    destroy_fraction(frac);
}

void column_add_column_mul_frac_matrix(Matrix* matrix, int col1, int col2, Fraction* frac)
{
    for (int row = 0; row < matrix->row; row++)
    {
        set_elem_matrix( matrix, row, col1, add_fraction(
                get_elem_matrix(matrix, row, col1),
                mul_fraction(
                        get_elem_matrix(matrix, row, col2),
                        copy_fraction(frac)
                )
        ));
    }

    destroy_fraction(frac);
}

Fraction* det_matrix(Matrix* matrix)
{
    Fraction* lambda = new_fraction_num(1);

    for (int dioganal = 0; dioganal < matrix->row; dioganal++)
    {
        if (is_zero_fraction(get_elem_matrix(matrix, dioganal, dioganal)))
        {
            int row_no_zero_elem = -1;

            for (int i = 1; i < matrix->row - dioganal; i++)
            {
                if (!is_zero_fraction(get_elem_matrix(matrix, dioganal + i, dioganal)))
                {
                    row_no_zero_elem = dioganal + i;
                    break;
                }
            }

            if (row_no_zero_elem != -1)
            {
                neg_fraction(lambda);
                swap_rows_matrix(matrix, dioganal, row_no_zero_elem);
            }
            else
            {
                set_fraction(lambda, new_fraction_default());
                break;
            }
        }

        Fraction* inverse_diagonal_element = inv_fraction(get_elem_matrix(matrix, dioganal, dioganal));

        mul_frac_row_matrix(matrix, dioganal, copy_fraction(inverse_diagonal_element));

        lambda = mul_fraction(lambda, inverse_diagonal_element);

        for (int i = 1; i < matrix->row - dioganal; i++)
        {
            row_add_row_mul_frac_matrix(matrix,
                                        dioganal + i,
                                        dioganal,
                                        neg_fraction(get_elem_matrix(matrix, dioganal + i, dioganal)));
        }
    }

    destroy_matrix(matrix);

    return cut_fraction(inv_fraction(lambda));
}

Fraction* get_elem_matrix(Matrix* matrix, int row, int col)
{
    return copy_fraction(matrix->elems[row][col]);
}

void set_elem_matrix(Matrix* matrix, int row, int col, Fraction* new_elem)
{
    set_fraction(matrix->elems[row][col], new_elem);
}

bool is_equal_matrix(Matrix* matrix1, Matrix* matrix2)
{
    if (matrix1->row != matrix2->row || matrix1->col != matrix2->col)
        return false;

    for (int i = 0; i < matrix1->row; i++)
        for (int j = 0; j < matrix1->col; j++)
            if (!is_equal_fraction(matrix1->elems[i][j], matrix2->elems[i][j]))
                return false;

    return true;
}

void print_matrix(Matrix* matrix)
{
    for (int i = 0; i < matrix->row; i++) {
        for (int j = 0; j < matrix->col; j++) {
            print_fraction(get_elem_matrix(matrix, i, j));
            printf("\t");
        }
        printf("\n");
    }
}

void destroy_matrix(Matrix* matrix)
{
    if (matrix != NULL){
        for (int i = 0; i < matrix->row; i++) {
            for (int j = 0; j < matrix->col; j++)
                destroy_fraction(matrix->elems[i][j]);
            free(matrix->elems[i]);
        }
        free(matrix->elems);
        free(matrix);
    }
}