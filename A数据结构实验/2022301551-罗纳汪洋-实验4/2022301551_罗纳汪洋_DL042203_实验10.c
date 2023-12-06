#include <stdio.h>
#include <stdlib.h>

#define INF 10000 // 定义一个最大值

/*
 * Sample Input
    4
    0 2 10 10000
    2 0 7 3
    10 7 0 6
    10000 3 6 0
    2
    0 2
    3 0
 * Sample Output
    9
    5
 */

typedef struct MatrixGraph { // 定义邻接矩阵图结构体
    int vertexCount;    // 图的节点数
    int **matrix;       // 存储图的邻接矩阵
} *Graph;

Graph createGraph(int vertexCount) { // 创建邻接矩阵图
    Graph graph = (Graph) malloc(sizeof(struct MatrixGraph));           // 创建一个图结构体
    graph->vertexCount = vertexCount;                                   // 节点数为vertexCount
    graph->matrix = (int **) malloc(sizeof(int *) * vertexCount);       // 为存储邻接矩阵分配空间
    for (int i = 0; i < vertexCount; ++i)
        graph->matrix[i] = (int *) malloc(sizeof(int) * vertexCount);   // 为每一行分配空间

    return graph; // 返回创建的图
}

int min(int a, int b) { // 求两个数的最小值
    return a < b ? a : b;
}

void floyd(Graph graph) { // floyd算法求解所有节点之间的最短路径
    int n = graph->vertexCount; // 节点数

    for (int k = 0; k < n; ++k) // 枚举中间节点k
        for (int i = 0; i < n; ++i) // 枚举起始节点i
            for (int j = 0; j < n; ++j) // 枚举结束节点j
                graph->matrix[i][j] = min(graph->matrix[i][k] + graph->matrix[k][j], graph->matrix[i][j]); // 更新i到j的最短路径

}

int main() {
    int vertexCount;
    scanf("%d", &vertexCount); // 读入节点数
    Graph graph = createGraph(vertexCount); // 创建邻接矩阵图

    for (int i = 0; i < vertexCount; ++i)
        for (int j = 0; j < vertexCount; ++j)
            scanf("%d", &graph->matrix[i][j]); // 读入邻接矩阵

    floyd(graph); // 求解所有节点之间的最短路径

    int times;
    scanf("%d", &times); // 读入查询次数
    int shortestPaths[times];
    for (int i = 0; i < times; ++i) { // 处理每个查询
        int startVertex, endVertex;
        scanf("%d%d", &startVertex, &endVertex); // 读入查询的起始节点和结束节点
        shortestPaths[i] = graph->matrix[startVertex][endVertex]; // 获取起始节点到结束节点的最短路径
    }
    for (int i = 0; i < times; ++i)
        printf("%d\n", shortestPaths[i]); // 输出每个查询的最短路径

    return 0;
}