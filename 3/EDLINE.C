#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH  50
typedef char ElemType;
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
int stackcurrentsize(STACK *a)
{
	return a->top-a->base;
}
void copytodatazone(STACK *a,ElemType datazone[20][81],int totalline)
{
	int i;
	i=stackcurrentsize(a);
	datazone[totalline][i]='\0';
	while(!stackempty(a)) pop(a, datazone[totalline]+--i);

}
void printdatazone(ElemType datazone[20][81],int totalline){
	int i;
	for(i=0;i<totalline;i++) printf("%s\n",datazone[i]);
}
void main()
{
	STACK s;
	ElemType ch,e;
	ElemType result[20][81];
	int i,totalline;
	initstack(&s);
	totalline=0;
	printf("----The program is for editing line by line-----\n");
	printf("please input:\n");
	ch=getchar();
	while(ch!='^'){
		while(ch!='^'&&ch!='\n'){
			switch(ch){
				case '#': pop(&s,&e); break;
				case '@': while(!stackempty(&s)) pop(&s,&e); break;
				default: push(&s,ch);
			}
			ch=getchar();
		}
		copytodatazone(&s,result,totalline);
		totalline+=1;
		if(ch!='^') ch=getchar();
	}
	printf("The result is\n");
	printdatazone(result,totalline);
	free(s.base);
}
