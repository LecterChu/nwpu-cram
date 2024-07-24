#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    int **p;
    int rows;
    int cols;
} Graph;
#define INF 10000

Graph createGraph(int rows, int cols)
{
    Graph m;
    m.p = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
    {
        m.p[i] = (int *)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++)
        {
            m.p[i][j] = INF;
        }
    }
    m.rows = rows;
    m.cols = cols;
    return m;
}

Graph createIdxGraph(int rows, int cols)
{
    Graph m;
    m.p = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
    {
        m.p[i] = (int *)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++)
        {
            m.p[i][j] = -1;
        }
    }
    m.rows = rows;
    m.cols = cols;
    return m;
}

void freeGraph(Graph m)
{
    for (int i = 0; i < m.rows; i++)
    {
        free(m.p[i]);
    }
    free(m.p);
}
void scanfGraph(Graph m)
{
    for (int i = 0; i < m.rows; i++)
    {
        for (int j = 0; j < m.cols; j++)
        {
            scanf("%d", &m.p[i][j]);
        }
    }
}

#define foreach(i, n) for (int i = 0; i < n; i++)

int find_nearest(Graph m, int v0, int *dist, int *final)
{
    int min = INF;
    int v = -1;
    foreach (i, m.rows)
    {
        if (!final[i] && dist[i] < min)
        {
            min = dist[i];
            v = i;
        }
    }
    return v;
}
// 更新v0到v_nearest的最短路径
void update_nearest(Graph m, Graph nearest_path, int v0, int v_nearest, int *dist, int *path, int *final)
{
    final[v_nearest] = 1;
    foreach (j, m.rows)
    {
        if (!final[j] && dist[v_nearest] + m.p[v_nearest][j] < dist[j])
        {
            dist[j] = dist[v_nearest] + m.p[v_nearest][j];
            path[j] = v_nearest;
            nearest_path.p[j][0] = v_nearest;
        }
    }
}
// 求v0结点到其他结点的最短路径
Graph dijkstra(Graph m, int v0)
{
    Graph nearest_path = createIdxGraph(m.rows, m.rows);
    int *dist = (int *)malloc(m.rows * sizeof(int));
    int *path = (int *)malloc(m.rows * sizeof(int));
    int *final = (int *)malloc(m.rows * sizeof(int)); // 判断是否已经求得最短路径
    foreach (i, m.rows)
    {
        dist[i] = m.p[v0][i];
        final[i] = 0;
        if (m.p[v0][i] < INF)
        {
            path[i] = v0; // 0结点到i结点有直接路径
            nearest_path.p[i][0] = v0;
        }
        else
        {
            path[i] = -1;
        }
    }
    foreach (i, m.rows)
    {
        int nearest = find_nearest(m, v0, dist, final);
        if (nearest == -1)
        {
            break;
        }
        update_nearest(m, nearest_path, v0, nearest, dist, path, final);
    }
    free(path);
    free(final);
    free(dist);
    return nearest_path;
}

void print_path(Graph nearest_path, int v0, int v1)
{
    if (v0 == v1)
    {
        printf("%d\n", v0);
        return;
    }
    if (nearest_path.p[v1][0] == -1)
    {
        printf("no path\n");
        return;
    }
    print_path(nearest_path, v0, nearest_path.p[v1][0]);
    printf("%d\n", v1);
}

void main()
{
    int N;
    scanf("%d", &N);
    Graph m = createGraph(N, N);
    scanfGraph(m);
    Graph path = dijkstra(m, 0);
    int v0, v1;
    scanf("%d %d", &v0, &v1);
    print_path(path, v0, v1);
    freeGraph(path);
    freeGraph(m);
}