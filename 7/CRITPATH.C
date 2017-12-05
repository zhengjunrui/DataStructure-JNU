/************************************************************************/
/*   Find critical path.                                                */
/*   The source graph is saved by adjacency list.                       */
/*   The program is tested using the graph on Page 186.                 */
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
int toplogicorder(ADJGraph *g,int ve[],STACK *s2){
	ArcNode *ptr;
	int i,indegree[MAX_VERTEX_NUM],count;
	STACK s;

	CalculateInDegree(g,indegree);
	initstack(&s);
	for(i=0;i<g->vexnum;i++){
		if(indegree[i]==0) push(&s,i);
		ve[i]=0;

	}
	count=0;
	while(!stackempty(&s)){
		pop(&s,&i);
		/*printf("%c, ",g->vexs[i].name);*/
		count+=1;
		push(s2,i);
		for(ptr=g->vexs[i].firstarc;ptr!=NULL;ptr=ptr->nextarc){
			indegree[ptr->adjvex]-=1;
			if(indegree[ptr->adjvex]==0) push(&s,ptr->adjvex);
			if(ve[i]+ptr->weight>ve[ptr->adjvex]) ve[ptr->adjvex]=ve[i]+ptr->weight;
		}
	}
	if(count<g->vexnum) return 0;
	else return 1;
}
void criticalpath(ADJGraph *g){
	int i,ee,el;
	int ve[MAX_VERTEX_NUM],vl[MAX_VERTEX_NUM];
	STACK s2;
	ArcNode *ptr;

	initstack(&s2);
	if(!toplogicorder(g,ve,&s2)) exit(0);
	for(i=0;i<g->vexnum;i++) vl[i]=ve[g->vexnum-1];
	while(!stackempty(&s2)){
		pop(&s2,&i);
		for(ptr=g->vexs[i].firstarc;ptr!=NULL;ptr=ptr->nextarc){
			if(vl[i]>vl[ptr->adjvex]-ptr->weight) vl[i]=vl[ptr->adjvex]-ptr->weight;
		}
	}
	for(i=0;i<g->vexnum;i++){
		for(ptr=g->vexs[i].firstarc;ptr!=NULL;ptr=ptr->nextarc){
			ee=ve[i];
			el=vl[ptr->adjvex]-ptr->weight;
			if(ee==el)
				printf("<%c, %c>\n",g->vexs[i].name,g->vexs[ptr->adjvex].name);
		}
	}
}
void main(){
	ADJGraph g1;
	ArcNode *ptr;
	int i,j,count;
	STACK s;

	CreateDN(&g1);
	printf("The critical path is :\n");
	criticalpath(&g1);
	getch();
}