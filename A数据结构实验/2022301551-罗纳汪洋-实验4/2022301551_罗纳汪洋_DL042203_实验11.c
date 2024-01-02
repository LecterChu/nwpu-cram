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
    2
    0 2
    3 0
 * Sample Output
    0
    1
    2
    3
    1
    0
 */

// 定义邻接矩阵图结构体
typedef struct MatrixGraph {
    int vertexCount; //节点数
    int **matrix, **shortestDist, **shortestPath; //存储邻接矩阵和最短路径和最短路径上的节点
} *Graph;

// 创建邻接矩阵图
Graph createGraph(int vertexCount) {
    Graph graph = (Graph) malloc(sizeof(struct MatrixGraph)); // 创建一个图结构体
    graph->vertexCount = vertexCount; // 节点数为vertexCount
    graph->matrix = (int **) malloc(sizeof(int *) * vertexCount); // 为存储邻接矩阵分配空间
    graph->shortestDist = (int **) malloc(sizeof(int *) * vertexCount); // 为存储最短路径分配空间
    graph->shortestPath = (int **) malloc(sizeof(int *) * vertexCount); // 为存储最短路径上的节点分配空间
    for (int i = 0; i < vertexCount; ++i) {
        graph->matrix[i] = (int *) malloc(sizeof(int) * vertexCount); // 为每一行分配空间
        graph->shortestDist[i] = (int *) malloc(sizeof(int) * vertexCount); // 为存储最短路径分配空间
        graph->shortestPath[i] = (int *) malloc(sizeof(int) * vertexCount); // 为存储最短路径上的节点分配空间
    }
    return graph; // 返回创建的图
}

// 返回两个整数中的较小值
int min(int a, int b) {
    return a < b ? a : b;
}

// Floyd算法求解所有节点间的最短路径
void floyd(Graph graph) {
    int n = graph->vertexCount;

    for (int i = 0; i < n; ++i) // 初始化最短路径和最短路径上的节点数组
        for (int j = 0; j < n; ++j) {
            graph->shortestDist[i][j] = graph->matrix[i][j]; // 最短路径初始值为邻接矩阵的值
            graph->shortestPath[i][j] = j; // 最短路径上的节点初始值为终点j
        }

    for (int k = 0; k < n; ++k) // 遍历所有中间节点
        for (int i = 0; i < n; ++i) // 遍历所有起点
            for (int j = 0; j < n; ++j) { // 遍历所有终点
                int newDist = min(graph->shortestDist[i][k] + graph->shortestDist[k][j],
                                  graph->shortestDist[i][j]); // 计算经过中间节点k的最短路径距离
                if (newDist != graph->shortestDist[i][j]) // 如果新的最短路径距离小于原来的最短路径距离
                    graph->shortestPath[i][j] = k; // 更新最短路径上的节点
                graph->shortestDist[i][j] = newDist; // 更新最短路径距离
            }
}

// 输出起点到终点最短路径上的节点
void printShortestPath(Graph graph, int startVertex, int endVertex) {
    int path = graph->shortestPath[startVertex][endVertex]; // 起点到终点最短路径上的节点
    printf("%d\n", path);

    if (path != endVertex) // 如果当前节点不是终点
        printShortestPath(graph, path, endVertex); // 继续输出下一个节点
}

int main() {
    int vertexCount;
    scanf("%d", &vertexCount); // 输入节点数
    Graph graph = createGraph(vertexCount); // 创建邻接矩阵图

    for (int i = 0; i < vertexCount; ++i)
        for (int j = 0; j < vertexCount; ++j) {
            int dist;
            scanf("%d", &dist); // 输入两个节点之间的距离
            graph->matrix[i][j] = graph->shortestDist[i][j] = dist; // 更新邻接矩阵和最短路径距离
            graph->shortestPath[i][j] = j; // 最短路径上的节点初始值为终点j
        }

    floyd(graph); // 使用Floyd算法求解所有节点间的最短路径

    int times;
    scanf("%d", &times); // 输入需要查询最短路径的次数
    int startVertexs[times], endVertexs[times];
    for (int i = 0; i < times; ++i) {
        scanf("%d%d", &startVertexs[i], &endVertexs[i]); // 输入起点和终点
    }
    for (int i = 0; i < times; ++i) {
        printf("%d\n", startVertexs[i]); // 输出当前查询的起点
        printShortestPath(graph, startVertexs[i], endVertexs[i]); // 输出起点到终点最短路径上的节点
    }
}