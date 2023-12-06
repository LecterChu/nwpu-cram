#include <stdio.h>
#include <stdlib.h>

/*
 * Sample Input
    5
 * Sample Output
    3.14159
 */

typedef int E;

// 定义双链表，用于储存大数
typedef struct DListNode {
    E element;
    struct DListNode *next;
    struct DListNode *prev;
} *Node;

// 初始化链表，使其头尾相接
void initList(Node head) {
    head->element = '\0';
    head->prev = head->next = head;
}

// 在链表尾部插入节点
void insertList(Node head, E element) {
    if (!head) return;
    Node node = (Node) malloc(sizeof(struct DListNode));
    node->element = element;

    node->prev = head->prev;        // 新节点的前驱节点为尾端节点
    node->next = head->prev->next;  // 新节点的后继节点为尾端节点的后继节点（头节点）
    head->prev->next = node;        // 链表尾端节点改为新节点
    head->prev = node;              // 头节点的前驱节点改为新节点
}

// 删除链表，释放链表占用的空间
void freeList(Node head) {
    Node node = head->next, tmp;
    // 依次释放节点空间
    while (node != head) {
        tmp = node;
        node = node->next;
        free(tmp);
    }
    head->next = head->prev = head;
}

// 大数加2（PI专用）
void AddTwo(Node head) {
    head->next->element += 2; // 个位数加2
}

// 大数乘法（整型）
void Mul(Node head, int factor) {
    // 从链表尾端开始
    Node node = head->prev;
    int tmp = 0;
    // 将每一位数乘以 因数factor 加到tmp中
    // 再取tmp的个位存入这个数位
    // 最后将tmp除10（进位），并迭代
    while (node != head) {
        tmp += node->element * factor;
        node->element = tmp % 10;
        tmp /= 10;
        node = node->prev;
    }
}

// 大数除法（整型） // 与乘法类似
void Div(Node head, int denominator) {
    // 从链表头部开始
    Node node = head->next;
    int rest = 0, tmp;
    // 将 余数rest 乘10，和 数位上的数，加到tmp中
    // 再令 余数rest 等于tmp模分母/除数
    // 最后将tmp整除分母存入数位中，迭代
    while (node != head) {
        tmp = rest * 10 + node->element;
        rest = tmp % denominator;
        node->element = tmp / denominator;
        node = node->next;
    }
}

// 以10为底取对数
// （获取大数整数部分的位数，如：二位数(如16)则返回1，三位数返回2 ...）
int logOfTen(Node NaturalHead) {
    int i = 0;
    while (1) {
        // 分割线以内为判断大数是否小于10
        // ---------------------

        // 定义节点node为大数的倒数第6位（十位）
        Node node = NaturalHead->prev->prev->prev->prev->prev->prev;
        int is_less_than_ten = 1; // 1为真，0为假
        // 若十位即以上的数位的数均为0，则判断大数小于10
        // 否则将 小于10 的标记置为0（假），并break
        while (node != NaturalHead) {
            if (node->element) {
                is_less_than_ten = 0;
                break;
            }
            node = node->prev;
        }
        if (is_less_than_ten) break;
        // ---------------------

        // 若大数不小于10，则将大数除10，并继续循环
        i++;
        Div(NaturalHead, 10);
    }

    // 将被除了i次10的大数复位（乘回i次10）
    for (int j = 0; j < i; ++j)
        Mul(NaturalHead, 10);
    return i;
}

// 输入精度n，并返回（计算PI所需的）项数NumOfTerms
int getNumOfTerms(int n) {
// // 原算法因耗时太久（导致TE）被弃用
// // 分割线之内为原算法
// // -----------------

//    // 声明一个大数乘积
//    // （最后4位为小数位，整数位数为 精度n + 5(增大5精度) + 5(预留)，共n + 14位）
//    struct DListNode productHead;
//    initList(&productHead);
//    for (int i = 0; i < n + 4 + 5 + 5; ++i)
//        insertList(&productHead, 0);
//    // 将个位（倒数第5位）置为1
//    productHead.prev->prev->prev->prev->prev->element = 1;
//
//    // 从i = 1开始循环
//    // 每轮循环将 大数乘积 乘2 * i + 1，再除i，并i++
//    // 当 大数乘积（以10为底）的对数 - 5(增大的精度) 大于 精度n 时，停止循环
//    int i = 1;
//    while (logOfTen(&productHead) - 5 < n) {
//        Mul(&productHead, 2 * i + 1);
//        Div(&productHead, i);
// //     printf("%d\n", i); // (用于调试)
//        i++;
//    }
//    // 清空大数乘积，并释放空间
//    freeList(&productHead);
//    return i; // 返回项数i

// // -----------------

    // 用一次函数代替原算法求项数，从而节省时间
    // 原算法:
    //      输入 1   --- 输出 20
    //      输入 2   --- 输出 80
    //      输入 250 --- 输出 800
    //      输入 500 --- 输出 1550
    // 故用 4 * n + 50 近似取代原算法，
    // 将时间复杂度降为常数阶
    // （虽然一定程度上会增大计算PI值的耗时，
    //   但在 求项数 的步骤中节省了大量的运算，利大于弊）
    return 4 * n + 50;
}

// 计算PI值
void calculatePI(Node head, int numOfTerms) {
    // 迭代k次 PI = PI * (2 * k + 1) / k + 2
    int k = numOfTerms;
    while (k > 0) {
        Div(head, 2 * k + 1);
        Mul(head, k);
        AddTwo(head);
        k--;
    }
}

// 输出PI
void printPI(Node head, int numOfDigits) {
    Node node = head->next;
    // 个位及小数点输出
    printf("%d.", node->element);
    node = node->next;
    // 小数部分的输出，共输出 numOfDigits 次
    while (node != head && numOfDigits > 0) {
        printf("%d", node->element);
        node = node->next;
        numOfDigits--;
    }
}

int main() {
    // 创建一个双链表头节点，并初始化
    struct DListNode PI_head;
    initList(&PI_head);

    // 输入精度
    int numOfDigits;
    scanf("%d", &numOfDigits);

    // 给双链表插入 numsOfDigits 个节点，并将个位（第一个节点）置为1
    for (int i = 0; i < numOfDigits + 1 + 5; ++i)
        insertList(&PI_head, 0);
    PI_head.next->element = 1;

    // 计算 计算PI值 所需的项数
    int numOfTerms = getNumOfTerms(numOfDigits);

    // 计算PI值，并将其输出
    calculatePI(&PI_head, numOfTerms);
    printPI(&PI_head, numOfDigits);
}