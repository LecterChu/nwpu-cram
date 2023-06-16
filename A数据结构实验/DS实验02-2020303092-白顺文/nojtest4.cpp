/*
3 4 3 2
1 1 1
1 3 1
2 2 2
1 2 1
2 2 3

*/
#include <stdio.h>
#include <process.h>
typedef struct
{
	int r, c, d; //r是第几行，c是第几列，d是元素内容
}Triple;

typedef struct
{
	Triple data[200]; //200个三元表
	int m, n, t; //存储这个矩阵当中信息，m是m行，n列，t是how many非0元素
}TsMatrix; //一个矩阵的数据类型

void transpose(TsMatrix A, TsMatrix* B, int i)//之前的转置用不到
{
	int p, q, col, x = i;
	B->m = A.n;
	B->n = A.m;
	if (i) {
		q = 0;
		for (col = 0; col < A.n; col++)
			for (p = 0; p < x; p++)
			{
				if (A.data[p].c == col) {
					B->data[q].r = A.data[p].c;
					B->data[q].c = A.data[p].r;
					B->data[q].d = A.data[p].d;
					++q;
					i--;
				}
			}

	}
}

void Add(TsMatrix A,TsMatrix* B)//自己的一个想法，最后没有写下去，abandoned
{
	int i,j,k;
	//判断谁的元素的多就按谁来遍历，以少的为标准，寻找多的矩阵里面相同标号的元素
	if(B->t>A.t)
	{
		for(i=0;i<A.t;i++)
			for ( j = 0; j < B->t; j++)
			{
				if(A.data[i].c==B->data[j].c&&A.data[i].r==B->data[j].r)
				{
					B->data[j].d=A.data[i].d+B->data[j].d;
				}
			}
			
	}
	else
	{
		for(i=0;i<A.t;i++)
			for ( j = 0; j < B->t; j++)
			{
				if(A.data[j].c==B->data[i].c&&A.data[j].r==B->data[i].r)
				{
					B->data[i].d=A.data[j].d+B->data[i].d;
				}
			}
	}

}

TsMatrix PlusMatrix(TsMatrix a,TsMatrix b);

int main()
{
	int m,n,t1,t2;
	scanf("%d%d%d%d",&m,&n,&t1,&t2);
	TsMatrix a,b,c;
	a.m=b.m=m;
	a.n=b.n=n;
	a.t=t1,b.t=t2;
	for(int i=0;i<t1;i++)
	{
		scanf("%d%d%d",&a.data[i].r,&a.data[i].c,&a.data[i].d);
	}
	for (int i = 0; i < t2; i++)
	{
		scanf("%d%d%d",&b.data[i].r,&b.data[i].c,&b.data[i].d);
	}
	c=PlusMatrix(a,b);
	for (int i = 0; i <c.t ; i++)
	{
		printf("%d %d %d\n",c.data[i].r,c.data[i].c,c.data[i].d);
	}
	return 0;
}

TsMatrix PlusMatrix(TsMatrix a,TsMatrix b)
{
	int i=0,k=0,j=0;
	TsMatrix c;//保存新的矩阵并return回去
	c.t=0;
	c.m=a.m;
	c.n=a.n;
	while(i<a.t&&j<b.t)
	{	//判断条件选择，从小到大依次进入c矩阵，谁r小或者r相等谁c小谁先进，避开加起来等于0的，若相等就加起来一起进
		if(a.data[i].r<b.data[j].r||(a.data[i].r==b.data[j].r&&a.data[i].c<b.data[j].c))
		{
			c.data[k++]=a.data[i++];
			c.t++;
		}
		else if(a.data[i].r>b.data[j].r||(a.data[i].r==b.data[j].r&&a.data[i].c>b.data[j].c))
		{
			c.data[k++]=b.data[j++];
			c.t++;
		}
		else
		{
			if(a.data[i].d+b.data[j].d!=0)
			{
				c.data[k]=a.data[i];
				c.data[k++].d=a.data[i++].d+b.data[j++].d;
				c.t++;
			}
		}
	}
    system("pause");
	return c;
}