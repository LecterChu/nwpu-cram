#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Sample Input
    4 4
    1 1 1
    2 1 2
    3 2 3
    0?0?0
 * Sample Output
    1 1 1
    1 2 2
    2 3 3
 */

// 定义一个结构体CLNode，用来表示十字链表的节点
typedef struct CLNode {
    int i, j;                       // 节点所在的行号和列号
    int val;                        // 节点所存储的值
    struct CLNode *right, *down;    // 节点的右指针和下指针
} *Node; // 给结构体起一个别名Node

// 定义一个结构体CrossList，用来表示十字链表
typedef struct CrossList {
    Node *rHead, *cHead;    // 十字链表的行头指针数组和列头指针数组
    int rSize, cSize;       // 十字链表的行数和列数
} *List; // 给结构体起一个别名List

// 创建一个新节点，并初始化其右指针和下指针为NULL
Node createNode() {
    Node node = (Node) malloc(sizeof(struct CLNode));  // 动态分配内存空间
    node->right = node->down = NULL;                        // 初始化右指针和下指针为NULL
    return node;                                            // 返回新节点
}

// 初始化一个十字链表，并为其分配内存空间
void initList(List list, int rSize, int cSize) {
    list->rSize = rSize; // 设置十字链表的行数
    list->cSize = cSize; // 设置十字链表的列数

    list->rHead = (Node *) malloc(sizeof(Node) * rSize); // 为行头指针数组分配内存空间
    list->cHead = (Node *) malloc(sizeof(Node) * cSize); // 为列头指针数组分配内存空间
    for (int i = 0; i < rSize; ++i)
        list->rHead[i] = createNode(); // 为每一行创建一个头节点
    for (int i = 0; i < cSize; ++i)
        list->cHead[i] = createNode(); // 为每一列创建一个头节点
}

// 向十字链表中插入一个非零元素
void insertList(List list, int i, int j, int val) {
    Node newNode = (Node) malloc(sizeof(struct CLNode)); // 创建一个新节点
    newNode->i = i;     // 设置新节点的行号
    newNode->j = j;     // 设置新节点的列号
    newNode->val = val; // 设置新节点的值

    Node node;

    // 在水平方向上找到插入位置，并更新右指针
    node = list->rHead[i - 1];                                      // 从第i行的头节点开始遍历
    while (node->right && node->right->j < j) node = node->right;   // 找到第i行中第j列之前的最后一个节点
    newNode->right = node->right;                                   // 将新节点的右指针指向原来的下一个节点
    node->right = newNode;                                          // 将原来的节点的右指针指向新节点

    // 在垂直方向上找到插入位置，并更新下指针
    node = list->cHead[j - 1];                                      // 从第j列的头节点开始遍历
    while (node->down && node->down->i < i) node = node->down;      // 找到第j列中第i行之前的最后一个节点
    newNode->down = node->down;                                     // 将新节点的下指针指向原来的下一个节点
    node->down = newNode;                                           // 将原来的节点的下指针指向新节点
}

// 计算稀疏矩阵的转置，即交换其行和列，并将结果存储在另一个稀疏矩阵中
void Transpose(List list, List targetList) {

    // 初始化目标稀疏矩阵，交换行数和列数
    initList(targetList, list->cSize, list->rSize);

    // 遍历原稀疏矩阵的每一列
    for (int i = 0; i < list->cSize; ++i) {
        Node node = list->cHead[i]->down;
        // 遍历该列的每一个非零元素
        while (node) {
            // 将该元素插入到目标稀疏矩阵中，交换其行号和列号
            insertList(targetList, node->j, node->i, node->val);
            node = node->down;
        }
    }
}

// 打印稀疏矩阵的非零元素，按行号和列号的顺序输出
void printList(List list) {
    for (int i = 0; i < list->rSize; ++i) {
        Node node = list->rHead[i]->right;
        while (node) {
            printf("%d %d %d\n", node->i, node->j, node->val);
            node = node->right;
        }
    }
}

// 主函数，从标准输入读取稀疏矩阵的行数、列数和非零元素，创建一个稀疏矩阵，并计算其转置，然后打印转置后的稀疏矩阵
int main() {

    // 读取稀疏矩阵的行数和列数
    int rSize, cSize;
    scanf("%d %d", &rSize, &cSize);

    // 创建一个空的稀疏矩阵，并初始化
    struct CrossList list;
    initList(&list, rSize, cSize);

    // 读取稀疏矩阵的非零元素，并插入到稀疏矩阵中
    int i, j, val;
    while (scanf("%d %d %d", &i, &j, &val)) {
        if (i == 0) break;
        insertList(&list, i, j, val);
    }

    // 创建一个空的目标稀疏矩阵，并计算原稀疏矩阵的转置
    struct CrossList targetList;
    Transpose(&list, &targetList);

    // 打印目标稀疏矩阵的非零元素
    printList(&targetList);

    return 0;
}