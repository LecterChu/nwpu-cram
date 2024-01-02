#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAP 100     // 定义最大容量为100

/*
 * Sample Input
 *     5 a b c d e 12 40 15 8 25
 *     bbbaddeccbbb
 * Sample Output
 *     00011111110111010110110000
 *     bbbaddeccbbb
 *
 */

/*
*       null
*      /   \
*     b    null
*          /  \
*         e   null
*             /  \
*            c   null
*                /  \
*               d    a
*/

typedef char E;  // 定义字符类型E

typedef struct TreeNode { // 定义树节点结构体
    E element;              // 元素
    struct TreeNode *left;  // 左子节点
    struct TreeNode *right; // 右子节点
    int value;              // 字符出现次数
} *Node;

typedef Node T;	// 节点T

typedef struct ListNode { // 链表节点结构体
    T element;              // 元素
    struct ListNode *next;  // 下一个节点
} *LNode;

typedef struct Queue {  // 队列结构体
    LNode front, rear;   // 队首、队尾节点
} *LinkedQueue;

// 初始化队列
int initQueue(LinkedQueue queue) {
    LNode node = (LNode) malloc(sizeof(struct ListNode));  // 申请空间创建链表节点
    if (node == NULL) return 0;                                 // 申请空间失败则返回0
    queue->front = queue->rear = node;                          // 队首、队尾节点都指向该节点
    node->next = NULL;                                          // 该节点的下一个节点为空
    return 1;                                                   // 初始化成功返回1
}

// 入队操作
int offerQueue(LinkedQueue queue, T element) {
    LNode node = (LNode) malloc(sizeof(struct ListNode));  // 申请空间创建链表节点
    if (node == NULL) return 0;                                 // 申请空间失败则返回0
    node->element = element;                                    // 节点元素为element
    node->next = NULL;                                          // 节点的下一个节点为空

    LNode pre = queue->front;   // pre指向队首节点
    while (pre->next && pre->next->element->value <= element->value)  // 找到element应该插入的位置
        pre = pre->next;

    if (pre == queue->rear) {   // 如果pre指向队尾节点,则element入队成为新的队尾节点
        queue->rear->next = node;
        queue->rear = node;
    } else {                    // 否则,element入队到pre之后
        node->next = pre->next;
        pre->next = node;
    }
    return 1;   // 入队成功返回1
}

// 出队操作
T pollQueue(LinkedQueue queue) {
    T e = queue->front->next->element;                      // 取出元素e
    LNode node = queue->front->next;                        // node指向出队节点
    queue->front->next = queue->front->next->next;          // 出队
    if (queue->rear == node) queue->rear = queue->front;    // 如果出队的是队尾节点,则队尾指向队首节点
    free(node);                                     // 释放节点空间
    return e;                                               // 返回出队元素
}

// 创建树节点
Node createNode(E element, int value) {
    Node node = (Node) malloc(sizeof(struct TreeNode));    // 申请空间创建节点
    node->element = element;                                    // 节点元素
    node->left = node->right = NULL;                            // 左右子节点为空
    node->value = value;                                        // 字符出现次数
    return node;                                                // 返回创建的节点
}

// 构建哈夫曼树
Node buildHuffmanTree(LinkedQueue queue) {
    while (queue->front->next != queue->rear) {   // 队列中至少有1个节点(除了头节点)
        Node left = pollQueue(queue);   // 出队左子节点
        Node right = pollQueue(queue);  // 出队右子节点
        Node node = createNode(' ', left->value + right->value);   // 创建父节点,元素为空格,value为左右子节点value之和
        node->left = left;    // 左子节点
        node->right = right;  // 右子节点
        offerQueue(queue, node);   // 父节点入队
    }
    return pollQueue(queue);   // 返回根节点
}

// 编码
char *encode(Node root, E e) {
    if (root == NULL) return NULL;      // 空树则返回NULL
    if (root->element == e) return "";  // 找到叶子节点则返回空字符串

    char *str = encode(root->left, e);   // 利用左子树编码
    char s[10];
    if (str != NULL) {    // 左子树成功编码
        s[0] = '0';
        s[1] = '\0';
        str = strcat(s, str);       // 前缀0
    } else {              // 左子树编码失败
        str = encode(root->right, e);   // 利用右子树编码
        if (str != NULL) {
            s[0] = '1';
            s[1] = '\0';
            str = strcat(s, str);   // 前缀1
        }
    }
    return str;   // 返回编码结果
}

int Index = 0;

// 解码
void decode(Node root, char *code, int codeSize) {
    if (root->element != ' ') { // 如果当前节点是叶子节点，则输出元素值
        printf("%c", root->element);
        return;
    }

    if (Index == codeSize) return;
    if (code[Index++] == '0')
        decode(root->left, code, codeSize); // 如果编码为0，则在左子树中继续解码
    else
        decode(root->right, code, codeSize); // 如果编码为1，则在右子树中继续解码
}

int main() {
    struct Queue queue;
    initQueue(&queue);

    // 读入输入元素和权值
    int num;
    scanf("%d", &num);
    char elements[num];
    int values[num];
    char c;
    for (int i = 0; i < num; ++i)
        scanf("%c%c", &c, &elements[i]); // 注意这里要读入两个字符，第一个是空格或换行符，第二个才是元素值字符
    for (int i = 0; i < num; ++i)
        scanf("%d", &values[i]);

    // 将输入元素和权值构造成节点，并加入到队列中
    for (int i = 0; i < num; ++i)
        offerQueue(&queue, createNode(elements[i], values[i]));

    // 构建哈夫曼树
    Node root = buildHuffmanTree(&queue);

    // 读入待编码字符串
    scanf("%c", &c);
    char Input[CAP];
    scanf("%s", Input);

    // 对每个字符进行编码，并将编码字符串拼接起来
    char code[CAP] = "";
    for (int i = 0; i < strlen(Input); ++i)
        strcat(code, encode(root, Input[i]));
    printf("%s", code);

    printf("\n");
    Index = 0;
    int codeSize = strlen(code);
    while (Index != codeSize)
        decode(root, code, codeSize); // 解码
    printf("\n");
}