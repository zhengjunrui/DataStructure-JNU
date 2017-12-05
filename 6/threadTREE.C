/***************************************************************/
/*    This program demostrates threaded binary tree            */
/*    Author:John Lee                                          */
/*    Date:2004-10-31                                          */
/***************************************************************/
#include <stdio.h>
typedef char TreeElemType;
typedef enum{LINK,THREAD}PointerTag;
typedef struct BiThreadTNode{
	TreeElemType data;
	PointerTag ltag,rtag;
	struct BiThreadTNode *lchild,*rchild;
}BiThreadTNode,*BiThreadTree;
BiThreadTNode *pre;
void CreateTree(BiThreadTree *T){
	char ch;
	BiThreadTree root;
	ch=getchar();
	if(ch=='#') *T=NULL;
	else{
		root=(BiThreadTree)malloc(sizeof(BiThreadTNode));
		*T=root;
		root->data=ch;
		root->ltag=LINK;
		root->rtag=LINK;
		CreateTree(&root->lchild);
		CreateTree(&root->rchild);
	}
}
void display(TreeElemType e){
	printf("%c\n",e);
}
void InThreading(BiThreadTree p){
	if(p!=NULL){
		InThreading(p->lchild);
		if(p->lchild==NULL){
			p->ltag=THREAD;
			p->lchild=pre;
		}
		if(pre->rchild==NULL) {
			pre->rtag=THREAD;
			pre->rchild=p;
		}
		pre=p;
		InThreading(p->rchild);
	}
}
void InOrderThreading(BiThreadTree *threadtree,BiThreadTree T){
	BiThreadTree p;
	p=(BiThreadTree)malloc(sizeof(BiThreadTNode));
	*threadtree=p;
	p->ltag=LINK;
	p->rtag=THREAD;
	p->rchild=p;
	if(T==NULL) p->lchild=p;
	else{
		p->lchild=T;
		pre=p;
		InThreading(T);
		pre->rchild=p;
		pre->rtag=THREAD;
		p->rchild=pre;
	}
}
void InOrderTrans_by_thread(BiThreadTree T,void (*visit)()){
	BiThreadTree p;
	p=T->lchild;
	while(p!=T){
		while(p->ltag==LINK) p=p->lchild;
		(*visit)(p->data);
		while(p->rtag==THREAD&&p->rchild!=T){
			p=p->rchild;
                        (*visit)(p->data);
		}
		p=p->rchild;
	}
}
void main(){
	BiThreadTree T,TThread;
	void (*p)();
	p=display;
	printf("Please input by preorder:\nfor example:ABC##DE#G##F###\n");
	CreateTree(&T);
	printf("In-order transverse :\n");
	InOrderThreading(&TThread, T);
	InOrderTrans_by_thread(TThread,p);
	getch();
}