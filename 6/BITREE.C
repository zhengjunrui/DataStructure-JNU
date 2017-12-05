/************************************************************************/
/*  		The code demonstrate the binary tree!			*/
/*   									*/
/*   Author: John Lee                                                   */
/*   E-mail: paperbakup@163.com                                         */
/*   Date : 2004-11	                                                */
/*   Modified 2006-04-21, add CreateTreeAfterOrder() and PrintTree();	*/
/************************************************************************/
#include <stdio.h>
typedef char TreeElemType;
typedef struct BiTNode{
	TreeElemType data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
/*******************************************************************/
/*****Stack function,copy from our program coded some weeks ago*****/
/*Stack routinue is only for Non-recursive Traversal               */
#define MAX_LENGTH  50
typedef BiTree ElemType;
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
int gettop(STACK *a,ElemType *e){
	if(a->top==a->base) return 0;
	else{
		*e=*(a->top-1);
		return 1;
	}
}
int stackempty(STACK *a)
{
	if(a->top==a->base) return 1;
	else return 0;
}
/*****Stack function over!!!!!!************************************************/
void CreateBiTree(BiTree *T){
	char ch;
	BiTree root;
	ch=getchar();
	if(ch=='#') *T=NULL;
	else{
		root=(BiTNode*)malloc(sizeof(BiTNode));
		*T=root;
		root->data=ch;
		CreateBiTree(&root->lchild);
		CreateBiTree(&root->rchild);
	}
}
void PrintPreOrder(BiTree T, int iIndent){
	int i;

	for(i=0;i<iIndent;i++) 	printf(" ");
	printf("%c\n",T->data);
	if(T->lchild!=NULL&&T->rchild!=NULL){
		PrintPreOrder(T->lchild, iIndent+1);
		PrintPreOrder(T->rchild, iIndent+1);
	}
	else if(T->lchild==NULL&&T->rchild!=NULL) {
		printf("\n");
		PrintPreOrder(T->rchild, iIndent+1);
	}
	else if(T->lchild!=NULL&&T->rchild==NULL) {
		PrintPreOrder(T->lchild, iIndent+1);
	}
}

void PrintTree(BiTree T){
	int iIndent=0;
	if(T==NULL) {
		printf("T is NULL\n");
		return;
	}
	PrintPreOrder(T, iIndent);
}

BiTree CreateTreeAfterOrder(){
	char ch;
	BiTNode *pLeftChild,*pRightChild,*root;

	ch=getchar();
	if(ch=='#') return NULL;
	else{
		pLeftChild=CreateTreeAfterOrder();
		pRightChild=CreateTreeAfterOrder();
		ch=getchar();
                root=(BiTNode*)malloc(sizeof(BiTNode));
		root->data=ch;
		root->lchild=pLeftChild;
		root->rchild=pRightChild;
		return root;
	}
}

void display(TreeElemType e){
	printf("%c\n",e);
}
void PreOrderTrans(BiTree T,void (*visit)()){
	if(T!=NULL){
		(*visit)(T->data);
		PreOrderTrans(T->lchild,visit);
		PreOrderTrans(T->rchild,visit);
	}
}
void InOrderTrans1(BiTree T,void (*visit)()){
	if(T!=NULL){
		InOrderTrans1(T->lchild,visit);
                (*visit)(T->data);
		InOrderTrans1(T->rchild,visit);
	}
}
void InOrderTrans2(BiTree T,void (*visit)()){
	STACK s;
	BiTree p;
	initstack(&s);
	push(&s,T);
	while(!stackempty(&s)){
		while(gettop(&s,&p)&&p) push(&s,p->lchild);
		pop(&s,&p);
		if(!stackempty(&s)){
			pop(&s,&p);
			(*visit)(p->data);
			push(&s,p->rchild);
		}
	}
}
void InOrderTrans3(BiTree T,void (*visit)()){
	STACK s;
	BiTree p=T;
	initstack(&s);
	while(p!=NULL||!stackempty(&s)){
		if(p!=NULL) {
			push(&s,p);
			p=p->lchild;
		}
		else{
			pop(&s,&p);
			(*visit)(p->data);
			p=p->rchild;
		}
	}
}
void main(){
	BiTree T;
	void (*p)();
	p=display;

	printf("Please input some charecters to create tree by preOrderTraversal:\n");
	printf("A example from p131 of the book:abc##de#g##f###\n");
	printf("Another example p129:-+a##*b##-c##d##/e##f##\n");
	/*CreateBiTree(&T);
	PrintTree(T);*/
	printf("Please input some charecters to create tree by AfterOrderTraversal:\n");
	printf("A example from p131 of the book:$$$##c$$#$##ge$##fdb#a\n");
	printf("Another example p129:$$$##a$$##b$$##c$##d-*+$$##e$##f/-\n");

	T=CreateTreeAfterOrder();
        printf("the resutl printed:\n");
	PrintTree(T);
	/*printf("Pre-order transverse:\n");
	PreOrderTrans(T,p);
	printf("In-order transverse 1:\n");
	InOrderTrans1(T,p);
	printf("In-order transverse 2:\n");
	InOrderTrans2(T,p);
	printf("In-order transverse 3:\n");
	InOrderTrans3(T,p);*/
	getch();
}