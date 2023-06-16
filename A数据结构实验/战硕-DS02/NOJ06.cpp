#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>

using namespace std;

const int maxn = 1005;
typedef struct node
{
    int col,row,val; //分别代表非零元素的 列，行，值
}Triple;

typedef struct
{
    int m,n,t; //矩阵的行数，列数和非零元个数
    int rpos[maxn]; //行元素个数前缀和数组
    Triple list[maxn]; //三元组
}Matrix;

void Minput(Matrix &A)
{
    int i,j,k;
    scanf("%d %d",&A.m,&A.n);
    while(1)
    {
        scanf("%d %d %d",&i,&j,&k);
        if(i==0 && j==0 && k==0) break;
        A.t++;
        A.list[A.t].row = i;
        A.list[A.t].col = j;
        A.list[A.t].val = k;
        A.rpos[i]++;
    }
    for(int i=1;i<=A.m;i++) A.rpos[i]+=A.rpos[i-1];
    for(int i=A.m;i>=1;i--) A.rpos[i] = A.rpos[i-1] + 1;
}

void Multi(Matrix A,Matrix B,Matrix &C)
{
    C.m = A.m, C.n = B.n , C.t = 0;
    int temp[maxn]; //行元素存储
    int Ar,Br,ptr;
    if(A.t * B.t !=0)
    {
        for(int i=1;i<=A.m;i++)
        {
            for(int j=1;j<=A.n;j++) temp[j] = 0;
            C.rpos[i] = C.t + 1;

            if(i < A.m) Ar = A.rpos[i+1];
            else Ar = A.t +1;

            for(int p=A.rpos[i];p<Ar;p++)
            {
                int c = A.list[p].col;
                
                if(c < B.m) Br = B.rpos[c+1];
                else Br = B.t + 1;
                for(int q = B.rpos[c];q<Br;q++)
                {
                    ptr = B.list[q].col;
                    temp[ptr] += (A.list[p].val * B.list[q].val);
                }
            }
            for(int k=1;k<=C.n;k++)
            {
                if(temp[k])
                {
                    C.t++;
                    C.list[C.t].row = i;
                    C.list[C.t].col = k;
                    C.list[C.t].val = temp[k]; 
                }
            }
        }
    }
}
void Moutput(Matrix A)
{
    for(int i=1;i<=A.t;i++)
    {
        printf("%d %d %d\n",A.list[i].row,A.list[i].col,A.list[i].val);
    }
}
int main()
{
    Matrix a,b,c;
    Minput(a);
    Minput(b);
    Multi(a,b,c);
    Moutput(c);
    return 0;
}