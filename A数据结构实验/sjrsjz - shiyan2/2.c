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

Matrix* transpose_matrix(Matrix *matrix)
{
    Matrix *tmp = create_matrix(matrix->col, matrix->row);
    Matrix_node_row *row_node = matrix->next;
    while (row_node != NULL)
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

Matrix* add_matrix(Matrix *A,Matrix* B){
    Matrix *tmp=create_matrix(A->row,A->col);
    Matrix_node_row *row_node_A = A->next;
    Matrix_node_row *row_node_B = B->next;
    if (!row_node_A || !row_node_B || A->row != B->row || A->col != B->col)
    {
        return NULL;
    }
    int current_row = 0;
    while(row_node_A || row_node_B){
        if(row_node_A)
            current_row = row_node_A->row > current_row ? row_node_A->row : current_row;
        else{
            current_row = A->row + 1;
        }
        if(row_node_B)
            current_row = row_node_B->row > current_row ? row_node_B->row : current_row;
        else{
            current_row = A->row + 1;
        }
        while(row_node_A && row_node_A->row<current_row){
            // insert row_node_A to tmp
            Matrix_node_row *new_row = (Matrix_node_row *)malloc(sizeof(Matrix_node_row));
            new_row->row = row_node_A->row;
            new_row->col = NULL;
            new_row->row_next = NULL;
            if (tmp->next == NULL)
            {
                tmp->next = new_row;
            }
            else
            {
                Matrix_node_row *tmp_row = tmp->next;
                while (tmp_row->row_next != NULL)
                {
                    tmp_row = tmp_row->row_next;
                }
                tmp_row->row_next = new_row;
            }
            Matrix_node_col *col_node = row_node_A->col;
            while (col_node != NULL)
            {
                insert_matrix(tmp, row_node_A->row, col_node->col, col_node->value);
                col_node = col_node->next;
            }
            row_node_A = row_node_A->row_next;
        }
        while(row_node_B && row_node_B->row<current_row){
            // insert row_node_B to tmp
            Matrix_node_row *new_row = (Matrix_node_row *)malloc(sizeof(Matrix_node_row));
            new_row->row = row_node_B->row;
            new_row->col = NULL;
            new_row->row_next = NULL;
            if (tmp->next == NULL)
            {
                tmp->next = new_row;
            }
            else
            {
                Matrix_node_row *tmp_row = tmp->next;
                while (tmp_row->row_next != NULL)
                {
                    tmp_row = tmp_row->row_next;
                }
                tmp_row->row_next = new_row;
            }
            Matrix_node_col *col_node = row_node_B->col;
            while (col_node != NULL)
            {
                insert_matrix(tmp, row_node_B->row, col_node->col, col_node->value);
                col_node = col_node->next;
            }
            row_node_B = row_node_B->row_next;
        }
        if(row_node_A && row_node_B && row_node_A->row==row_node_B->row){
            // add row_node_A and row_node_B to tmp
            Matrix_node_row *new_row = (Matrix_node_row *)malloc(sizeof(Matrix_node_row));
            new_row->row = row_node_A->row;
            new_row->col = NULL;
            new_row->row_next = NULL;
            if(tmp->next==NULL){
                tmp->next = new_row;
            }else{
                Matrix_node_row *tmp_row = tmp->next;
                while(tmp_row->row_next!=NULL){
                    tmp_row = tmp_row->row_next;
                }
                tmp_row->row_next = new_row;
            }
            Matrix_node_col *col_node_A = row_node_A->col;
            Matrix_node_col *col_node_B = row_node_B->col;
            while (col_node_A != NULL || col_node_B != NULL)
            {
                if(col_node_A && col_node_B && col_node_A->col==col_node_B->col){
                    insert_matrix(tmp, row_node_A->row, col_node_A->col, col_node_A->value+col_node_B->value);
                    col_node_A = col_node_A->next;
                    col_node_B = col_node_B->next;
                }else if(col_node_A && (!col_node_B || col_node_A->col<col_node_B->col)){
                    insert_matrix(tmp, row_node_A->row, col_node_A->col, col_node_A->value);
                    col_node_A = col_node_A->next;
                }else{
                    insert_matrix(tmp, row_node_B->row, col_node_B->col, col_node_B->value);
                    col_node_B = col_node_B->next;
                }
            }
            row_node_A = row_node_A->row_next;
            row_node_B = row_node_B->row_next;
        }
        
    }
    return tmp;
}

int main()
{
    int col, row;
    scanf("%d %d", &row, &col);
    int MatA_n, MatB_n;
    scanf("%d %d", &MatA_n, &MatB_n);
    Matrix *matrix_A = create_matrix(row, col);
    Matrix *matrix_B = create_matrix(row, col);
    while (MatA_n--)
    {
        int r, c, v;
        scanf("%d %d %d", &r, &c, &v);
        if (r == 0 && c == 0 && v == 0)
            break;
        insert_matrix(matrix_A, r, c, v);
    }
    while (MatB_n--)
    {
        int r, c, v;
        scanf("%d %d %d", &r, &c, &v);
        if (r == 0 && c == 0 && v == 0)
            break;
        insert_matrix(matrix_B, r, c, v);
    }
    Matrix *matrix_C = add_matrix(matrix_A, matrix_B);
    if (matrix_C == NULL)
    {
        printf("ERROR\n");
    }
    else
    {
        Matrix_node_row *row_node = matrix_C->next;
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
    }
    free_matrix(matrix_A);
    free_matrix(matrix_B);
    free_matrix(matrix_C);
    return 0;
}
