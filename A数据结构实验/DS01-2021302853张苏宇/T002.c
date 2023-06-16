#include <stdio.h>
#include <stdlib.h>

#define MAX 1000      // 设定求小数点后多少位

typedef struct Node { // 双向链表的结构体
	int data;
	struct Node *pre;
	struct Node *next;
} LNODE, * LinkList;


void LinkCreate(LinkList L) ; //初始化双循环链表，并且将每个节点data设为0

void Sum(LinkList a, LinkList b) ; //两个链表相加，从后往前p = p->pre

void Mul(LinkList a, int n) ; //乘法，对链表每一位 *n，从后往前p = p->pre

void Div(LinkList a, int n) ; //除法，对链表每一位 /n，从前往后p = p->next


int main() {
	int n, up, down, s = 0;
	scanf("%d", &n);

	LinkList sum, temp;
	sum = (LinkList)malloc(sizeof(LNODE));
	temp = (LinkList)malloc(sizeof(LNODE));
	//创建两个链表的头结点

	LinkCreate(sum);
	LinkCreate(temp);
	//初始化双循环链表

	sum->next->data = 2;//首项为2
	temp->next->data = 2;//首项为2

	while (s++ < 2000) {//运用递推关系式，计算Π的值
		up = s;
		down = (2 * s + 1);
		Mul(temp, up);
		Div(temp, down);
		Sum(temp, sum);
	}

	sum = sum->next;
	if (n == 0)//考虑无小数的情况
		printf("%d\n", sum->data);
	else {
		printf("%d.", sum->data);
		for (int i = 0; i < n; i++) {
			printf("%d", sum->next->data);
			sum = sum->next;
		}
	}
	printf("\n");
	return 0;

}


void LinkCreate(LinkList L) { //初始化双循环链表，并且将每个节点data设为0
	LinkList p = L, q;
	int i;
	L->next = L->pre = L;
	for (i = 0; i < MAX; i++) {
		q = (LinkList)malloc(sizeof(LNODE));
		q->data = 0;
		p->next = q;
		q->pre = p;
		q->next = L;
		L->pre = q;
		p = q;
	}

}


void Sum(LinkList a, LinkList b) { //两个链表相加，从后往前p = p->pre
	LinkList p = a->pre, q = b->pre;
	int x;
	while (q != b) {
		x = q->data + p->data;
		q->data = x % 10;
		q->pre->data += x / 10;
		q = q->pre;
		p = p->pre;
	}
}


void Mul(LinkList a, int n) { //乘法，对链表每一位 *n，从后往前p = p->pre
	LinkList p = a->pre;
	int  x, y = 0;
	for (; p != a; p = p->pre) {
		x = (p->data) * n + y;
		y = x / 10;
		p->data = x % 10;
	}
	x = (p->data) * n + y;
	y = x / 10;
	p->data = x % 10;
}


void Div(LinkList a, int n) { //除法，对链表每一位 /n，从前往后p = p->next
	LinkList p = a->next;
	int x, y = 0;
	for (; p != a; p = p->next) {
		x = p->data + y * 10;
		p->data = x / n;
		y = x % n;
	}
}


