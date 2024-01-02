#include <stdio.h>
#include <stdlib.h>

/*
 * Sample Input
    3 4 3 2
    1 1 1
    1 3 1
    2 2 2
    1 2 1
    2 2 3
 * Sample Output
    1 1 1
    1 2 1
    1 3 1
    2 2 5
 */

// 定义一个结构体，表示一个三元组，用来存储稀疏矩阵中的非零元素的行、列和值
typedef struct ThreeTuple {
    int i, j;
    int val;
} *Tuple;

// 定义一个结构体，表示一个三元组表，用来存储稀疏矩阵中的所有非零元素的三元组，以及表的容量和大小
typedef struct TupleTable {
    struct ThreeTuple *tuple;
    int cap;
    int size;
} *Table;

// 初始化一个三元组表，给定一个容量，分配相应的内存空间，并将表的大小设为0
void initTable(Table table, int capacity) {
    table->tuple = (struct ThreeTuple *) malloc(sizeof(struct ThreeTuple) * capacity);
    table->cap = capacity;
    table->size = 0;
}

// 向一个三元组表中插入一个三元组，给定行、列和值，并更新表的大小
void insertTable(Table table, int i, int j, int val) {
    table->tuple[table->size].i = i;
    table->tuple[table->size].j = j;
    table->tuple[table->size].val = val;

    table->size++;
}

// 将两个三元组表表示的稀疏矩阵相加，结果存储在另一个三元组表中，按照行、列的顺序合并相同位置的元素，并过滤掉值为0的元素
void addTwoTable(Table A, Table B, Table result) {
    int index_a = 0, index_b = 0;
    while (index_a < A->size && index_b < B->size) {
        if (A->tuple[index_a].i == B->tuple[index_b].i && A->tuple[index_a].j == B->tuple[index_b].j) {
            // 如果两个表中当前位置的元素行、列相同，则将它们的值相加，并判断是否为0，如果不为0，则插入到结果表中，并更新两个表的索引
            int sum = A->tuple[index_a].val + B->tuple[index_b].val;
            if (sum)
                insertTable(result, A->tuple[index_a].i, A->tuple[index_a].j, sum);
            index_a++;
            index_b++;
        } else if (A->tuple[index_a].i < B->tuple[index_b].i) {
            // 如果 A表中当前位置的元素行 小于 B表中当前位置的元素行，则将 A表中当前位置的元素 插入到结果表中，并更新A表的索引
            insertTable(result, A->tuple[index_a].i, A->tuple[index_a].j, A->tuple[index_a].val);
            index_a++;
        } else if (A->tuple[index_a].i > B->tuple[index_b].i) {
            // 如果 A表中当前位置的元素行 大于 B表中当前位置的元素行，则将 B表中当前位置的元素 插入到结果表中，并更新B表的索引
            insertTable(result, B->tuple[index_b].i, B->tuple[index_b].j, B->tuple[index_b].val);
            index_b++;
        } else if (A->tuple[index_a].j < B->tuple[index_b].j) {
            // 如果 A表中当前位置的元素列 小于 B表中当前位置的元素列，则将 A表中当前位置的元素 插入到结果表中，并更新A表的索引
            insertTable(result, A->tuple[index_a].i, A->tuple[index_a].j, A->tuple[index_a].val);
            index_a++;
        } else {
            // 如果 A表中当前位置的元素列 大于 B表中当前位置的元素列，则将 B表中当前位置的元素 插入到结果表中，并更新B表的索引
            insertTable(result, B->tuple[index_b].i, B->tuple[index_b].j, B->tuple[index_b].val);
            index_b++;
        }
    }

    // 如果A表还有剩余的元素，则将它们依次插入到结果表中
    while (index_a < A->size) {
        insertTable(result, A->tuple[index_a].i, A->tuple[index_a].j, A->tuple[index_a].val);
        index_a++;
    }
    // 如果B表还有剩余的元素，则将它们依次插入到结果表中
    while (index_b < B->size) {
        insertTable(result, B->tuple[index_b].i, B->tuple[index_b].j, B->tuple[index_b].val);
        index_b++;
    }
}

// 打印一个三元组表，按照行、列、值的顺序输出每个元素
void printTable(Table table) {
    for (int i = 0; i < table->size; ++i)
        printf("%d %d %d\n", table->tuple[i].i, table->tuple[i].j, table->tuple[i].val);
}

int main() {
    int rSize, cSize, t1, t2;
    struct TupleTable A, B, result;
    // 从标准输入读取两个稀疏矩阵的行数、列数、非零元素个数
    scanf("%d %d %d %d", &rSize, &cSize, &t1, &t2);
    // 初始化三个三元组表，分别表示两个稀疏矩阵和它们的和
    initTable(&A, t1);
    initTable(&B, t2);
    initTable(&result, t1 + t2);

    int i, j, val;
    // 从标准输入读取第一个稀疏矩阵的非零元素，并插入到对应的三元组表中
    for (int k = 0; k < t1; ++k) {
        scanf("%d %d %d", &i, &j, &val);
        insertTable(&A, i, j, val);
    }
    // 从标准输入读取第二个稀疏矩阵的非零元素，并插入到对应的三元组表中
    for (int k = 0; k < t2; ++k) {
        scanf("%d %d %d", &i, &j, &val);
        insertTable(&B, i, j, val);
    }

    // 调用函数，将两个三元组表相加，结果存储在第三个三元组表中
    addTwoTable(&A, &B, &result);
    // 打印第三个三元组表，即稀疏矩阵相加的结果
    printTable(&result);
}