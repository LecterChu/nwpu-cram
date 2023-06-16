/*
4
0 2 10 10000
2 0 7 3
10 7 0 6
10000 3 6 0
2
0 2
3 0
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>
#include <stdlib.h>

using namespace std;

int map[105][105];
int n,m,u,v;
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
    for(int k=0;k<n;k++)
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(i!=j && j!=k && i!=k)
                {
                    if(map[i][j] > map[i][k] + map[k][j])
                    {
                        map[i][j] = map[i][k] + map[k][j];
                    }
                }
            }
        }
    }
    
    scanf("%d",&m);
    for(int i=0;i<m;i++)
    {
        scanf("%d%d",&u,&v);
        printf("%d\n",map[u][v]);
    }
    system("pause");
    return 0;
}