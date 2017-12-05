/************************************************************************/
/*   The code creates Adjacency List for the graphics and create a bi-  */
/*   nary tree to save the traverse result. So, you can get the shape   */
/*   of the binary tree by its pre-order sequence and in-order sequence */
/*   Then you can test the result.                                      */
/*   The data for testing can find on P.159.                            */
/*   Input as follow:                                                   */
/*   3                                                                  */
/*   13 13                                                              */
/*   ABCDEFGHIJKLM                                                      */
/*   AB1                                                                */
/*   AC2                                                                */
/*   AF3                                                                */
/*   ... ... And so on    						*/
/*   Author: John Lee                                                   */
/*   E-mail: paperbakup@163.com                                         */
/*   Date : 2004-11-13                                                  */
/************************************************************************/
#include <limits.h>
#include <stdio.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTEX_NUM 20
typedef enum {DG,DN,UDG,UDN} GraphKind;
typedef struct ArcNode{
	int adjvex;
	struct ArcNode *nextarc;
	int weight;
}ArcNode;
typedef struct {
	char name;
	ArcNode *firstarc;
}VNode;
typedef struct{
	VNode vexs[MAX_VERTEX_NUM];
	int vexnum,arcnum;
	int kind;
}ADJGraph;
/*********************************************************************/
/*****Binary tree function,copy from our program coded a week ago*****/
typedef char TreeElemType;
typedef struct BiTNode{
	TreeElemType data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

void PreOrderTrans(BiTree T){
	if(T!=NULL){
		printf("%c ",T->data);
		PreOrderTrans(T->lchild);
		PreOrderTrans(T->rchild);
	}
}
void InOrderTrans(BiTree T){
	if(T!=NULL){
		InOrderTrans(T->lchild);
		printf("%c ",T->data);
		InOrderTrans(T->rchild);
	}
}
/*****Binary Tree function over!!!!!!**********************************/

void CreateUDN(ADJGraph *G){
	int i,j,k,weight;
	char v1,v2,tmp[MAX_VERTEX_NUM];
	ArcNode *p;
	printf("Please input the number of vetexes and arcs\n");
	scanf("%d%d",&G->vexnum,&G->arcnum);
	printf("Please input the name of vertex\n");
	flushall();
	for(i=0;i<G->vexnum;i++) {
		scanf("%c",&(G->vexs[i].name));
		tmp[i]=G->vexs[i].name;/*for using strchr() to loacte a VERTEX*/
		G->vexs[i].firstarc=NULL;/*initialize head pointer*/
	}
	printf("please input the arcs by its two vertexes\n");
	for(k=0;k<G->arcnum;k++){
		flushall();
		scanf("%c%c%d",&v1,&v2,&weight);
		i=strchr(tmp,v1)-tmp;
		j=strchr(tmp,v2)-tmp;
		p=(ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex=j;
		p->weight=weight;
		p->nextarc=G->vexs[i].firstarc;
		G->vexs[i].firstarc=p;

		p=(ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex=i;
		p->weight=weight;
		p->nextarc=G->vexs[j].firstarc;
		G->vexs[j].firstarc=p;
	}
}
void CreateUDG(ADJGraph *G){

}
void CreateDN(ADJGraph *G){

}
void CreateDG(ADJGraph *G){

}
void CreateGraph(ADJGraph *G){
	printf("Please input the kind of graph(0-DG,1-DN,2_UDG,3-UDN):\n");
	scanf("%d",&G->kind);
	switch(G->kind){
		case DG:
			CreateDG(G);
			break;
		case UDG:
			CreateUDG(G);
			break;
		case DN:
			CreateDN(G);
			break;
		case UDN:
			CreateUDN(G);
			break;
		default:
			exit(0);

	}
}

void DFS(ADJGraph *G,int v,int *visited,BiTNode *t){
	int w,first;
	BiTNode *p,*q;
	ArcNode *ptr;

	visited[v]=first=TRUE;
	for(ptr=G->vexs[v].firstarc;ptr!=NULL;ptr=ptr->nextarc){
		w=ptr->adjvex;/*w is serial number of current vertex*/
		if(visited[w]==FALSE) {
			p=(BiTNode*)malloc(sizeof(BiTNode));
			p->data=G->vexs[w].name;
			p->lchild=p->rchild=NULL;
			if(first==TRUE){
				t->lchild=p;
				first=FALSE;
			}
			else q->rchild=p;
			q=p;
			DFS(G,w,visited,p);
		}/*end if visited*/
	}
}
void DFSTras(ADJGraph *G,BiTree *T){
	int visited[MAX_VERTEX_NUM];
	int i;
	BiTNode *p,*q;
	*T=NULL;
	for(i=0;i<G->vexnum;i++) visited[i]=FALSE;
	for(i=0;i<G->vexnum;i++){
		if(visited[i]==FALSE){
			p=(BiTNode*)malloc(sizeof(BiTNode));
			p->data=G->vexs[i].name;
			p->lchild=p->rchild=NULL;
			if(*T==NULL) *T=p;
			else q->rchild=p;
			q=p;
			DFS(G,i,visited,p);
		}
	}
}

void main(){
	ADJGraph g1;
	BiTree T;
	ArcNode *ptr;
	int i,j;
	CreateGraph(&g1);
	for(i=0;i<g1.vexnum;i++){
		printf("The vertex is:%c,adjvex:",g1.vexs[i].name);
		for(ptr=g1.vexs[i].firstarc;ptr!=NULL;ptr=ptr->nextarc)
			printf("%c\t",g1.vexs[ptr->adjvex].name);
		printf("\n");
	}
	DFSTras(&g1,&T);
	printf("The result of Pre-order transversing is:\n");
	PreOrderTrans(T);
	printf("\n");
	printf("The result of In-order transversing is:\n");
	InOrderTrans(T);
        printf("\n");
	getch();
}