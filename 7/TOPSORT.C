/************************************************************************/
/*   Sorting by toplogical order                                        */
/*   The source graph is saved by adjacency list.                       */
/*   Author: John Lee                                                   */
/*   E-mail: paperbakup@163.com                                         */
/*   Date : 2004-11-17                                                  */
/************************************************************************/

/*********************************************************************/
/*****The code Creating adjacency list is copied from adjlist.c ******/
/*****The code for stack, from stack.c   *****************************/
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
void CreateDN(ADJGraph *G){
	int i,j,k,weight;
	char v1,v2,tmp[MAX_VERTEX_NUM];
	ArcNode *p;

	G->kind=DN;
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
	}
}

#define MAX_LENGTH  50
typedef int ElemType;
typedef struct {
   ElemType *base;
   ElemType *top;
   int stacksize;
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
/*****Copied code over!!!!!!*******************************************/

void CalculateInDegree(ADJGraph *g,int indegree[]){
	int i;
	ArcNode *ptr;

	for(i=0;i<g->vexnum;i++) indegree[i]=0;
	for(i=0;i<g->vexnum;i++){
		for(ptr=g->vexs[i].firstarc;ptr!=NULL;ptr=ptr->nextarc){
			indegree[ptr->adjvex]+=1;
		}
	}
}
int topsort(ADJGraph *g){
	ArcNode *ptr;
	int i,indegree[MAX_VERTEX_NUM],count;
	STACK s;

	CalculateInDegree(g,indegree);
	initstack(&s);
	for(i=0;i<g->vexnum;i++)
		if(indegree[i]==0) push(&s,i);
	count=0;
	while(!stackempty(&s)){
		pop(&s,&i);
		printf("%c, ",g->vexs[i].name);
		count+=1;
		for(ptr=g->vexs[i].firstarc;ptr!=NULL;ptr=ptr->nextarc){
			indegree[ptr->adjvex]-=1;
			if(indegree[ptr->adjvex]==0) push(&s,ptr->adjvex);
		}
	}
	if(count<g->vexnum) return 0;
	else return 1;
}
void main(){
	ADJGraph g1;
	ArcNode *ptr;
	int i,j,count;
	STACK s;

	CreateDN(&g1);
	printf("The topologic order sequence:\n");
	topsort(&g1);
	printf("\n");
/*	for(i=0;i<g1.vexnum;i++){
		printf("The vertex is:%c,adjvex:",g1.vexs[i].name);
		for(ptr=g1.vexs[i].firstarc;ptr!=NULL;ptr=ptr->nextarc)
			printf("%c\t",g1.vexs[ptr->adjvex].name);
		printf("\n");
	}*/
	getch();
}