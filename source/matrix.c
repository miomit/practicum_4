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