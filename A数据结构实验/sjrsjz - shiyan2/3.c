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
} CrossList;

CrossList *create_cross_list(int rows, int cols)
{
    CrossList *list = (CrossList *)malloc(sizeof(CrossList));
    list->rows = rows;
    list->cols = cols;
    list->rowHeads = (MatrixNode **)calloc(rows, sizeof(MatrixNode *));
    list->colHeads = (MatrixNode **)calloc(cols, sizeof(MatrixNode *));
    return list;
}

void free_cross_list(CrossList *list)
{
    for (int i = 0; i < list->rows; i++)
    {
        MatrixNode *node = list->rowHeads[i];
        while (node != NULL)
        {
            MatrixNode *tmp = node;
            node = node->right;
            free(tmp);
        }
    }
    free(list->rowHeads);
    free(list->colHeads);
    free(list);
}

void insert_node(CrossList *list, int row, int col, int value)
{
    MatrixNode *new_node = (MatrixNode *)malloc(sizeof(MatrixNode));
    new_node->row = row;
    new_node->col = col;
    new_node->value = value;

    // Insert into row
    MatrixNode *row_node = list->rowHeads[row];
    MatrixNode *prev_row = NULL;
    while (row_node != NULL && row_node->col < col)
    {
        prev_row = row_node;
        row_node = row_node->right;
    }
    new_node->right = row_node;
    if (prev_row == NULL)
    {
        list->rowHeads[row] = new_node;
    }
    else
    {
        prev_row->right = new_node;
    }

    // Insert into column
    MatrixNode *col_node = list->colHeads[col];
    MatrixNode *prev_col = NULL;
    while (col_node != NULL && col_node->row < row)
    {
        prev_col = col_node;
        col_node = col_node->down;
    }
    new_node->down = col_node;
    if (prev_col == NULL)
    {
        list->colHeads[col] = new_node;
    }
    else
    {
        prev_col->down = new_node;
    }
}

void add_matrix(CrossList *list1, CrossList *list2, CrossList *result)
{
    for (int i = 0; i < list1->rows; i++)
    {
        MatrixNode *node1 = list1->rowHeads[i];
        MatrixNode *node2 = list2->rowHeads[i];
        while (node1 != NULL && node2 != NULL)
        {
            if (node1->col < node2->col)
            {
                insert_node(result, i, node1->col, node1->value);
                node1 = node1->right;
            }
            else if (node1->col > node2->col)
            {
                insert_node(result, i, node2->col, node2->value);
                node2 = node2->right;
            }
            else
            {
                int value = node1->value + node2->value;
                if (value != 0)
                {
                    insert_node(result, i, node1->col, value);
                }
                node1 = node1->right;
                node2 = node2->right;
            }
        }
        while (node1 != NULL)
        {
            insert_node(result, i, node1->col, node1->value);
            node1 = node1->right;
        }
        while (node2 != NULL)
        {
            insert_node(result, i, node2->col, node2->value);
            node2 = node2->right;
        }
    }
}

int main()
{
    int col, row;
    scanf("%d %d", &row, &col);
    int MatA_n, MatB_n;
    scanf("%d %d", &MatA_n, &MatB_n);
    CrossList *matrix_A = create_cross_list(row, col);
    CrossList *matrix_B = create_cross_list(row, col);
    while (MatA_n--)
    {
        int r, c, v;
        scanf("%d %d %d", &r, &c, &v);
        if (r == 0 && c == 0 && v == 0)
            break;
        insert_node(matrix_A, r, c, v);
    }
    while (MatB_n--)
    {
        int r, c, v;
        scanf("%d %d %d", &r, &c, &v);
        if (r == 0 && c == 0 && v == 0)
            break;
        insert_node(matrix_B, r, c, v);
    }
    CrossList *matrix_C;
    add_matrix(matrix_A, matrix_B, matrix_C = create_cross_list(row, col));
    // print matrix
    for (int i = 0; i < matrix_C->rows; i++)
    {
        MatrixNode *node = matrix_C->rowHeads[i];
        while (node != NULL)
        {
            printf("%d %d %d\n", node->row, node->col, node->value);
            node = node->right;
        }
    }

    free_cross_list(matrix_A);
    free_cross_list(matrix_B);
    free_cross_list(matrix_C);
    return 0;
}
