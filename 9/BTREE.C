/************************************************************************/
/*   The code search a B-Tree.  	                                */
/*   The code has been tested by a little data, so it can not ensure    */
/*   that it can deal with all case!!!.                                 */
/*   If you can not work for some cases, please report it to me.        */
/*   Author: John Lee                                                   */
/*   E-mail: paperbakup@163.com                                         */
/*   Date : 2004-11-27                                                  */
/************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#define M 3
typedef char RecordType;
typedef struct BTNode{
	int keynum;
	struct BTNode *parent;
	int key[M+1];
	struct BTNode *ptr[M+1];
	RecordType *recptr[M+1];
}BTNode,*BTree;
typedef enum{FOUND,NOFOUND} Status;
typedef struct{
	BTNode *ptr;
	int     pos;
	Status  found_or_not;
}Result;

int search(BTNode *p,int keyword){
	/*if can not find the keyword, return the postion of left neighbor*/
	int low=1,high=p->keynum,mid,pos;

	while(low<=high){
		mid=(low+high)/2;
		if(p->key[mid]==keyword) return mid;
		else if(p->key[mid]>keyword) high=mid-1;
		else low=mid+1;
	}
	if(keyword>p->key[mid]) pos=mid;
	else pos=mid-1;
	return pos;
}
Result searchBT(BTree T,int keyword){
	BTNode *p,*q;
	Status tag;
	Result val;
	int i;

	p=T;
	q=NULL;
	tag=NOFOUND;
	i=0;
	while(p!=NULL&&tag==NOFOUND){
		i=search(p,keyword);
		if(p->key[i]==keyword) tag=FOUND;
		else {
			q=p;
			p=p->ptr[i];
		}
	}
	if(tag==FOUND) {
		val.ptr=p;
		val.pos=i;
		val.found_or_not=FOUND;
		}
	else {
		val.ptr=q;
		val.pos=i;
		val.found_or_not=NOFOUND;
	}
	return val;
}

void InsertInNode(BTNode *q, int pos,int keyword, BTNode *child){
	int i;

	if(q->keynum==M) {
		printf("The maximum key number is reached ,can not insert!\n");
		exit(0);
	}
	for(i=q->keynum;i>pos;i--){
		q->key[i+1]=q->key[i];
		q->ptr[i+1]=q->ptr[i];
		q->recptr[i+1]=q->recptr[i];
	}
	q->key[pos+1]=keyword;
	q->ptr[pos+1]=child;
	q->recptr[pos+1]=NULL;/* if using practically, is not null*/
	q->keynum++;
}
void split(BTNode *q, int *x,int pos,BTNode **ptr_ap){
	int i,j,s,keyword;
	int savekey[M+2];    /*Save the keywords(total M) of a node, and a key*/
	BTNode *saveptr[M+2];/*to insert to it.*/
	RecordType *saverecptr[M+2];
	BTNode *ap;

	i=j=0;
	keyword=*x;
	while(i<=M+1){
		if(i==pos+1) {
			savekey[i]=keyword;
			saveptr[i]=*ptr_ap;
			saverecptr[i]=NULL;
		}
		else {
			savekey[i]=q->key[j];
			saveptr[i]=q->ptr[j];
			saverecptr[i]=q->recptr[j];
			j++;
		}
		i++;
	}/*ready to split savekey to 2 Node:q,ap*/
	ap=(BTNode*)malloc(sizeof(BTNode));
	s=(M+1)/2+1; /* M+1 total records*/
	for(i=0;i<=s-1;i++){
		q->key[i]=savekey[i];
		q->ptr[i]=saveptr[i];
		q->recptr[i]=saverecptr[i];
	}
	q->keynum=s-1;
	for(i=s+1,j=1;i<=M+1;i++,j++){
		ap->key[j]=savekey[i];
		ap->ptr[j]=saveptr[i];
		ap->recptr[j]=saverecptr[i];
	}
	ap->parent=q->parent;
	ap->keynum=M+1-s;
	ap->ptr[0]=saveptr[s];
	*x=savekey[s];
	*ptr_ap=ap;
}
Status InsertBTree(BTree *ptr_T, int keyword, BTNode* q, int pos){
	int x;
	BTNode *ap,*root;

	ap=NULL;x=keyword;
	while(q!=NULL){
		if(q->keynum<M){/*Insert derectly*/
			InsertInNode(q,pos,x,ap);
			return;
		}
		else{
			split(q,&x,pos,&ap);
			q=q->parent;
			if(q!=NULL) pos=search(q,x);
		}/*end else*/
	}/*end while*/

	root=(BTNode*)malloc(sizeof(BTNode));
	root->keynum=1;
	root->ptr[0]=*ptr_T;
	root->ptr[1]=ap;
	root->key[1]=x;
	root->parent=NULL;
	(*ptr_T)->parent=root;
	ap->parent=root;

	*ptr_T=root;
}
Status SearchAndInsert(BTree *ptr_T, int keyword){
	BTNode *ptr_node_pos,*T;
	int  pos_in_node;
	Result val;

	int kdebug=0;

	T=*ptr_T;
	val=searchBT(T,keyword);
	if(val.found_or_not==FOUND){
		printf("The searching result is:\n Record:%d\tPosition:%d\n",val.ptr->key[val.pos],val.pos);
	}
	else{
		printf("No found! Insert record: %d.\n",keyword);
		InsertBTree(ptr_T, keyword, val.ptr, val.pos);
	}
	kdebug++;
}
void main(){
	BTree T=NULL;

	int keyword,i;
	int testrecord[]={24, 45,90,53,87,11,15};/*can modified*/
	int total=7;/*The number of records*/

        printf("The test data to create B-Tree is (can modified in the program) :\n");
	for(i=0;i<total;i++) printf("%d\t",testrecord[i]);
        printf("\n");

        /**** Create a B-tree by searching******************/
	for(i=0;i<total;i++)
		SearchAndInsert(&T,testrecord[i]);
	printf("Please input a key to search:\n");
	scanf("%d",&keyword);
	SearchAndInsert(&T,keyword);
	getch();
}