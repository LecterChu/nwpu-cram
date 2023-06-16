#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>
#include<queue>

using namespace std;

const int maxn = 1005;
typedef struct node
{
    int val; // 存储对应的权值
    char data; // 存储对应的字符
    struct node *lchild;
    struct node *rchild;
}Node,*Tree;
bool vis[maxn];
Tree huff[maxn];
int n;
char str[maxn];
string code[maxn];
int Getmin(int length);
Tree GetHuffman();

Tree GetHuffman()
{
    Tree root;
    int len = n;
    int l,r;
    do
    {
        l = Getmin(len);
        r = Getmin(len);
        if(l==-1 || r==-1) break;
        huff[len]->data = '\0';
        huff[len]->val = huff[l]->val + huff[r]->val;
        huff[len]->lchild = huff[l];
        huff[len]->rchild = huff[r];
        len++;
    }while(l!=r);
    root = huff[l];
    return root;
}

int Getmin(int length)
{
    int k=-1,minn = 1000005;
    for(int i=0;i<length;i++)
    {
        if( vis[i] == false && huff[i]->val < minn )
        {
            minn = huff[i]->val;
            k = i;
        }
    }
    if(k!=-1) vis[k] = true;
    return k;
}

void Huffmancoding(Tree root,string str,int len)
{
    if(root == NULL) return ;
    if(root->data != '\0')
    {
        code[(int)(root->data)] = str;
    }
    str += "1";
    Huffmancoding(root->rchild,str,len+1);
    str[len] = '0';
    Huffmancoding(root->lchild,str,len+1);
}

int main()
{
    for(int i=0;i<maxn;i++)
    {
        huff[i] =(Tree)malloc(sizeof(Node));
        huff[i]->lchild = NULL;
        huff[i]->rchild = NULL;
        huff[i]->data = '\0';
        huff[i]->val = 0;
    }
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        cin>>huff[i]->data;
    }
    for(int i=0;i<n;i++)
    {
        scanf("%d",&huff[i]->val);
    }
    scanf("%s",str);
    Tree root = GetHuffman();
    Huffmancoding(root,"\0",0);
    int len  = strlen(str);
    for(int i=0;i<len;i++)
    {
        cout<<code[(int)str[i]];
    }
    printf("\n%s",str);
    return 0;
}