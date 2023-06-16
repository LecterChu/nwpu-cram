#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#define MAX 1000

typedef struct Node
{
	int data;
	struct Node* pre;
	struct Node* next;
}LNode, * LinkList;


void LinkCreate(LinkList L) //初始化双循环链表，置每个节点data为0
{
	LinkList p = L, q;
	int i;
	L->next = L->pre = L;
	for (i = 0; i < MAX; i++)
	{
		q = (LinkList)malloc(sizeof(LNode));
		q->data = 0;
		p->next = q;
		q->pre = p;
		q->next = L;
		L->pre = q;
		p = q;
	}

}

void Sum(LinkList a, LinkList b) //加法，从后往前pre
{
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

void Mul(LinkList a, int n) //乘法，从后往前pre
{
	LinkList p = a->pre;
	int  x, y = 0;
	for (; p != a; p = p->pre)
	{
		x = (p->data) * n + y;
		y = x / 10;
		p->data = x % 10;
	}
	x = (p->data) * n + y;
	y = x / 10;
	p->data = x % 10;
}

void Div(LinkList a, int n) //除法，从前往后next
{
	LinkList p = a->next;
	int x, y = 0;
	for (; p != a; p = p->next)
	{
		x = p->data + y * 10;
		p->data = x / n;
		y = x % n;
	}
}

int main()
{
	int n, i, top, bot, s = 1;
	scanf("%d", &n);
	LinkList sum, rad;
	sum = (LinkList)malloc(sizeof(LNode));
	rad = (LinkList)malloc(sizeof(LNode));
	LinkCreate(sum);
	LinkCreate(rad);
	sum->next->data = 3;//首项
	rad->next->data = 3;//首项
	while (s < 2000)
	{
		top = (2 * s - 1) * (2 * s - 1);
		bot = 8 * s * (2 * s + 1);
		Mul(rad, top);
		Div(rad, bot);
		Sum(rad, sum);
		s++;
	}
	if (n == 0) printf("3\n");
	else {
		sum = sum->next;
		printf("%d.", sum->data);
		for (i = 0; i < n; i++) {
			printf("%d", sum->next->data);
			sum = sum->next;
		}
	}
	printf("\n");
	return 0;

}

