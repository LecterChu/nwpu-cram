#include<cstdio>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>

using namespace std;

const int maxn = 105;
typedef struct 
{
    int col,row,val; //列，行，值
}triple;
typedef struct node
{
    int m,n,t; // 行数，列数，不为0数的个数
    triple list[maxn];
    node()
    {
        m = n = t = 0;
        for(int i=0;i<maxn;i++) 
        {
            list[i].col = list[i].row = list[i].val = 0;
        }
    }
}matrix;

void PlusMatrix(matrix a,matrix b,matrix &c);

int t1,t2;
int main()
{
    matrix a,b,c;
    scanf("%d%d",&a.m,&a.n);
    scanf("%d%d",&a.t,&b.t);
    for(int i=0;i<a.t;i++)
    {
        scanf("%d%d%d",&a.list[i].row,&a.list[i].col,&a.list[i].val);
    }
    for(int i=0;i<b.t;i++)
    {
        scanf("%d%d%d",&b.list[i].row,&b.list[i].col,&b.list[i].val);
    }
    PlusMatrix(a,b,c);
    for(int i=0;i<c.t;i++)
    {
        printf("%d %d %d\n",c.list[i].row,c.list[i].col,c.list[i].val);
    }
    return 0;
}

void PlusMatrix(matrix a,matrix b,matrix &c)
{
    int i=0,j=0,k=0; // 对应a，b, c矩阵的指针
    while(i<a.t && j<b.t)
    {
        if(a.list[i].row < b.list[j].row || (a.list[i].row == b.list[j].row && a.list[i].col < b.list[j].col))
        {
            c.t++;
            c.list[k++] = a.list[i++]; 
        }
        else
        {
            if(a.list[i].row > b.list[j].row || (a.list[i].row == b.list[j].row && a.list[i].col > b.list[j].col))
            {
                c.t++;
                c.list[k++] = b.list[j++];
            }
            else
            {
                if(a.list[i].val + b.list[j].val !=0 )
                {
                    c.t++;
                    c.list[k].row = a.list[i].row;
                    c.list[k].col = a.list[i].col;
                    c.list[k++].val = a.list[i].val + b.list[j].val;
                }
                i++;
                j++;
            }
        }
        
    }
}