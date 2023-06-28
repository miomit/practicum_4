#include "./header/input.h"
#include "./header/std.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

Matrix* input_matrix(const char* filename, const int index)
{
    char path[1024];
    chdir("/path/to/change/directory/to/");
    getcwd(path, sizeof(path));

    strncat(path, "/input/", sizeof(path));
    strncat(path, filename, sizeof(path));
    strncat(path, ".matrix", sizeof(path));

    FILE *file = fopen(path, "r");

    char line[1024];
    int count;
    fgets(line, sizeof(line), file);
    sscanf(line, "%d", &count);

    if (count <= index) {
        printf("count <= index");
        return NULL;
    }

    int c = -1;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strlen(line) == 1) continue;
        if (line[0] == '>')
        {
            c++;
        }

        if (c != index) continue;

        int row, col;
        fgets(line, sizeof(line), file);
        sscanf(line, "%d", &row);
        fgets(line, sizeof(line), file);
        sscanf(line, "%d", &col);

        Matrix* matrix = new_matrix(row, col);
        char** fracs;
        for (int i = 0; i < row; i++)
        {
            fgets(line, sizeof(line), file);
            fracs = str_split(line, ' ');
            for (int j = 0; j < col; j++)
            {
                matrix->elems[i][j] = new_fraction_str(fracs[j]);
                free(fracs[j]);
            }
            free(fracs);
        }
        fclose(file);
        return matrix;
    }

    fclose(file);
    return NULL;
}