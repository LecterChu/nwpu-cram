#include <stdio.h>
#include <stdlib.h>

#define INF 10000

/*
 * Sample Input
    4
    0 2 10 10000
    2 0 7 3
    10 7 0 6
    10000 3 6 0
    0 2
 * Sample Output
    0
    1
    2
 */

typedef struct MatrixGraph {
    int vertexCount;    // 顶点数
    int **matrix;       // 邻接矩阵
} *Graph;

typedef struct QueueNode {
    int vertex;                     // 顶点
    int dist;                       // 距离
    int path;                       // 前驱顶点
    struct QueueNode *prev, *next;  // 前驱和后继节点
} *QNode;

typedef struct LinkedQueue {
    struct QueueNode *front, *rear; // 队首和队尾指针
} *Queue;

void initQueue(Queue queue) { // 初始化队列
    QNode node = (QNode) malloc(sizeof(struct QueueNode)); // 创建一个节点
    node->dist = 0;                     // 距离初始化为0
    node->next = node->prev = NULL;     // 指针初始化为空
    queue->front = queue->rear = node;  // 队首和队尾都指向该节点
}

void offerQueue(Queue queue, int vertex, int dist, int path) { // 入队操作
    QNode newNode = (QNode) malloc(sizeof(struct QueueNode)); // 创建新节点
    newNode->vertex = vertex;               // 保存顶点
    newNode->dist = dist;                   // 保存距离
    newNode->path = path;                   // 保存前驱顶点
    newNode->next = newNode->prev = NULL;   // 指针初始化为空

    QNode node = queue->front;
    while (node->next && node->next->dist < dist) // 从队首开始遍历，找到第一个距离比当前节点大的节点
        node = node->next;

    if (node->next) // 如果有下一个节点
        node->next->prev = newNode; // 将新节点作为其前驱
    newNode->next = node->next; // 将新节点的后继指向后一个节点
    node->next = newNode;       // 将新节点作为前一个节点的后继
    newNode->prev = node;       // 将新节点的前驱指向前一个节点
    if (!newNode->next) // 如果新节点没有后继
        queue->rear = newNode; // 将新节点作为队尾
}

QNode pollQueue(Queue queue) { // 出队操作
    QNode node = queue->front->next;        // 获取队首节点的后继节点
    if (node->next)
        node->next->prev = queue->front;    // 将后继节点的前驱指向队首
    else
        queue->rear = queue->front;         // 如果没有后继节点，将队尾指向队首
    queue->front->next = node->next;        // 将队首的后继指向后一个节点
    node->next = node->prev = NULL;         // 将出队节点的指针初始化为空
    return node; // 返回出队节点
}

Graph createGraph(int vertexCount) { // 创建图
    Graph graph = (Graph) malloc(sizeof(struct MatrixGraph)); // 创建图
    graph->vertexCount = vertexCount; // 保存顶点数
    graph->matrix = (int **) malloc(sizeof(int *) * vertexCount); // 创建邻接矩阵
    for (int i = 0; i < vertexCount; ++i)
        graph->matrix[i] = (int *) malloc(sizeof(int) * vertexCount);
    return graph; // 返回图
}

int *dijkstra(Graph graph) { // Dijkstra算法
    struct LinkedQueue leftVertex; // 创建一个链式优先队列
    initQueue(&leftVertex); // 初始化优先队列

    int *shortestPath = (int *) malloc(sizeof(int) * graph->vertexCount); // 创建一个数组，存储到源点的最短路径

    for (int i = 1; i < graph->vertexCount; ++i) // 将源点到其它顶点的距离入队
        offerQueue(&leftVertex, i, graph->matrix[0][i], 0);

    for (int i = 0; i < graph->vertexCount - 1; ++i) { // 进行n-1次迭代
        QNode vertex = pollQueue(&leftVertex);          // 获取当前距离源点最近的顶点
        shortestPath[vertex->vertex] = vertex->path;    // 将该顶点的前驱顶点保存到数组中

        QNode node = leftVertex.front->next;
        while (node) { // 遍历队列中剩余的顶点
            QNode nextNode = node->next; // 保存下一个节点的指针

            int newDist = vertex->dist + graph->matrix[vertex->vertex][node->vertex]; // 计算新的距离
            if (newDist < node->dist) { // 如果新距离比旧距离小
                node->dist = newDist; // 更新距离
                node->path = vertex->vertex; // 更新前驱顶点

                if (node->dist < node->prev->dist) { // 如果该节点比前一个节点更靠近源点
                    if (node->next)
                        node->next->prev = node->prev;  // 将该节点的后继节点的前驱指向该节点的前驱
                    else
                        leftVertex.rear = node->prev;   // 如果该节点没有后继，将队尾指向该节点的前驱
                    node->prev->next = node->next;      // 将该节点的前驱节点的后继指向该节点的后继

                    QNode tmp = node->prev;
                    while (tmp->prev->dist > node->dist) // 将该节点插入到距离更远的节点之前
                        tmp = tmp->prev;

                    tmp->prev->next = node;
                    node->prev = tmp->prev;
                    node->next = tmp;
                    tmp->prev = node;
                }

            }

            node = nextNode;
        }
    }

    return shortestPath; // 返回到源点的最短路径
}

void printShortestPath(int *shortestPath, int endVertex) { // 输出最短路径
    if (endVertex == 0) return; // 如果到达源点，结束递归

    int lastVertex = shortestPath[endVertex];
    printShortestPath(shortestPath, lastVertex); // 递归输出前驱顶点
    printf("%d\n", lastVertex); // 输出顶点
}

int main() { // 主函数
    int vertexCount;
    scanf("%d", &vertexCount); // 输入顶点数
    Graph graph = createGraph(vertexCount); // 创建图

    for (int i = 0; i < vertexCount; ++i)
        for (int j = 0; j < vertexCount; ++j)
            scanf("%d", &graph->matrix[i][j]); // 输入邻接矩阵

    int *shortestPath = dijkstra(graph); // 运行Dijkstra算法，获取最短路径长度

    int startVertex, endVertex;
    scanf("%d%d", &startVertex, &endVertex);    // 输入起点和终点
    printShortestPath(shortestPath, endVertex); // 输出最短路径
    printf("%d", endVertex);                    // 输出终点
}