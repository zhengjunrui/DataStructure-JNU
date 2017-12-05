/************************************************************************/
/*   The code creates a balanced binary tree.                           */
/*   The code has been tested by a little data, so it can not ensure    */
/*   that it can deal with all case!!!.                                 */
/*   The data for testing can find on Page 234 of the book.	        */
/*   If you can not work for some cases, please report it to me.        */
/*   Author: John Lee                                                   */
/*   E-mail: paperbakup@163.com                                         */
/*   Date : 2004-11-27                                                  */
/************************************************************************/
#include <stdio.h>
typedef int TreeElemType;
typedef struct AVLNode{
	TreeElemType data;
	int bf; /*balance factor*/
	struct AVLNode *lchild,*rchild;
}AVLNode,*AVLTree;
typedef enum{FOUND,NOFOUND} Status;
#define YES 1
#define NO  0
void R_Rotate(AVLTree *p){
	AVLNode *q,*T;

	T=*p;
	q=T->lchild;
	T->lchild=q->rchild;
	q->rchild=T;
	*p=q;
}

void L_Rotate(AVLTree *p){
	AVLNode *q,*T;

	T=*p;
	q=T->rchild;
	T->rchild=q->lchild;
	q->lchild=T;
	*p=q;
}

void LeftBalance(AVLTree *ptr_T){
	AVLNode *T,*lc,*rd;

	T=*ptr_T;
	lc=T->lchild;
	switch(lc->bf){
		case 1:
			T->bf=lc->bf=0;
			R_Rotate(ptr_T);
			break;
		case -1:
			rd=lc->rchild;
			switch(rd->bf){
				case 1:
					T->bf=-1;
					lc->bf=0;
					break;
				case 0:
					T->bf=0;
					lc->bf=0;
					break;
				case -1:
					T->bf=0;
					lc->bf=-1;
					break;

			}
			rd->bf=0;
			L_Rotate(&T->lchild);/*(&lc) is error,why?*/
			R_Rotate(ptr_T);
			break;
		default:
			printf("Balance factor error!!\n");
			exit(0);
	}
}

void RightBalance(AVLTree *ptr_T){
	AVLNode *T,*lc,*rd;

	T=*ptr_T;
	rd=T->rchild;
	switch(rd->bf){
		case -1:
			T->bf=rd->bf=0;
			L_Rotate(ptr_T);
			break;
		case 1:
			lc=rd->lchild;
			switch(lc->bf){
				case 1:
					T->bf=0;
					rd->bf=-1;
					break;
				case 0:
					T->bf=0;
					rd->bf=0;
					break;
				case -1:
					T->bf=1;
					rd->bf=0;
					break;

			}
			lc->bf=0;
			R_Rotate(&T->rchild);
			L_Rotate(ptr_T);
			break;
		default:
			printf("Balance factor error!!\n");
			exit(0);
	}
}
Status searchAVL(AVLTree *ptr_T,int key,AVLNode **ptr_key_pos, int *taller){
	AVLNode *p,*T;

	T=*ptr_T;
	if(T==NULL) {
		/***** No found, insert a node**********/
		p=(AVLNode*)malloc(sizeof(AVLNode));
		p->data=key;
		p->rchild=p->lchild=NULL;
		p->bf=0;
		*ptr_T=p;
		/***** Insert over*********************/
		*taller=YES;
		return NOFOUND;
	}
	else if(T->data==key) {
		*ptr_key_pos=T;
		return FOUND;
	}
	else if(key<T->data) {
		if(searchAVL(&T->lchild,key,ptr_key_pos,taller)==FOUND) return FOUND;
		if(*taller==YES){
			switch(T->bf){
				case 1:
					LeftBalance(ptr_T);
					*taller=NO;
					break;
				case 0:
					T->bf=1;
					*taller=YES;
					break;
				case -1:
					T->bf=0;
					*taller=NO;
					break;
			}/*end swith*/
		}
		return NOFOUND;
	}/*end if(key<T->data)*/
	else /*(key>T->data)*/ {
		if(searchAVL(&T->rchild,key,ptr_key_pos,taller)==FOUND) return FOUND;
		if(*taller==YES){
			switch(T->bf){
				case 1:
					T->bf=0;
					*taller=NO;
					break;
				case 0:
					T->bf=-1;
					*taller=YES;
					break;
				case -1:
					RightBalance(ptr_T);
					*taller=NO;
					break;
			}/*end swith*/
		}
		return NOFOUND;
	}/*end else key>T->data*/
}

void PreOrderTrans(AVLTree T){
	if(T!=NULL){
		printf("%d ",T->data);
		PreOrderTrans(T->lchild);
		PreOrderTrans(T->rchild);
	}
}
void InOrderTrans(AVLTree T){
	if(T!=NULL){
		InOrderTrans(T->lchild);
		printf("%d ",T->data);
		InOrderTrans(T->rchild);
	}
}

void main(){
	AVLTree T=NULL; /* Initailizing is necessary*/
	AVLNode *position;
	int key,i,taller;
	int record[]={13,24,37,90,53};/*can finded in Page 234*/
	int total=5;/*The number of records*/

        printf("The test data is (can modified in the program) :\n");
        for(i=0;i<total;i++) printf("%d\t",record[i]);
        printf("\n");

        /**** Create a AVL tree by searching******************/
	for(i=0;i<total;i++)
		searchAVL(&T,record[i],&position,&taller);

        /********Verify the result of creating BST*****/
	printf("Pre-order transverse:\n");
	PreOrderTrans(T);
	printf("\n");
	printf("In-order transverse:\n");
	InOrderTrans(T);
	printf("\n");
	printf("Please input a key to search:\n");
	scanf("%d",&key);
	if(searchAVL(&T,key,&position,&taller)==NOFOUND)
		printf("No found a key: (%d) from the Tree, Insert it!\n",key);
	else
		printf("The record is :%d\n",position->data);
	/********Verify over!!!************************/

	getch();
}