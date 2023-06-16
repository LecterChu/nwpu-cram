/*
4 
0 2 10 10000
2 0 7 3
10 7 0 6
10000 3 6 0
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>
#include <stdlib.h>

using namespace std;

const int maxn = 105;
const int inf = 10000;
int n;
int map[maxn][maxn];
int dis[maxn];
bool vis[maxn];
int pre[maxn];
int u,v;
void dijkstra(int s) //s start
{
    for(int i=0;i<n;i++)
    {
        dis[i] = inf;
        vis[i] = false;
    }
    int u = s;
    dis[u] = 0;
    while(!vis[u])
    {
        vis[u] = true;
        for(int i=0;i<n;i++)
        {
            if(!vis[i] && dis[i] > dis[u] + map[u][i])
            {
                dis[i] = map[u][i] + dis[u];
                pre[i] = u;
            }
        }
        int tag = inf;
        for(int i=0;i<n;i++)
        {
            if(!vis[i] && dis[i] < tag)
            {
                tag = dis[i];
                u = i;
            }
        }
    }
}
void PrintPath(int u,int v)
{
    if(u == v)
    {
        printf("%d\n",u);
        return ;
    }
    PrintPath(u,pre[v]);
    printf("%d\n",v); 
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            scanf("%d",&map[i][j]);
        }
    }
    scanf("%d%d",&u,&v);
    dijkstra(0);
    dijkstra(u);
    PrintPath(u,v);
    system("pause");
    return 0;
}