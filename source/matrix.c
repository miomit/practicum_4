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

Matrix* inv_matrix(Matrix* matrix)
{
    Matrix* res = new_matrix_square_identity(matrix->row);

    for (int dioganal = 0; dioganal < matrix->row; dioganal++) {
        if (is_zero_fraction(get_elem_matrix(matrix, dioganal, dioganal))) {
            int row_no_zero_elem = -1;

            for (int i = 1; i < matrix->row - dioganal; i++) {
                if (!is_zero_fraction(get_elem_matrix(matrix, dioganal + i, dioganal))) {
                    row_no_zero_elem = dioganal + i;
                    break;
                }
            }

            if (row_no_zero_elem != -1) {
                swap_rows_matrix(res, dioganal, row_no_zero_elem);
                swap_rows_matrix(matrix, dioganal, row_no_zero_elem);
            }
        }

        Fraction* inverse_diagonal_element = inv_fraction(get_elem_matrix(matrix, dioganal, dioganal));

        mul_frac_row_matrix(res, dioganal, copy_fraction(inverse_diagonal_element));
        mul_frac_row_matrix(matrix, dioganal, copy_fraction(inverse_diagonal_element));

        for (int i = 1; i < matrix->row - dioganal; i++)
        {
            row_add_row_mul_frac_matrix(res,
                                        dioganal + i,
                                        dioganal,
                                        neg_fraction(get_elem_matrix(matrix, dioganal + i, dioganal)));

            row_add_row_mul_frac_matrix(matrix,
                                        dioganal + i,
                                        dioganal,
                                        neg_fraction(get_elem_matrix(matrix, dioganal + i, dioganal)));
        }
    }

    for (int dioganal = matrix->row - 1; dioganal >= 0; dioganal--)
    {
        for (int i = 1; i <= dioganal; i++)
        {
            row_add_row_mul_frac_matrix(res,
                                        dioganal - i,
                                        dioganal,
                                        neg_fraction(get_elem_matrix(matrix, dioganal - i, dioganal)));

            row_add_row_mul_frac_matrix(matrix,
                                        dioganal - i,
                                        dioganal,
                                        neg_fraction(get_elem_matrix(matrix, dioganal - i, dioganal)));
        }
    }

    destroy_matrix(matrix);

    return res;
}

