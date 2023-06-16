#ifndef Stack_H   
#define Stack_H   
  
typedef int Item;  
typedef struct node * PNode;  
/*定义栈节点类型*/  
typedef struct node  
{  
    Item data;  
    PNode down;  
}Node;  
/*定义栈类型*/  
typedef struct stack  
{  
    PNode top;  
    int size;  
}Stack;  
/*构造一个空栈*/  
Stack *InitStack();  
  
/*销毁一个栈*/  
void DestroyStack(Stack *ps);  
  
/*把栈置空*/  
void ClearStack(Stack *ps);  
  
/*判定是否为空栈*/  
int IsEmpty(Stack *ps);  
  
/*返回栈大小*/  
int GetSize(Stack *ps);  
  
/*返回栈顶元素*/  
PNode GetTop(Stack *ps,Item *pitem);  
  
/*元素入栈*/  
PNode Push(Stack *ps,Item item);  
  
/*元素出栈*/  
PNode Pop(Stack *ps,Item *pitem);  
  
/*遍历栈并访问visit函数*/  
void StackTraverse(Stack *ps,void (*visit)());  
  
#endif  
