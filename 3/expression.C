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
ElemType gettop(STACK *a)
{
	return *(a->top-1);
}
int stackempty(STACK *a)
{
	if(a->top==a->base) return 1;
	else return 0;
}
ElemType operate(ElemType a,ElemType theta,ElemType b){
	int aa,bb,cc;
	char ss[5];
	/*transfer from char to int*/
	ss[0]=a;
	ss[1]='\0';
	aa=atoi(ss);
	ss[0]=b;
	ss[1]='\0';
	bb=atoi(ss);
	switch(theta){
		case '+': cc=aa+bb; break;
		case '-': cc=aa-bb; break;
		case '*': cc=aa*bb; break;
		case '/': cc=aa/bb; break;
	}
	itoa(cc,ss,10);
	return ss[0];
}
int isdata(ElemType ch){
	if(ch>=48&&ch<=57) return 1;
	else return 0;
}
ElemType precede(ElemType a,ElemType b){
	static char table[7][7]={{'>','>','<','<','<','>','>'},
			   {'>','>','<','<','<','>','>'},
			   {'>','>','>','>','<','>','>'},
			   {'>','>','>','>','<','>','>'},
			   {'<','<','<','<','<','=','^'},
			   {'>','>','>','>','^','>','>'},
			   {'<','<','<','<','<','^','='}};
	int i,j;
	switch(a){
		case '+': i=0;break;
		case '-': i=1;break;
		case '*': i=2;break;
		case '/': i=3;break;
		case '(': i=4;break;
		case ')': i=5;break;
		case '#': i=6;break;
	}
	switch(b){
		case '+': j=0;break;
		case '-': j=1;break;
		case '*': j=2;break;
		case '/': j=3;break;
		case '(': j=4;break;
		case ')': j=5;break;
		case '#': j=6;break;
	}
	return table[i][j];
}
void main()
{
	STACK optr,opnd;
	ElemType ch,a,b,theta,tmp;
	initstack(&optr);
	initstack(&opnd);
	push(&optr,'#');
	printf("----The program calculate result of a expression.-----\n");
	printf("----The program can only deal with number 0~9.-----\n");
	printf("please input a expression:\n");
	ch=getchar();
	while(ch!='#'||gettop(&optr)!='#'){
		if(isdata(ch)) {push(&opnd,ch);ch=getchar();}
		else{
			switch(precede(gettop(&optr),ch)){
				case '<': push(&optr,ch);ch=getchar();break;
				case '=': pop(&optr,&tmp);ch=getchar();break;
				case '>':
					pop(&optr,&theta);
					pop(&opnd,&b);
					pop(&opnd,&a);
					push(&opnd,operate(a,theta,b));
					break;
			}/*end switch*/
		}/*end else*/
	}/*end while*/
	pop(&opnd,&tmp);
	printf("The result is :%c\n",tmp);
	free(optr.base);
	free(opnd.base);
}
