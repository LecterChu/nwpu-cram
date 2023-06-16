/*
6
0 1 4 10000 10000 10000
1 0 2 7 5 10000
4 2 0 10000 1 10000
10000 7 10000 0 3 2
10000 5 1 3 0 6
10000 10000 10000 2 6 0
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>
 #include <stdlib.h>

using namespace std;

int map[105][105];
int n;
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
    for(int i=0;i<n;i++)
    {
        printf("%d\n",map[0][i]);
    }
    system("pause");
    return 0;
}