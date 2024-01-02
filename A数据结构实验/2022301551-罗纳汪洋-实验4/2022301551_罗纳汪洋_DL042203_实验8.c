#include <stdio.h>
#include <stdlib.h>

#define INF 10000 // 定义一个最大值

/*
 * Sample Input
    6
    0 1 4 10000 10000 10000
    1 0 2 7 5 10000
    4 2 0 10000 1 10000
    10000 7 10000 0 3 2
    10000 5 1 3 0 6
    10000 10000 10000 2 6 0
 * Sample Output
    0
    1
    3
    7
    4
    9
 */

typedef struct MatrixGraph { // 定义邻接矩阵图结构体
    int vertexCount;    // 图的节点数
    int **matrix;       // 存储图的邻接矩阵
} *Graph;

typedef struct QueueNode { // 定义优先队列的节点结构体
    int vertex;                     // 当前节点的编号
    int dist;                       // 当前节点到源节点的距离
    int path;                       // 当前节点的前驱节点
    struct QueueNode *prev, *next;  // 前继节点和后继节点指针
} *QNode;

typedef struct LinkedQueue { // 定义优先队列结构体
    struct QueueNode *front, *rear; // 队头和队尾指针
} *Queue;

void initQueue(Queue queue) { // 初始化优先队列
    QNode node = (QNode) malloc(sizeof(struct QueueNode)); // 创建一个空节点
    node->dist = 0;                     // 节点到源节点的距离为0
    node->next = node->prev = NULL;     // 节点的前继节点和后继节点均为空
    queue->front = queue->rear = node;  // 队头和队尾指针均指向这个空节点
}

void offerQueue(Queue queue, int vertex, int dist, int path) { // 将节点加入优先队列
    QNode newNode = (QNode) malloc(sizeof(struct QueueNode)); // 创建一个新节点
    newNode->vertex = vertex;               // 节点的编号为vertex
    newNode->dist = dist;                   // 节点到源节点的距离为dist
    newNode->path = path;                   // 节点最短路径的前一个节点编号为path
    newNode->next = newNode->prev = NULL;   // 节点的前继节点和后继节点均初始化为空

    QNode node = queue->front; // 从队头开始遍历
    while (node->next && node->next->dist < dist) // 找到第一个到源节点距离比当前节点小的节点
        node = node->next;

    // 将新节点插入到它之前
    if (node->next) // 判断该节点是否是最后一个节点
        node->next->prev = newNode;
    newNode->next = node->next;
    node->next = newNode;
    newNode->prev = node;
    if (!newNode->next)
        queue->rear = newNode;
}

QNode pollQueue(Queue queue) { // 从优先队列中取出节点
    QNode node = queue->front->next;            // 取出队头的后继节点
    if (node->next)
        node->next->prev = queue->front;        // （若不是队尾节点）将它后继节点的前继指针改为队头
    else
        queue->rear = queue->front;
    queue->front->next = node->next;            // 将队头的后继节点改为它的后继节点

    node->next = node->prev = NULL;             // 将它的前继指针和后继指针均为空
    return node; // 返回取出的节点
}

Graph createGraph(int vertexCount) { // 创建邻接矩阵图
    Graph graph = (Graph) malloc(sizeof(struct MatrixGraph));       // 创建一个图结构体
    graph->vertexCount = vertexCount;                               // 节点数为vertexCount
    graph->matrix = (int **) malloc(sizeof(int *) * vertexCount);   // 为存储邻接矩阵分配空间
    for (int i = 0; i < vertexCount; ++i)
        graph->matrix[i] = (int *) malloc(sizeof(int) * vertexCount); // 为每一行分配空间
    return graph; // 返回创建的图结构体
}

int *dijkstra(Graph graph) { // 执行迪杰斯特拉算法
    struct LinkedQueue leftVertex;  // 定义优先队列
    initQueue(&leftVertex);         // 初始化优先队列

    int *shortestDist = (int *) malloc(sizeof(int) * (graph->vertexCount - 1)); // 存储每个节点到源节点的最短距离

    for (int i = 1; i < graph->vertexCount; ++i) // 将除源节点外的所有节点加入优先队列
        offerQueue(&leftVertex, i, graph->matrix[0][i], 0);

    for (int i = 0; i < graph->vertexCount - 1; ++i) {      // 对于剩下的所有节点
        QNode vertex = pollQueue(&leftVertex);              // 从优先队列中取出到源节点距离最小的节点
        shortestDist[vertex->vertex - 1] = vertex->dist;    // 将它到源节点的距离存储到数组中

        QNode node = leftVertex.front->next; // 从优先队列中读取下一个节点
        while (node) { // 对于剩下的所有节点
            QNode nextNode = node->next; // 记录该节点的后继节点，用于循环迭代

            int newDist = vertex->dist + graph->matrix[vertex->vertex][node->vertex]; // 计算从源节点到当前节点的距离
            if (newDist < node->dist) { // 如果新的距离更小
                node->dist = newDist;           // 更新节点到源节点的距离
                node->path = vertex->vertex;    // 更新当前节点的前驱节点

                if (node->dist < node->prev->dist) { // 如果当前节点到源节点的距离比它的前驱节点更小（需要更新优先队列）
                    if (node->next) // 如果当前节点存在后继节点（不是最后一个节点）
                        node->next->prev = node->prev;  // 将node的后继节点的前继节点指向node的前继节点
                    else
                        leftVertex.rear = node->prev;   // 如果当前节点没有后继节点，将队尾指针指向node的前继节点
                    node->prev->next = node->next;      // 将node的前继节点的后继节点指向node的后继节点

                    QNode tmp = node->prev; // 从node的前继节点开始向前遍历
                    while (tmp->prev->dist > node->dist)
                        tmp = tmp->prev; // 找到第一个到源节点的距离比node的距离大的节点

                    tmp->prev->next = node; // 将node插入到这个节点之前
                    node->prev = tmp->prev;
                    node->next = tmp;
                    tmp->prev = node;
                }
            }

            node = nextNode; // 处理下一个节点
        }
    }

    return shortestDist; // 返回每个节点到源节点的最短距离
}

int main() {
    int vertexCount;
    scanf("%d", &vertexCount);
    Graph graph = createGraph(vertexCount); // 创建邻接矩阵图

    for (int i = 0; i < vertexCount; ++i) // 读入邻接矩阵
        for (int j = 0; j < vertexCount; ++j)
            scanf("%d", &graph->matrix[i][j]);

    int *shortestDist = dijkstra(graph); // 执行迪杰斯特拉算法，得到每个节点到源节点的最短距离

    printf("0\n"); // 输出源节点到其自身的最短距离（0）
    for (int i = 0; i < vertexCount - 1; ++i) // 输出每个节点到源节点的最短距离
        printf("%d\n", shortestDist[i]);
}