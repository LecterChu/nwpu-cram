/*
3 4 3 2
1 1 1
1 3 1
2 2 2
1 2 1
2 2 3
*/
#include <stdio.h>
#include <iostream>
#include <process.h>
int rm,rn;
typedef struct node
{
    int r,c,d;
    struct node *right;
    struct node *down;
}Node,*NodePtr;

typedef struct 
{
    int m, n ,t;
    NodePtr* rp;
    NodePtr* cp;
}Matrix;

void CreateMatrix(Matrix *p);//创造十字链表
void InitMatrix(Matrix *p,int m,int n);//初始化
void OutputMatrix(Matrix p);//输出
void PlusMatrix(Matrix *a,Matrix *b);//两个十字链表相加并返回a中

int main()
{
    Matrix a,b;
    scanf("%d%d%d%d",&rm,&rn,&a.t,&b.t);
    InitMatrix(&a,rm,rn);
    InitMatrix(&b,rm,rn);
    CreateMatrix(&a);
    CreateMatrix(&b);
    PlusMatrix(&a,&b);
    OutputMatrix(a);
    system("pause");
    return 0;
}

//初始化 增加指针数组，每一个元素都是指针，rp cp则是二级指针
void InitMatrix(Matrix *p,int m,int n)
{
    p->m=m,p->n=n;
    p->rp=(NodePtr*)malloc((m+1)*sizeof(NodePtr));
    p->cp=(NodePtr*)malloc((n+1)*sizeof(NodePtr));
    for(int i=1;i<m+1;i++) p->rp[i]=NULL;
    for(int i=1;i<n+1;i++) p->cp[i]=NULL;
}

void CreateMatrix(Matrix *p)
{
    NodePtr k;
    for(int i=0;i<p->t;i++)
    {
        NodePtr q = (NodePtr)malloc(sizeof(Node));
        scanf("%d%d%d",&q->r,&q->c,&q->d);
        q->right = NULL,q->down = NULL;
        if(p->rp[q->r] == NULL || p->rp[q->r]->c > q->c)  // 行方向建立链表
        {
            q->right = p->rp[q->r];
            p->rp[q->r] = q;
        }
        else
        {
            for (k = p->rp[q->r]; k->right != NULL && k->right->c < q->c;k=k->right) ;
            q->right = k->right;
            k->right = q;
        }
        if(p->cp[q->c] == NULL || p->cp[q->c]->r > q->r) // 列方向建立链表
        {
            q->down = p->cp[q->c];
            p->cp[q->c] = q;
        }
        else
        {
            for (k = p->cp[q->c]; k->down != NULL && k->down->r< q->r;k=k->down) ;
            q->down = k->down;
            k->down = q;
        }
    }
}

void OutputMatrix(Matrix p)
{
    NodePtr k;
    for(int i=1;i<=p.m;i++)
    {
        k=p.rp[i];
        while(k!=NULL)
        {
        printf("%d %d %d\n",k->r,k->c,k->d);
        k=k->right;
        }
    }
}


//相加
void PlusMatrix(Matrix *a,Matrix *b)
{
    NodePtr k,j;
    for(int i=1;i<=rm;i++)
    {
        k=b->rp[i];
        while (k!=NULL)
        {
            j=(NodePtr)malloc(sizeof(Node));
            j->c=k->c;
            j->r=k->r;
            j->d=k->d;
            j->down=NULL;
            j->right=NULL;
            if(a->rp[j->r]==NULL)
            {
                a->rp[j->r]=j;
                a->t++;
            }
            else
            {
                NodePtr h=a->rp[j->r];
                NodePtr pre=h;
                while(h!=NULL&&h->c<j->c)
                {
                    pre=h;
                    h=h->right;
                }
                if(h!=NULL&&h->c==j->c)
                {
                    h->d=h->d+j->d;
                    if(h->d==0)
                    {
                        if(pre==h)
                        {
                            a->rp[j->r]=h->right;
                        }
                        else
                        {
                            pre->right=h->right;
                        }
                        a->t--;
                    }
                }
                else 
                {
                    if(pre==h)
                    {
                        j->right=a->rp[j->r];
                        a->rp[j->r]=j;
                    }
                    else
                    {
                        j->right=h;
                        pre->right=j;
                    }
                    a->t++;
                }
            }
            k=k->right;
        }
        
    }
}