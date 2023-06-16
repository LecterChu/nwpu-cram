#include<cstdio>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>

using namespace std;

int rm,cn;
typedef struct node
{
    int row,col,val;
    struct node *right; // 右边元素地址
    struct node *down; //  下边元素地址
}Node,*NodePtr;
typedef struct
{
    int m,n,t;
    NodePtr *rp;  // 行指针数组，指向行的第一个元素
    NodePtr *cp; // 列指针数组，指向列的第一个元素
}Matrix;

void CreateMatrix(Matrix *p); //建立矩阵
void InitMatrix(Matrix *p,int m,int n); // 初始化矩阵
void Insert(Matrix &a, NodePtr &b); // 一次将每个元素合并到A矩阵中
void OutputMatrix(Matrix p); //输出矩阵
void PlusMatrix(Matrix &a,Matrix &b); // 把矩阵b 加到矩阵a 上
void CopyNode(NodePtr a,NodePtr &b); // 复制A节点到B

int main()
{
//    freopen("test.in","r",stdin);
    Matrix a,b;
    scanf("%d%d%d%d",&rm,&cn,&a.t,&b.t);
    InitMatrix(&a,rm,cn);
    InitMatrix(&b,rm,cn);
    CreateMatrix(&a);
    CreateMatrix(&b);
    PlusMatrix(a,b);
    OutputMatrix(a);
//    OutputMatrix(b);
    return 0;
}

void InitMatrix(Matrix *p,int m,int n)
{
    p->m = m , p->n = n;
    p->rp = (NodePtr*)malloc((m + 1) * sizeof(NodePtr));
    p->cp = (NodePtr*)malloc((n + 1) * sizeof(NodePtr));
    for(int i=1;i<=m;i++)   p->rp[i] = NULL;
    for(int i=1;i<=n;i++)   p->cp[i] = NULL;
}

void CreateMatrix(Matrix *p)
{
    NodePtr k;
    for(int i=0;i<p->t;i++)
    {
        NodePtr q = (NodePtr)malloc(sizeof(Node));
        scanf("%d%d%d",&q->row,&q->col,&q->val);
        q->right = NULL,q->down = NULL;
        if(p->rp[q->row] == NULL || p->rp[q->row]->col > q->col)  // 行方向建立链表
        {
            q->right = p->rp[q->row];
            p->rp[q->row] = q;
        }
        else
        {
            for (k = p->rp[q->row]; k->right != NULL && k->right->col < q->col;k=k->right) ;
            q->right = k->right;
            k->right = q;
        }
        if(p->cp[q->col] == NULL || p->cp[q->col]->row > q->row) // 列方向建立链表
        {
            q->down = p->cp[q->col];
            p->cp[q->col] = q;
        }
        else
        {
            for (k = p->cp[q->col]; k->down != NULL && k->down->row < q->row;k=k->down) ;
            q->down = k->down;
            k->down = q;
        }
    }
}
void Insert(Matrix &a,NodePtr &x)
{
//    NodePtr cptr = a.cp[x->col]; // 列方向的指针
    if(a.rp[x->row] == NULL)
    {
        a.rp[x->row] = x;
        a.t++; // 矩阵元素个数增加一
    }
    else
    {
        NodePtr rptr = a.rp[x->row];
        NodePtr pre = rptr; // 前取指针，记录前驱方便插入
        while(rptr!=NULL && rptr->col < x->col)
        {
            pre = rptr;
            rptr = rptr->right;
        }
        if(rptr!=NULL && rptr->col == x->col)
        {
            rptr->val += x->val;
            if(rptr->val == 0)
            {
                if(pre == rptr)
                {
                    a.rp[x->row] = rptr->right;
                }
                else
                {
                    pre->right = rptr->right;
                }
                a.t--;
            }
        }
        else 
        {
            if(pre == rptr)
            {
                x->right = rptr;
                a.rp[x->row] = x;
            }
            else
            {
                x->right = rptr;
                pre->right = x;
            }
            a.t++;
        }
    }
}

void PlusMatrix(Matrix &a,Matrix &b)
{
    for(int i=1;i<=b.m;i++)
    {
        NodePtr k = b.rp[i];
        while(k!=NULL)
        {
            NodePtr q = (NodePtr)malloc(sizeof(Node));
            CopyNode(k,q);
            Insert(a,q);
            k = k->right;
        }
    }
}
void CopyNode(NodePtr a,NodePtr &b)
{
    b->val = a->val;
    b->row = a->row;
    b->col = a->col;
    b->down = a->down;
    b->right = a->right;
}

void OutputMatrix(Matrix p)
{
    NodePtr k;
    for(int i=1;i<=p.m;i++)
    {
        k = p.rp[i];

        while(k!=NULL)
        {
//            if(k->val!=0)
            printf("%d %d %d\n",k->row,k->col,k->val);
            k = k->right;
        }
    }
}
