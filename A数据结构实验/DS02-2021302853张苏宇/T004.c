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


//稀疏矩阵的加法，返回值为新矩阵
TsMatrix PlusMatrix(TsMatrix a, TsMatrix b) {
	int i = 0, k = 0, j = 0;
	TsMatrix c;
	c.t = 0;
	c.m = a.m;
	c.n = a.n;
//初始化返回的新矩阵

	while (i <= a.t && j <= b.t && (!(i == a.t && j == b.t))) {
		//判断条件
		//按照从上到下从左到右的顺序依次遍历，先比较同行，再比较同列
		if (a.data[i].r < b.data[j].r || (a.data[i].r == b.data[j].r && a.data[i].c < b.data[j].c)) {
			c.data[k++] = a.data[i++];
			c.t++;
		} else if (a.data[i].r > b.data[j].r || (a.data[i].r == b.data[j].r && a.data[i].c > b.data[j].c)) {
			c.data[k++] = b.data[j++];
			c.t++;
		}
		//考虑相加和为0的情况，如果不为零则保留
		else {
			if (a.data[i].d + b.data[j].d != 0) {
				c.data[k] = a.data[i];
				c.data[k++].d = a.data[i++].d + b.data[j++].d;
				c.t++;
			}
		}
	}
	return c;
}



int main() {
	int m, n, t1, t2;
	scanf("%d%d%d%d", &m, &n, &t1, &t2);
	TsMatrix a, b, c;
	a.m = b.m = m;
	a.n = b.n = n;
	a.t = t1, b.t = t2;

	for (int i = 0; i < t1; i++) {
		scanf("%d%d%d", &a.data[i].r, &a.data[i].c, &a.data[i].d);
	}

	for (int i = 0; i < t2; i++) {
		scanf("%d%d%d", &b.data[i].r, &b.data[i].c, &b.data[i].d);
	}
	//获取要相加的两个矩阵a,b

	c = PlusMatrix(a, b);

	//逐个输出相加后的矩阵元素
	for (int i = 0; i < c.t ; i++) {
		printf("%d %d %d\n", c.data[i].r, c.data[i].c, c.data[i].d);
	}
	return 0;
}
