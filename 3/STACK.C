#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH  50
typedef int ElemType;
typedef struct {
   ElemType *base;
   ElemType *top;
   int stacksize; /*×î´óÈÝÁ¿*/
}STACK;
void initstack(STACK *a)
{
	a->stacksize=MAX_LENGTH;
	a->base=(ElemType *)malloc(sizeof(ElemType)* a->stacksize);
	a->top=a->base;
}
void push(STACK *a, ElemType e)
{
	if(a->top-a->base==a->stacksize) {
		a->base=(ElemType*)realloc(a->base,sizeof(ElemType)* a->stacksize*2);
		a->top=a->base+a->stacksize;
		a->stacksize*=2;
	}
	*a->top++=e;
}
void pop(STACK *a, ElemType *e)
{
	if(a->base==a->top) {
		printf("The stack is NULL!\n");
		return;
	}
	*e=*--a->top;
}
int stackempty(STACK *a)
{
	if(a->top==a->base) return 1;
	else return 0;
}
void main()
{
	STACK s;
      	ElemType e;
	initstack(&s);
	printf("----The program convert number from decimail to octonal-----\n");
	printf("please input a decimail number:\n");
	scanf("%d",&e);
	while(e) {
		push(&s,e%8);
		e=e/8;
	}
	printf("The result is :");
	while(!stackempty(&s))
	{
		pop(&s,&e);
		printf("%d",e);
	}
	printf("\n");
	free(s.base);
}
