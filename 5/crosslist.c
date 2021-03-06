/***********************************************************************/
/*   The program demostrates Cross-List!                               */
/*   The code has been tested by a little data, so it can not ensure   */
/*   that it can deal with all case!!!.                                */
/*   The data for testing can find on Page 104 of the book	       */
/*   If you can not work for some cases, please report it to me        */
/*   Author: John Lee                                                  */
/*   E-mail: paperbakup@163.com                                        */
/*   Date : 2004-10-23                                                 */
/***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
typedef int ElemType;
typedef struct OLNode{
	int i,j;
	ElemType e;
	struct OLNode *right,*down;
}OLNode,*ptrNode;
typedef struct{
	OLNode **rowhead,**colhead;
	int col,row,total;
}CrossList;
void init(CrossList *m){
	int p;
	OLNode *q,*r,*rprior;
	printf("Please input quantity of elements,rows and columns:\n");
	scanf("%d%d%d",&m->total,&m->row,&m->col);
	m->rowhead=(OLNode**)malloc((m->row+1)*sizeof(OLNode*));
	m->colhead=(OLNode**)malloc((m->col+1)*sizeof(OLNode*));
	for(p=1;p<=m->row;p++) m->rowhead[p]=NULL;
	for(p=1;p<=m->col;p++) m->colhead[p]=NULL;
	printf("please input elment group by group:\n");
	for(p=1;p<=m->total;p++){
		q=(OLNode*)malloc(sizeof(OLNode));
		scanf("%d%d%d",&q->i,&q->j,&q->e);
		if(m->rowhead[q->i]==NULL||m->rowhead[q->i]->j>q->j){
			q->right=m->rowhead[q->i];
			m->rowhead[q->i]=q;
		}
		else{
			rprior=m->rowhead[q->i];
			for(r=m->rowhead[q->i]->right;r!=NULL&&r->j<=q->j;r=r->right) rprior=r;
			q->right=r;
			rprior->right=q;
		}
		if(m->colhead[q->j]==NULL||m->colhead[q->j]->i>q->i){
			q->down=m->colhead[q->j];
			m->colhead[q->j]=q;
		}
		else{
			rprior=m->colhead[q->j];
			for(r=m->colhead[q->j]->down;r!=NULL&&r->i<=q->i;r=r->down) rprior=r;
			q->down=r;
			rprior->down=q;
		}
	}/*end for p */
}
void displaybyrow(CrossList *m){
	int p;
	OLNode *q;
	for(p=1;p<=m->row;p++){
		q=m->rowhead[p];
		printf("row %d :",p);
		while(q!=NULL) {
			printf("%d\t",q->e);
			q=q->right;
		}
		printf("\n");
	}
}
void displaybycol(CrossList *m){
	int p;
	OLNode *q;
	for(p=1;p<=m->col;p++){
		q=m->colhead[p];
		printf("col %d :",p);
		while(q!=NULL) {
			printf("%d\t",q->e);
			q=q->down;
		}
		printf("\n");
	}
}
void insert_b(OLNode **L,OLNode *q){
	OLNode *p,*pre,*head;
	head=*L;
	p=head;
	pre=NULL;
	if(head==NULL){
		*L=q;
		q->down=NULL;
		return;
	}
	while(p!=NULL){
		if(p->i<q->i) {
			pre=p;
			p=p->down;
		}
		else break;
	}
	if(pre==NULL){
		q->down=p;
		*L=q;
	}
	else{
		q->down=p;
		pre->down=q;
	}
}
void del_b(OLNode **L,int i){
	OLNode *p,*pre,*head,*q;
	head=*L;
	p=head;
	pre=NULL;
	if(p->down==NULL) {
		*L=NULL;
		return;
	}
	while(p!=NULL){
		if(p->i!=i) {
			pre=p;
			p=p->down;
		}
		else break;
	}
	if(pre==NULL){
		*L=p->down;
	}
	else{
		pre->down=p->down;
	}
	free(p);
}
void add(CrossList *a,CrossList *b){
	OLNode *pa,*pb,*pre,*tmp,*q,***hl;
	int j,p;
	hl=(OLNode***)malloc(sizeof(OLNode**)*(a->col+1));
	for(j=1;j<=a->col;j++) *hl[j]=&a->colhead[j];
	for(p=1;p<=a->row;p++){
	   pa=a->rowhead[p];pb=b->rowhead[p];pre=NULL;
	   while(pb!=NULL){
		if(pa==NULL||pa->j>pb->j){
			q=(OLNode*)malloc(sizeof(OLNode));
			q->i=pb->i;q->j=pb->j;q->e=pb->e;
			if(pre==NULL){
				 a->rowhead[p]=q;
				 q->right=pa;
			}
			else{
				pre->right=q;
				q->right=pa;
				pre=q;
			}
			insert_b(&(a->colhead[q->j]),q);
                        pb=pb->right;
		}
		else if(pa->j<pb->j){
			pre=pa;
			pa=pa->right;
		}
		else{
			pa->e+=pb->e;
			if(pa->e==0){
				if(pre==NULL) {
					a->rowhead[p]=pa->right;
					pa=a->rowhead[p];
				}
				else{
					pre->right=pa->right;
					pa=pa->right;
				}
				del_b(&(a->colhead[pb->j]),p);
			}
                        pb=pb->right;
		}
	   }/*end while*/
	}/*end for p*/
}
void main(){
	CrossList a,b;
	printf("This program demostrates Cross-List!!!\n");
	init(&a);
	displaybyrow(&a);

	init(&b);
	add(&a,&b);
	displaybyrow(&a);
	getch();
}