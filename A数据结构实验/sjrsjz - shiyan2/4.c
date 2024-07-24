#include <stdio.h>
#include <stdlib.h>

typedef struct MatrixNode
{
    int row;
    int col;
    int value;
    struct MatrixNode *right;
    struct MatrixNode *down;
} MatrixNode;

typedef struct
{
    int rows;
    int cols;
    MatrixNode **rowHeads;
    MatrixNode **colHeads;
} Matrix;

Matrix *create_matrix(int rows, int cols)
{
    Matrix *matrix = (Matrix *)malloc(sizeof(Matrix));
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->rowHeads = (MatrixNode **)malloc(rows * sizeof(MatrixNode *));
    matrix->colHeads = (MatrixNode **)malloc(cols * sizeof(MatrixNode *));
    while(rows--){
        matrix->rowHeads[rows] = NULL;
    }
    while(cols--){
        matrix->colHeads[cols] = NULL;
    }
    return matrix;
}

void free_matrix(Matrix *matrix)
{
    for (int i = 0; i < matrix->rows; i++)
    {
        MatrixNode *node = matrix->rowHeads[i];
        while (node != NULL)
        {
            MatrixNode *tmp = node;
            node = node->right;
            free(tmp);
        }
    }
    free(matrix->rowHeads);
    free(matrix->colHeads);
    free(matrix);
}

void insert_node(Matrix *matrix, int row, int col, int value)
{
    MatrixNode *new_node = (MatrixNode *)malloc(sizeof(MatrixNode));
    new_node->row = row;
    new_node->col = col;
    new_node->value = value;

    // Insert into row
    MatrixNode *row_node = matrix->rowHeads[row];
    MatrixNode *prev_row = NULL;
    while (row_node != NULL && row_node->col < col)
    {
        prev_row = row_node;
        row_node = row_node->right;
    }
    if (row_node != NULL && row_node->col == col)
    {
        row_node->value = value;
    }
    else
    {
        new_node->right = row_node;
        if (prev_row == NULL)
        {
            matrix->rowHeads[row] = new_node;
        }
        else
        {
            prev_row->right = new_node;
        }
    }

    // Insert into col
    MatrixNode *col_node = matrix->colHeads[col];
    MatrixNode *prev_col = NULL;
    while (col_node != NULL && col_node->row < row)
    {
        prev_col = col_node;
        col_node = col_node->down;
    }
    new_node->down = col_node;
    if (prev_col == NULL)
    {
        matrix->colHeads[col] = new_node;
    }
    else
    {
        prev_col->down = new_node;
    }   
}

Matrix* multiply_matrices(Matrix *matrix1, Matrix *matrix2)
{
    if (matrix1->cols != matrix2->rows)
    {
        return NULL;
    }

    Matrix *result = create_matrix(matrix1->rows, matrix2->cols);
    for (int i = 0; i < matrix1->rows; i++)
    {
        for (int j = 0; j < matrix2->cols; j++)
        {
            int sum = 0;
            MatrixNode *node1 = matrix1->rowHeads[i];
            MatrixNode *node2 = matrix2->colHeads[j];
            while (node1 != NULL && node2 != NULL)
            {
                if (node1->col < node2->row)
                {
                    node1 = node1->right;
                }
                else if (node1->col > node2->row)
                {
                    node2 = node2->down;
                }
                else
                {
                    sum += node1->value * node2->value;
                    node1 = node1->right;
                    node2 = node2->down;
                }
            }
            if (sum != 0)
            {
                insert_node(result, i, j, sum);
            }
        }
    }
    return result;
}

int main(){
    int rows1, cols1, rows2, cols2;
    scanf("%d %d", &rows1, &cols1);

    Matrix *matrix1 = create_matrix(rows1, cols1);

    while(1){
        int row, col, value;
        scanf("%d %d %d", &row, &col, &value);
        if(row==0 && col==0 && value==0) break;
        insert_node(matrix1, row - 1, col - 1, value);
    }

    scanf("%d %d", &rows2, &cols2);
    Matrix *matrix2 = create_matrix(rows2, cols2);

    while(1){
        int row, col, value;
        scanf("%d %d %d", &row, &col, &value);
        if(row==0 && col==0 && value==0) break;
        insert_node(matrix2, row - 1, col - 1, value);
    }


    Matrix *result = multiply_matrices(matrix1, matrix2);
    if (result == NULL)
    {
        printf("Error: Invalid dimensions\n");
    }
    else
    {
        for (int i = 0; i < result->rows; i++)
        {
            MatrixNode *node = result->rowHeads[i];
            while (node != NULL)
            {
                printf("%d %d %d\n", node->row + 1, node->col + 1, node->value);
                node = node->right;
            }
        }
    }

    free_matrix(matrix1);
    free_matrix(matrix2);
    free_matrix(result);

    return 0;

}