#include <stdio.h>
#include <stdlib.h>

/*
 * Sample Input
    3?3
    1?1?1
    2?2?2
    2?3?4
    3?1?-4
    0?0?0
    3?3
    1?3?-2
    2?3?-5
    3?1?8
    3?2?-6
    0?0?0
 * Sample Output
    1?3?-2
    2?1?32
    2?2?-24
    2?3?-10
    3?3?8
 */

// 定义一个结构体，表示一个三元组，用来存储稀疏矩阵中的非零元素及其位置
typedef struct ThreeTuple {
    int i, j;                   // 行号和列号
    int val;                    // 元素值
    struct ThreeTuple *next;    // 指向下一个三元组的指针
} *Tuple;

// 定义一个结构体，表示一个三元组表，用来存储稀疏矩阵的信息
typedef struct TupleTable {
    struct ThreeTuple *head;    // 指向表头结点的指针，表头结点不存储数据，只用于连接其他结点
    int rSize, cSize;           // 矩阵的行数和列数
    int size;                   // 矩阵中非零元素的个数
} *Table;

// 初始化一个三元组表，分配内存空间，并将表头结点的指针设为NULL，非零元素个数设为0
void initTable(Table table) {
    table->head = (Tuple) malloc(sizeof(struct ThreeTuple));
    table->head->next = NULL;
    table->size = 0;
}

// 向一个三元组表中插入一个新的三元组，将其放在表尾，并更新非零元素个数
void insertTable(Table table, int i, int j, int val) {
    Tuple newTuple = (Tuple) malloc(sizeof(struct ThreeTuple));
    newTuple->i = i;
    newTuple->j = j;
    newTuple->val = val;
    newTuple->next = NULL;

    Tuple tuple = table->head;
    while (tuple->next)
        tuple = tuple->next;
    tuple->next = newTuple;

    table->size++;
}

// 计算两个稀疏矩阵（三元组表）的乘积，并将结果存储在另一个三元组表中
void mulTwoTable(Table A, Table B, Table result) {
    // 初始化结果表，并将结果表的：
    //    行数设置为 A 表的行数，
    //    列数设置为 B 表的列数
    initTable(result);
    result->rSize = A->rSize;
    result->cSize = B->cSize;

    // 设置一个指针指向 A 表的第一个元素
    Tuple flag = A->head->next;
    // 遍历 A 表的每一行
    for (int i = 1; i <= A->rSize; ++i) {
        // 设置一个指针指向当前行的第一个元素
        Tuple tuple_A = flag;
        // 在当前行内，遍历每个元素
        while (tuple_A->i == i) {
            // 创建一个临时数组，用于存储当前行与 B 表每一列的乘积
            // 并初始化临时数组为 0
            int tmp[B->cSize];
            for (int j = 0; j < B->cSize; ++j)
                tmp[j] = 0;

            // 设置一个指针指向 B 表的第一个元素
            Tuple tuple_B = B->head->next;
            // 遍历 B 表的每个元素
            while (tuple_B) {
                // 如果 A 表已经遍历完当前行，即 当前元素的行号大于当前行号，跳出循环
                if (tuple_A == NULL || tuple_A->i > i) break;

                // 如果 B 表当前元素的行号等于 A 表当前元素的列号，说明可以相乘
                if (tuple_B->i == tuple_A->j)
                    // 将相乘的结果累加到临时数组对应的位置上
                    tmp[tuple_B->j - 1] += tuple_A->val * tuple_B->val;
                // 如果 B 表当前元素的行号大于 A 表当前元素的列号，说明需要移动 A 表的指针到下一个元素，
                // 并继续循环（即不移动 B 表的指针）
                else if (tuple_B->i > tuple_A->j) {
                    tuple_A = tuple_A->next;
                    continue;
                }

                // 移动 B 表的指针到下一个元素
                tuple_B = tuple_B->next;
            }

            // 遍历临时数组，将不为 0 的值插入到结果表中
            for (int j = 0; j < B->cSize; ++j) {
                if (tmp[j] != 0)
                    insertTable(result, i, j + 1, tmp[j]);
            }

            // 移动 A 表的指针到下一行的第一个元素
            while (tuple_A && tuple_A->i == i) {
                tuple_A = tuple_A->next;
            }

            // 如果 A 表已经遍历完所有元素，退出函数
            if (tuple_A == NULL) return;

            // 更新标志指针为 A 表当前指针
            flag = tuple_A;
        }
    }
}

// 打印一个三元组表，按照三元组的格式输出每个非零元素及其位置
void printTable(Table table) {
    Tuple tuple = table->head->next;
    while (tuple) {
        printf("%d?%d?%d\n", tuple->i, tuple->j, tuple->val);
        tuple = tuple->next;
    }
}

// 主函数
int main() {
    // 定义一个三元组表 A，并初始化
    struct TupleTable A;
    initTable(&A);
    // 从标准输入读取 A 的行数和列数
    scanf("%d?%d", &A.rSize, &A.cSize);

    // 循环读取 A 的每个元素的行号、列号和值，直到遇到 0 0 结束
    int i, j, val;
    while (1) {
        scanf("%d?%d?%d", &i, &j, &val);
        if (i == 0 && j == 0) break;
        // 将读取到的元素插入到 A 中
        insertTable(&A, i, j, val);
    }

    // 定义一个三元组表 B，并初始化
    struct TupleTable B;
    initTable(&B);
    // 从标准输入读取 B 的行数和列数
    scanf("%d?%d", &B.rSize, &B.cSize);

    // 循环读取 B 的每个元素的行号、列号和值，直到遇到 0 0 结束
    while (1) {
        scanf("%d?%d?%d", &i, &j, &val);
        if (i == 0 && j == 0) break;
        // 将读取到的元素插入到 B 中
        insertTable(&B, i, j, val);
    }

    // 定义一个三元组表 result，用于存储 A 和 B 的乘积
    struct TupleTable result;
    // 调用上面定义的函数，计算 A 和 B 的乘积，并将结果存储在 result 中
    mulTwoTable(&A, &B, &result);
    // 打印 result 表的内容
    printTable(&result);
}