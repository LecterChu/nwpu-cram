#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>

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
    return 0;
}