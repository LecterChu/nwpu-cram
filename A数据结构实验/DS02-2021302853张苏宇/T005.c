#include <stdio.h>

//定义三元组结构体
typedef struct node {
	int r, c, d;
	//分别指向该结构体down和right的指针
	struct node *right;
	struct node *down;
} Node, *NodePtr;

//定义十字链表
typedef struct {
	int m, n, t;
	//分别指向下和右的指针
	NodePtr *rp;
	NodePtr *cp;
} Matrix;


void CreateMatrix(Matrix *p);//创造十字链表

void InitMatrix(Matrix *p, int m, int n); //初始化稀疏矩阵

void OutputMatrix(Matrix p);//输出稀疏矩阵

void PlusMatrix(Matrix *a, Matrix *b); //两个十字链表相加

int rm, rn;//定义全局变量，函数中需使用


//通过主函数调用初始化函数，创建函数，相加函数和输出函数。
int main() {

	Matrix a, b;
	scanf("%d %d %d %d", &rm, &rn, &a.t, &b.t);
	InitMatrix(&a, rm, rn);
	InitMatrix(&b, rm, rn);
	CreateMatrix(&a);
	CreateMatrix(&b);
	PlusMatrix(&a, &b);
	OutputMatrix(a);
	return 0;

}


//初始化稀疏矩阵
//增加指针数组，每一个元素都是指针，rp cp则是二级指针
void InitMatrix(Matrix *p, int m, int n) {
	p->m = m, p->n = n;
	//申请内存
	p->rp = (NodePtr *)malloc((m + 1) * sizeof(NodePtr));
	p->cp = (NodePtr *)malloc((n + 1) * sizeof(NodePtr));
	//初始化空链表
	for (int i = 1; i < m + 1; i++)
		p->rp[i] = NULL;
	for (int i = 1; i < n + 1; i++)
		p->cp[i] = NULL;
}

//创造十字链表
//通过判断节点行数列数和当前矩阵的状态之间的关系条件不断添加进入矩阵对应节点，分别从行和列两个顺序遍历插入。
void CreateMatrix(Matrix *p) {
	NodePtr k;

	//逐一处理各三元组
	for (int i = 0; i < p->t; i++) {
		NodePtr q = (NodePtr)malloc(sizeof(Node));
		scanf("%d%d%d", &q->r, &q->c, &q->d);
		q->right = NULL, q->down = NULL;

		// 行方向建立链表
		if (p->rp[q->r] == NULL || p->rp[q->r]->c > q->c) {
			q->right = p->rp[q->r];
			p->rp[q->r] = q;
		} else {
			for (k = p->rp[q->r]; k->right != NULL && k->right->c < q->c; k = k->right) ;
			q->right = k->right;
			k->right = q;
		}

		// 列方向建立链表
		if (p->cp[q->c] == NULL || p->cp[q->c]->r > q->r) {
			q->down = p->cp[q->c];
			p->cp[q->c] = q;
		} else {
			for (k = p->cp[q->c]; k->down != NULL && k->down->r < q->r; k = k->down) ;
			q->down = k->down;
			k->down = q;
		}
	}
}


//输出稀疏矩阵
void OutputMatrix(Matrix p) {
	NodePtr k;
	//逐一输出
	for (int i = 1; i <= p.m; i++) {
		k = p.rp[i];
		while (k != NULL) {
			printf("%d %d %d\n", k->r, k->c, k->d);
			k = k->right;
		}
	}
}


//两个十字链表相加
void PlusMatrix(Matrix *a, Matrix *b) {
	NodePtr k, j;

	//按照从上到下从左到右的顺序依次相加
	//不断析取第二个矩阵的节点，和创建链表一样，不断判断条件，添加进入第一个矩阵
	for (int i = 1; i <= rm; i++) {
		k = b->rp[i];
		while (k != NULL) {
			j = (NodePtr)malloc(sizeof(Node));
			j->c = k->c;
			j->r = k->r;
			j->d = k->d;
			j->down = NULL;
			j->right = NULL;

			//如果right为空
			if (a->rp[j->r] == NULL) {
				a->rp[j->r] = j;
				a->t++;
			} else {
				NodePtr h = a->rp[j->r];
				NodePtr pre = h;
				while (h != NULL && h->c < j->c) {
					pre = h;
					h = h->right;
				}


				//若是行数列数相等则相加，若为0则删去此节点。
				if (h != NULL && h->c == j->c) {
					h->d = h->d + j->d;
					if (h->d == 0) {
						if (pre == h) {
							a->rp[j->r] = h->right;
						} else {
							pre->right = h->right;
						}
						a->t--;
					}
				}
				//将剩余的直接保存
				else {
					if (pre == h) {
						j->right = a->rp[j->r];
						a->rp[j->r] = j;
					} else {
						j->right = h;
						pre->right = j;
					}
					a->t++;
				}
			}
			k = k->right;
		}

	}
}


