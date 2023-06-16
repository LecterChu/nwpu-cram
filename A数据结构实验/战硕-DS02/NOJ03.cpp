#include <cstdio>

int cpot[30];

typedef struct
{
	int i, j, e;
}Triple;

typedef struct
{
	int m, n, t;
	Triple data[500];
}TsMatrix;

int main()
{
	int i, p;
	TsMatrix M, T;
	M.t = 0;
	scanf("%d %d", &M.m, &M.n);
	while(1)
	{
		++M.t; 
		scanf("%d %d %d", &M.data[M.t].i, &M.data[M.t].j, &M.data[M.t].e);
		if(M.data[M.t].i == 0 && M.data[M.t].j == 0 && M.data[M.t].e == 0)
		{
			M.t--;
			break;
		}
		cpot[M.data[M.t].j]++;
	}
	T.t = M.t;
	for(i = 1; i <= M.n; i++) cpot[i] += cpot[i - 1];
	for(i = M.n; i >= 1; i--) cpot[i] = cpot[i-1] + 1 ;
	for(i = 1; i <= M.t; i++)
	{
		p = cpot[M.data[i].j]++;
		T.data[p].i = M.data[i].j;
		T.data[p].j = M.data[i].i;
		T.data[p].e = M.data[i].e;
	}
	for(i = 1; i <= T.t; i++)
		printf("%d %d %d\n", T.data[i].i, T.data[i].j, T.data[i].e);
	return 0;
}