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
            print_fraction(matrix->elems[i][j]);
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