Matrix* inv_block_matrix(Matrix* matrix)
{
    int row_d = matrix->row / 2;
    int col_d = matrix->col / 2;

    Matrix* A = block_4_4(copy_matrix(matrix), row_d, col_d, 0);
    Matrix* B = block_4_4(copy_matrix(matrix), row_d, col_d, 1);
    Matrix* C = block_4_4(copy_matrix(matrix), row_d, col_d, 2);
    Matrix* D = block_4_4(copy_matrix(matrix), row_d, col_d, 3);

    Matrix* A_inv = inv_matrix(copy_matrix(A));

    Matrix* H = inv_matrix(
        sub_matrix(
            copy_matrix(D),
            mul_matrix(
                    copy_matrix(C),
                    mul_matrix(
                            copy_matrix(A_inv),
                            copy_matrix(B)
                    )
            )
    ));

    Matrix* A_res = add_matrix(
            copy_matrix(A_inv),
            mul_matrix(
                    copy_matrix(A_inv),
                    mul_matrix(
                            copy_matrix(B),
                            mul_matrix(
                                    copy_matrix(H),
                                    mul_matrix(
                                            copy_matrix(C),
                                            copy_matrix(A_inv)
                                            )
                                    )
                            )
                    )
            );

    Matrix* B_res = mul_frac_matrix(
            mul_matrix(
                    copy_matrix(A_inv),
                    mul_matrix(
                            copy_matrix(B),
                            copy_matrix(H)
                            )
                    ),
            new_fraction_num(-1)
            );

    Matrix* C_res = mul_frac_matrix(
            mul_matrix(
                    copy_matrix(H),
                    mul_matrix(
                            copy_matrix(C),
                            copy_matrix(A_inv)
                            )
            ),
            new_fraction_num(-1)
    );

    Matrix* D_res = copy_matrix(H);

    destroy_matrix(A);
    destroy_matrix(B);
    destroy_matrix(C);
    destroy_matrix(D);
    destroy_matrix(H);
    destroy_matrix(matrix);

    return append_v_matrix(
            append_h_matrix(A_res, B_res),
            append_h_matrix(C_res, D_res)
            );
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

Fraction* det_block_matrix(Matrix* matrix)
{
    int row_d = matrix->row / 2;
    int col_d = matrix->col / 2;

    Matrix* A = block_4_4(copy_matrix(matrix), row_d, col_d, 0);
    Matrix* B = block_4_4(copy_matrix(matrix), row_d, col_d, 1);
    Matrix* C = block_4_4(copy_matrix(matrix), row_d, col_d, 2);
    Matrix* D = block_4_4(copy_matrix(matrix), row_d, col_d, 3);

    if (A->row <= 100)
    {
        Fraction* det_a = det_matrix(copy_matrix(A));

        return mul_fraction(det_a,  det_matrix(
            sub_matrix(
                D,
                mul_matrix(
                        C,
                        mul_matrix(
                                inv_matrix(A),
                                B
                                )
                        )
                )));
    }
    else
    {
        Fraction* det_a = det_block_matrix(copy_matrix(A));

        return mul_fraction(det_a,  det_block_matrix(
            sub_matrix(
                D,
                mul_matrix(
                        C,
                        mul_matrix(
                                inv_block_matrix(A),
                                B
                                )
                        )
                )));
    }
}

Matrix* append_v_matrix(Matrix* matrix1, Matrix* matrix2)
{
    Matrix* matrix_res = new_matrix(matrix1->row + matrix2->row, matrix1->col);

    for (int i = 0; i < matrix1->row; i++)
        for (int j = 0; j < matrix1->col; j++)
            matrix_res->elems[i][j] = get_elem_matrix(matrix1, i, j);

    for (int i = 0; i < matrix2->row; i++)
        for (int j = 0; j < matrix2->col; j++)
            matrix_res->elems[matrix1->row + i][j] = get_elem_matrix(matrix2, i, j);

    destroy_matrix(matrix1);
    destroy_matrix(matrix2);

    return matrix_res;
}

Matrix* append_h_matrix(Matrix* matrix1, Matrix* matrix2)
{
    Matrix* matrix_res = new_matrix(matrix1->row, matrix1->col + matrix2->col);

    for (int i = 0; i < matrix1->row; i++)
        for (int j = 0; j < matrix1->col; j++)
            matrix_res->elems[i][j] = get_elem_matrix(matrix1, i, j);

    for (int i = 0; i < matrix2->row; i++)
        for (int j = 0; j < matrix2->col; j++)
            matrix_res->elems[i][matrix1->col + j] = get_elem_matrix(matrix2, i, j);

    destroy_matrix(matrix1);
    destroy_matrix(matrix2);

    return matrix_res;
}

/*
    A B
    C D, where A - 0, B - 1, C - 2, D - 3
*/
Matrix* block_4_4(Matrix* matrix, int row_d, int col_d, int index)
{
    Matrix* matrix_res;

    switch (index) {
        case 0:
            matrix_res = new_matrix(row_d, col_d);
            for (int i = 0; i < row_d; i++)
                for (int j = 0; j < col_d; j++)
                    matrix_res->elems[i][j] = get_elem_matrix(matrix, i, j);
            break;
        case 1:
            matrix_res = new_matrix(row_d, matrix->col - col_d);
            for (int i = 0; i < matrix_res->row; i++)
                for (int j = 0; j < matrix_res->col; j++)
                    matrix_res->elems[i][j] = get_elem_matrix(matrix, i, col_d + j);
            break;
        case 2:
            matrix_res = new_matrix(matrix->row - row_d, col_d);
            for (int i = 0; i < matrix_res->row; i++)
                for (int j = 0; j < matrix_res->col; j++)
                    matrix_res->elems[i][j] = get_elem_matrix(matrix, row_d + i, j);
            break;
        default:
            matrix_res = new_matrix(matrix->row - row_d, matrix->col - col_d);
            for (int i = 0; i < matrix_res->row; i++)
                for (int j = 0; j < matrix_res->col; j++)
                    matrix_res->elems[i][j] = get_elem_matrix(matrix, row_d + i, col_d + j);
            break;
    }

    destroy_matrix(matrix);

    return matrix_res;
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