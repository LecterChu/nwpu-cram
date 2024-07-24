#include <stdio.h>
#include <stdlib.h>

typedef struct Matrix_node_col
{
    int col;
    int value;
    struct Matrix_node_col *next;
} Matrix_node_col;

typedef struct Matrix_node_row
{
    int row;
    Matrix_node_col *col;
    struct Matrix_node_row *row_next;
} Matrix_node_row;

typedef struct
{
    int row;
    int col;
    Matrix_node_row *next;
} Matrix;

Matrix *create_matrix(int row, int col)
{
    Matrix *matrix = (Matrix *)malloc(sizeof(Matrix));
    matrix->row = row;
    matrix->col = col;
    matrix->next = NULL;
    return matrix;
}

void free_matrix(Matrix *matrix)
{
    Matrix_node_row *row_node = matrix->next;
    while (row_node != NULL)
    {
        Matrix_node_row *tmp_row = row_node;
        row_node = row_node->row_next;
        Matrix_node_col *col_node = tmp_row->col;
        while (col_node != NULL)
        {
            Matrix_node_col *tmp_col = col_node;
            col_node = col_node->next;
            free(tmp_col);
        }
        free(tmp_row);
    }
    free(matrix);
}

void insert_matrix(Matrix *matrix, int row, int col, int value)
{
    if(!value) return;
    Matrix_node_row *row_node = matrix->next;
    Matrix_node_row *prev_row = NULL;
    while (row_node != NULL && row_node->row < row)
    {
        prev_row = row_node;
        row_node = row_node->row_next;
    }
    if (row_node == NULL || row_node->row > row)
    {
        Matrix_node_row *new_row = (Matrix_node_row *)malloc(sizeof(Matrix_node_row));
        new_row->row = row;
        new_row->col = NULL;
        new_row->row_next = row_node;
        if (prev_row == NULL)
        {
            matrix->next = new_row;
        }
        else
        {
            prev_row->row_next = new_row;
        }
        row_node = new_row;
    }
    Matrix_node_col *col_node = row_node->col;
    Matrix_node_col *prev_col = NULL;
    while (col_node != NULL && col_node->col < col)
    {
        prev_col = col_node;
        col_node = col_node->next;
    }
    if (col_node == NULL || col_node->col > col)
    {
        Matrix_node_col *new_col = (Matrix_node_col *)malloc(sizeof(Matrix_node_col));
        new_col->col = col;
        new_col->value = value;
        new_col->next = col_node;
        if (prev_col == NULL)
        {
            row_node->col = new_col;
        }
        else
        {
            prev_col->next = new_col;
        }
    }
    else
    {
        col_node->value = value;
    }
}

Matrix* transpose_matrix_B(Matrix *matrix)
{
    Matrix *tmp = create_matrix(matrix->col, matrix->row);
    Matrix_node_col **rows = (Matrix_node_col **)malloc(matrix->col * sizeof(Matrix_node_col *));
    Matrix_node_col **rows_curr = (Matrix_node_col **)malloc(matrix->col * sizeof(Matrix_node_col *));

    for (int i = 0; i < matrix->col; i++)
    {
        rows[i] = NULL;
        rows_curr[i] = NULL;
    }
    Matrix_node_row *row_node = matrix->next;
    while (row_node != NULL)
    {
        Matrix_node_col *col_node = row_node->col;
        while (col_node != NULL)
        {
            Matrix_node_col *curr_row = rows_curr[col_node->col - 1];
            if (curr_row == NULL)
            {
                Matrix_node_col *new_col = (Matrix_node_col *)malloc(sizeof(Matrix_node_col));
                new_col->col = row_node->row;
                new_col->value = col_node->value;
                new_col->next = NULL;
                rows[col_node->col - 1] = new_col;
                rows_curr[col_node->col - 1] = new_col;
            }
            else{

                Matrix_node_col *new_col = (Matrix_node_col *)malloc(sizeof(Matrix_node_col));
                new_col->col = row_node->row;
                new_col->value = col_node->value;
                new_col->next = NULL;
                curr_row->next = new_col;
                rows_curr[col_node->col - 1] = new_col;

            }
            
            col_node = col_node->next;
        }
        row_node = row_node->row_next;
    }
    Matrix_node_row *prev_row = NULL;
   
    for (int i = 0; i < matrix->col; i++)
    {
        Matrix_node_col *new_row = rows[i];
        if(!new_row) continue;
        Matrix_node_row *row_node = (Matrix_node_row *)malloc(sizeof(Matrix_node_row));
        row_node->row = i + 1;
        row_node->col = new_row;
        row_node->row_next = NULL;
        
        if (prev_row == NULL)
        {
            tmp->next = row_node;
        }
        else
        {
            prev_row->row_next = row_node;
        }
        prev_row = row_node;
    }
    free(rows);
    free(rows_curr);
    return tmp;
}

Matrix *transpose_matrix(Matrix *matrix)
{
    Matrix *tmp = create_matrix(matrix->col, matrix->row);
    Matrix_node_row *row_node = matrix->next;
    while (row_node != NULL) // 转置（实际上有更高效的算法（遍历列并按行插入））
    {
        Matrix_node_col *col_node = row_node->col;
        while (col_node != NULL)
        {
            insert_matrix(tmp, col_node->col, row_node->row, col_node->value);
            col_node = col_node->next;
        }
        row_node = row_node->row_next;
    }
    return tmp;
}

int main()
{
    int col, row;
    scanf("%d %d", &row, &col);
    Matrix *matrix = create_matrix(row, col);
    do
    {

        int r, c, v;
        scanf("%d %d %d", &r, &c, &v);
        if (r == 0 && c == 0 && v == 0)
            break;
        insert_matrix(matrix, r, c, v);
    } while (1);
    Matrix* trans = transpose_matrix(matrix);
    // print matrix
    Matrix_node_row *row_node = trans->next;
    while (row_node != NULL)
    {
        Matrix_node_col *col_node = row_node->col;
        while (col_node != NULL)
        {
            printf("%d %d %d\n", row_node->row, col_node->col, col_node->value);
            col_node = col_node->next;
        }
        row_node = row_node->row_next;
    }
   
    free_matrix(matrix);
    free_matrix(trans);
}
