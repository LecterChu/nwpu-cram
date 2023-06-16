#include <stdio.h>
#define MAX 1000


//定义三元组结构体
typedef struct {
	int r, c;
	//所在行数和列数
	int d;
	//所表示的值
} Triple;


//存储矩阵的三元组顺序表
typedef struct {
	Triple data[MAX];
	int m, n, t;
	//存储这个矩阵当中信息，m行，n列，t个非0元素
} TsMatrix;


//稀疏矩阵的转置函数
void Transpose(TsMatrix A, TsMatrix *B, int i) {
	int p, q, r, x = i;

//将矩阵 a 存储的行数、列数赋值给转置矩阵 b
	B->m = A.n;
	B->n = A.m;

//从第一行开始依次遍历
	if (i) {
		q = 0;
		for (r = 0; r < A.n; r++)
			for (p = 0; p < x; p++) {
				if (A.data[p].c == r) {
					//交换a,b的行数和列数，并把a的值赋给b
					B->data[q].r = A.data[p].c;
					B->data[q].c = A.data[p].r;
					B->data[q].d = A.data[p].d;
					q++;
				}
			}

	}
}

int main() {
	int m, n, i = 0, j = 0;

	scanf("%d %d", &m, &n);
	TsMatrix A, B;
	A.m = m;
	A.n = n;

//获取初始矩阵a
	while (1) {
		int r, c, d;
		scanf("%d %d %d", &r, &c, &d);
		if (r == 0 && c == 0 && d == 0)
			break;
		A.data[i].r = r, A.data[i].c = c, A.data[i].d = d;
		i++;
	}

	Transpose(A, &B, i);

//逐个输出转置后的矩阵元素
	for (j = 0; j < i; j++) {
		printf("%d %d %d\n", A.data[j].c, A.data[j].r, A.data[j].d);
	}
	return 0;
}