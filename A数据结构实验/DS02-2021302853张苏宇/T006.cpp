#include <stdio.h>



//定义三元组结构体
typedef struct {
	int r, c;
	//所在行数和列数
	int d;
	//所表示的值
} Triple;

//一个矩阵的数据类型
typedef struct {
	Triple list[1000];
	//1000个三元表
	int m, n, t;
	//存储这个矩阵当中信息，m行，n列，t个非0元素
	int rpos[1000] = {0};
} Matrix;


void InitMatrix(Matrix *a);//初始化矩阵

void OutputMatrix(Matrix a);//输出函数，将三元组表内矩阵信息以三元组形式输出

void MutiplyMatrix(Matrix a, Matrix b, Matrix *c); //矩阵相乘


int main() {
	Matrix a, b, c;
	InitMatrix(&a);
	InitMatrix(&b);
	MutiplyMatrix(a, b, &c);
	OutputMatrix(c);
	return 0;
}


//初始化矩阵
void InitMatrix(Matrix *A) {
	int i, j, k;
	scanf("%d %d", &A->m, &A->n);
	A->t = 0;
	while (1) {
		scanf("%d %d %d", &i, &j, &k);
		if (i == 0 && j == 0 && k == 0)
			break;
		//当输入0 0 0时结束
		A->t++;
		//从1开始
		A->list[A->t].r = i;
		A->list[A->t].c = j;
		A->list[A->t].d = k;
		A->rpos[i]++;
		//输入时设计rpos前缀和数组，记录第i行中的非0元素个数
	}

	//通过两个for循环，算出第i行中第一个元素在其三元组表中的位置，并将其存储在对应的rpos[i]数组当中
	for (int i = 1; i <= A->m; i++)
		A->rpos[i] += A->rpos[i - 1];
	for (int i = A->m; i >= 1; i--)
		A->rpos[i] = A->rpos[i - 1] + 1;
}

//矩阵相乘
void MutiplyMatrix(Matrix a, Matrix b, Matrix *c) {
	//对c矩阵的基本信息初始化赋值
	c->m = a.m;
	c->n = b.n;
	c->t = 0;
	int t[1000] = {0};
	int x, y, z, s;
	//判断条件是否不等于0
	if (a.t * b.t != 0) {
		for (int i = 1; i <= a.m; i++) {
			for (int j = 1; j <= a.n; j++)
				t[j] = 0;
			c->rpos[i] = c->t + 1;

			if (i < a.m)
				x = a.rpos[i + 1];
			else
				x = a.t + 1;

			for (int p = a.rpos[i]; p < x; p++) {
				int c = a.list[p].c;

				if (c < b.m)
					y = b.rpos[c + 1];
				else
					y = b.t + 1;

				for (int q = b.rpos[c]; q < y; q++) {
					z = b.list[q].c;
					t[z] += (a.list[p].d * b.list[q].d);
				}
			}
			//求a.list[p].d 和 b.list[q].d的乘积

			for (int k = 1; k <= c->n; k++) {
				if (t[k]) {
					c->t++;
					c->list[c->t].r = i;
					c->list[c->t].c = k;
					c->list[c->t].d = t[k];
				}
			}
			//

		}
	}
}

//输出函数，将三元组表内矩阵信息以三元组形式输出
void OutputMatrix(Matrix A) {
	for (int i = 1; i <= A.t; i++) {
		printf("%d %d %d\n", A.list[i].r, A.list[i].c, A.list[i].d);
	}
}
