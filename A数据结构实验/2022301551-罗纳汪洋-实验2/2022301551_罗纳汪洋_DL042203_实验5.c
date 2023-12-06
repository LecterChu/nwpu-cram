#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Sample Input
    3?4?3?2
    1?1?1
    1?3?1
    2?2?2
    1?2?1
    2?2?3
 * Sample Output
    1?1?1
    1?2?1
    1?3?1
    2?2?5
 */

//定义一个结构体CLNode，用来表示十字链表的节点
typedef struct CLNode {
    int i, j;                       //节点所在的行号和列号
    int val;                        //节点所存储的值
    struct CLNode *right, *down;    //节点的右指针和下指针
} *Node; //给结构体起一个别名Node

//定义一个结构体CrossList，用来表示十字链表
typedef struct CrossList {
    Node *rHead, *cHead;    //十字链表的行头指针数组和列头指针数组
    int rSize, cSize;       //十字链表的行数和列数
} *List; //给结构体起一个别名List

//创建一个新节点，并初始化其右指针和下指针为NULL
Node createNode() {
    Node node = (Node) malloc(sizeof(struct CLNode));  //动态分配内存空间
    node->right = node->down = NULL;                        //初始化右指针和下指针为NULL
    return node;                                            //返回新节点
}

//初始化一个十字链表，并为其分配内存空间
void initList(List list, int rSize, int cSize) {
    list->rSize = rSize; //设置十字链表的行数
    list->cSize = cSize; //设置十字链表的列数

    list->rHead = (Node *) malloc(sizeof(Node) * rSize); //为行头指针数组分配内存空间
    list->cHead = (Node *) malloc(sizeof(Node) * cSize); //为列头指针数组分配内存空间
    for (int i = 0; i < rSize; ++i)
        list->rHead[i] = createNode(); //为每一行创建一个头节点
    for (int i = 0; i < cSize; ++i)
        list->cHead[i] = createNode(); //为每一列创建一个头节点
}

//向十字链表中插入一个非零元素
void insertList(List list, int i, int j, int val) {
    Node newNode = (Node) malloc(sizeof(struct CLNode)); //创建一个新节点
    newNode->i = i;     //设置新节点的行号
    newNode->j = j;     //设置新节点的列号
    newNode->val = val; //设置新节点的值

    Node node;

    // 在水平方向上找到插入位置，并更新右指针
    node = list->rHead[i - 1];                                      //从第i行的头节点开始遍历
    while (node->right && node->right->j < j) node = node->right;   //找到第i行中第j列之前的最后一个节点
    newNode->right = node->right;                                   //将新节点的右指针指向原来的下一个节点
    node->right = newNode;                                          //将原来的节点的右指针指向新节点

    // 在垂直方向上找到插入位置，并更新下指针
    node = list->cHead[j - 1];                                      //从第j列的头节点开始遍历
    while (node->down && node->down->i < i) node = node->down;      //找到第j列中第i行之前的最后一个节点
    newNode->down = node->down;                                     //将新节点的下指针指向原来的下一个节点
    node->down = newNode;                                           //将原来的节点的下指针指向新节点
}

//实现两个十字链表（稀疏矩阵）的加法，并将结果存储在另一个十字链表中
void addTwoList(List A, List B, List result) {
    for (int i = 0; i < A->rSize; ++i) {    //遍历每一行
        Node node_A = A->rHead[i]->right;   //取出A矩阵第i行的第一个非零元素
        Node node_B = B->rHead[i]->right;   //取出B矩阵第i行的第一个非零元素

        while (node_A && node_B) { //当两个矩阵都有非零元素时
            if (node_A->j == node_B->j) {       //如果两个元素在同一列
                int sum = node_A->val + node_B->val;    //计算两个元素的和
                if (sum != 0)                           //如果和不为0，将和插入到结果矩阵中
                    insertList(result, node_A->i, node_A->j, sum);
                node_A = node_A->right;                 //A矩阵指向下一个非零元素
                node_B = node_B->right;                 //B矩阵指向下一个非零元素
            } else if (node_A->j < node_B->j) { //如果A矩阵的元素在B矩阵的元素之前
                insertList(result, node_A->i, node_A->j, node_A->val);  //将A矩阵的元素插入到结果矩阵中
                node_A = node_A->right;                                     //A矩阵指向下一个非零元素
            } else {                            //如果B矩阵的元素在A矩阵的元素之前
                insertList(result, node_B->i, node_B->j, node_B->val);  //将B矩阵的元素插入到结果矩阵中
                node_B = node_B->right;                                     //B矩阵指向下一个非零元素
            }
        }

        //如果A或B矩阵还有剩余的非零元素，将剩余的元素插入到结果矩阵中
        while (node_A) {
            insertList(result, node_A->i, node_A->j, node_A->val);
            node_A = node_A->right;
        }
        while (node_B) {
            insertList(result, node_B->i, node_B->j, node_B->val);
            node_B = node_B->right;
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

//主函数
int main() {
    int rSize, cSize, t1, t2;
    scanf("%d?%d?%d?%d", &rSize, &cSize, &t1, &t2);

    struct CrossList A, B, result;      // 定义三个 CrossList 结构体，分别表示两个稀疏矩阵 A 和 B 以及它们的和 result
    initList(&A, rSize, cSize);         // 初始化 A 矩阵
    initList(&B, rSize, cSize);         // 初始化 B 矩阵
    initList(&result, rSize, cSize);    // 初始化 result 矩阵

    // 将输入的非零元素分别插入到 A B 矩阵中
    int i, j, val;
    for (int k = 0; k < t1; ++k) {
        scanf("%d?%d?%d", &i, &j, &val);
        insertList(&A, i, j, val);
    }
    for (int k = 0; k < t2; ++k) {
        scanf("%d?%d?%d", &i, &j, &val);
        insertList(&B, i, j, val);
    }

    // 调用函数，将 A 和 B 矩阵相加，得到 result 矩阵
    addTwoList(&A, &B, &result);
    // 调用函数，打印 result 矩阵
    printList(&result);

    return 0;
}