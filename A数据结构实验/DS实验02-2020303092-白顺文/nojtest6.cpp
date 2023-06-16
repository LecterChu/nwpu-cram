/*
3 3
1 1 1
2 2 2
2 3 4
3 1 -4
0 0 0
3 3
1 3 -2
2 3 -5
3 1 8
3 2 -6
0 0 0
*/

#include <stdio.h>
#include <process.h>
typedef struct
{
	int r, c, d; //r是第几行，c是第几列，d是元素内容
}Triple;

typedef struct
{
	Triple list[1000]; //1000个三元表
	int m, n, t; //存储这个矩阵当中信息，m是m行，n列，t是how many非0元素
	int rpos[1000]={0};
}Matrix; //一个矩阵的数据类型

void InitMatrix(Matrix* a);
void OutputMatrix(Matrix a);
void MutiplyMatrix(Matrix a,Matrix b,Matrix *c);

int main()
{
	Matrix a,b,c;
	InitMatrix(&a);
	InitMatrix(&b);
	MutiplyMatrix(a,b,&c);
	OutputMatrix(c);
	system("pause");
    return 0;
}

void InitMatrix(Matrix *A)
{
	int i,j,k;
    scanf("%d %d",&A->m,&A->n);
	A->t=0;
    while(1)
    {
        scanf("%d %d %d",&i,&j,&k);
        if(i==0 && j==0 && k==0) break;
        A->t++;//start from 1
        A->list[A->t].r = i;
        A->list[A->t].c = j;
        A->list[A->t].d = k;
        A->rpos[i]++;
    }
    for(int i=1;i<=A->m;i++) A->rpos[i]+=A->rpos[i-1];
    for(int i=A->m;i>=1;i--) A->rpos[i] = A->rpos[i-1] + 1;
}



void MutiplyMatrix(Matrix a,Matrix b,Matrix *c)
{
	c->m=a.m;
	c->n=b.n;
	c->t=0;
	int t[1000]={0};
	int x,y,z,s;
	if(a.t*b.t!=0)
	{
		for(int i=1;i<=a.m;i++)
		{
			for(int j=1;j<=a.n;j++) t[j]=0;
			c->rpos[i]=c->t+1;

			if(i < a.m)  x= a.rpos[i+1];
            else x= a.t +1;

			for(int p=a.rpos[i];p<x;p++)
			{
				int c=a.list[p].c;

				if(c<b.m) y=b.rpos[c+1];
				else y=b.t+1;

				for(int q=b.rpos[c];q<y;q++)
				{
					z=b.list[q].c;
					t[z]+=(a.list[p].d*b.list[q].d);
				}
			}

			for(int k=1;k<=c->n;k++)
			{
				if(t[k])
				{
					c->t++;
					c->list[c->t].r=i;
					c->list[c->t].c=k;
					c->list[c->t].d=t[k];
				}
			}

		}
	}
}


void OutputMatrix(Matrix A)
{
    for(int i=1;i<=A.t;i++)
    {
        printf("%d %d %d\n",A.list[i].r,A.list[i].c,A.list[i].d);
    }
}
