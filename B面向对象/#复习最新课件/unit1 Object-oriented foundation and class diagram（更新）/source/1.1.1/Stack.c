#include"Stack.h"   
#include<malloc.h>   
#include<stdlib.h>   
/*构造一个空栈*/  
Stack *InitStack()  
{  
    Stack *ps = (Stack *)malloc(sizeof(Stack));  
    if(ps!=NULL)  
    {  
        ps->top = NULL;  
        ps->size = 0;  
    }  
    return ps;  
}  
  
/*判定是否为空栈*/  
int IsEmpty(Stack *ps)  
{  
    if(ps->top == NULL && ps->size == 0)  
        return 1;  
    else  
        return 0;  
}  
  
/*返回栈大小*/  
int GetSize(Stack *ps)  
{  
    return ps->size;  
}  
  
/*元素入栈*/  
PNode Push(Stack *ps,Item item)  
{  
    PNode pnode = (PNode)malloc(sizeof(Node));  
    if(pnode != NULL)  
    {  
        pnode->data = item;  
        pnode->down = GetTop(ps,NULL);  
        ps->size++;  
        ps->top = pnode;  
          
    }  
    return pnode;  
}  
  
/*返回栈顶元素*/  
PNode GetTop(Stack *ps,Item *pitem)  
{  
    if(IsEmpty(ps)!=1&&pitem!=NULL)  
    {  
        *pitem = ps->top->data;  
    }  
    return ps->top;  
}  
  
  
/*元素出栈*/  
PNode Pop(Stack *ps,Item *pitem)  
{  
    PNode p = ps->top;  
    if(IsEmpty(ps)!=1&&p!=NULL)  
    {  
        if(pitem!=NULL)  
            *pitem = p->data;  
        ps->size--;  
        ps->top = ps->top->down;     
        free(p);  
    }  
    return ps->top;  
}  
  
/*销毁一个栈*/  
void DestroyStack(Stack *ps)  
{  
    if(IsEmpty(ps)!=1)  
        ClearStack(ps);  
    free(ps);  
}  
  
/*把栈置空*/  
void ClearStack(Stack *ps)  
{  
    while(IsEmpty(ps)!=1)  
    {  
        Pop(ps,NULL);  
    }  
}  
  
/*遍历栈并访问visit函数 */  
void StackTraverse(Stack *ps,void (*visit)())  
{  
    PNode p = ps->top;  
    int i = ps->size;  
    while(i--)  
    {  
        visit(p->data);  
        p = p->down;  
    }  
}  
