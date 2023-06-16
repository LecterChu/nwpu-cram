#include"Stack.h"   
#include<stdio.h>   
void print(Item i)  
{  
    printf("该节点元素为%d\n",i);  
}  
main()  
{  
    Stack *ps = InitStack();  
    int i,item;  
  
    printf("0-9依次入栈并输出如下：\n");  
    for(i=0;i<10;i++)  
    {  
        Push(ps,i);  
        GetTop(ps,&item);  
        printf("%d ",item);  
    }  
      
    printf("\n从栈顶到栈顶遍历并对每个元素执行print函数：\n");  
    StackTraverse(ps,print);  
  
    printf("栈中元素依次出栈并输出如下：\n");  
    for(i=0;i<10;i++)  
    {  
        Pop(ps,&item);  
        printf("%d ",item);  
    }  
      
    ClearStack(ps);  
    if(IsEmpty(ps))  
        printf("\n将栈置空成功\n");  
    DestroyStack(ps);  
    printf("栈已被销毁\n");  
          
}  
