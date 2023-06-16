/*
4 4
1 1 1
2 1 2
3 2 3
0 0 0
*/
#include <stdio.h>
#include <process.h>

typedef struct
{
	int r, c, d;
}Triple;

typedef struct
{
	Triple data[200];
	int m, n;
}TsMatrix;

void transpose(TsMatrix A, TsMatrix* B, int i)
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

int main()
{
	int m, n, i = 0, j = 0;
	scanf("%d%d", &m, &n);
	TsMatrix A, B;
	A.m = m;
	A.n = n;
	for (;;)
	{
		int r, c, d;
		scanf("%d%d%d", &r, &c, &d);
		if (r == 0 && c == 0 && d == 0)
			break;
		A.data[i].r = r, A.data[i].c = c, A.data[i].d = d;
		i++;
	}
	transpose(A, &B, i);
	for (j = 0; j < i; j++)
	{
		printf("%d %d %d\n", A.data[j].c, A.data[j].r, A.data[j].d);
	}
	system("pause");
	return 0;
}
