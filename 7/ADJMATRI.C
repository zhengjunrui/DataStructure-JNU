/***********************************************************************/
/*   The code creates Adjacency Matrix for the graphics                */
/*   Now the code can only deal with undirectional graphics,           */
/*   the other kind of graphics can created by modifying the function  */
/*   CreateUDN.It is very easy,so I do not provide it here	       */
/*   Author: John Lee                                                  */
/*   E-mail: paperbakup@163.com                                        */
/*   Date : 2004-11-7                                                  */
/***********************************************************************/
#include <limits.h>
#include <stdio.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTEX_NUM 20
typedef enum {DG,DN,UDG,UDN} GraphKind;
typedef struct {
	char vexs[MAX_VERTEX_NUM+1];
	int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int vexnum,arcnum;
	GraphKind kind;
}MGraph;
/*******************************************************************/
/*****Queue function,copy from our program coded some weeks ago*****/
#define MAX_LENGTH  50
typedef char ElemType;
typedef struct {
   ElemType *base;
   int front;
   int rear;
}SqQueue;
void initqueue(SqQueue *a)
{
	a->base=(ElemType *)malloc(sizeof(ElemType)* MAX_LENGTH);
	a->front=a->rear=0;
}
int SqQueueempty(SqQueue *a)
{
	if(a->rear==a->front) return 1;
	else return 0;
}
void enqueue(SqQueue *a, ElemType e)
{
	if((a->rear+1)%MAX_LENGTH==a->front) printf("The queue is full now!\n");
        else{
		a->base[a->rear]=e;
		a->rear=(a->rear+1)%MAX_LENGTH;

	}
}
void dequeue(SqQueue *a, ElemType *e)
{
	if(a->rear==a->front) printf("The SqQueue is NULL!\n");
	else{
		*e=a->base[a->front];
		a->front=(a->front+1)%MAX_LENGTH;
	}

}
/*****Queue function over!!!!!!************************************************/
void CreateUDN(MGraph *G){
	int i,j,k,weight;
	char v1,v2;
	printf("Please input the number of vetexes and arcs\n");
	scanf("%d%d",&G->vexnum,&G->arcnum);
	printf("Please input the name of vertex\n");
	flushall();
	for(i=0;i<G->vexnum;i++) scanf("%c",&G->vexs[i]);
	G->vexs[G->vexnum]='\0';
	for(i=0;i<G->vexnum;i++)
		for(j=0;j<G->vexnum;j++) G->arcs[i][j]=INT_MAX;
	printf("please input the arcs by its two vertexes\n");
	for(k=0;k<G->arcnum;k++){
		flushall();
		scanf("%c%c%d",&v1,&v2,&weight);
		i=strchr(G->vexs,v1)-G->vexs;
		j=strchr(G->vexs,v2)-G->vexs;
		G->arcs[i][j]=G->arcs[j][i]=weight;
	}
}
void CreateUDG(MGraph *G){

}
void CreateDN(MGraph *G){

}
void CreateDG(MGraph *G){

}
void CreateGraph(MGraph *G){
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
int FirstAdjVex(MGraph *G,int v){
	int j=0;
	while(j<G->vexnum){
		if(G->arcs[v][j]!=INT_MAX) break;
		j++;
	}
	if(j==G->vexnum) return -1;
	else return j;
}
int NextAdjVex(MGraph *G,int v,int w){
	int j;
	j=w+1;
	while(j<G->vexnum){
		if(G->arcs[v][j]!=INT_MAX) break;
		j++;
	}
	if(j==G->vexnum) return -1;
	else return j;
}
void DFS(MGraph *G,int v,int *visited){
	int w;
	visited[v]=TRUE;
	printf("%c ",G->vexs[v]);
	w=FirstAdjVex(G,v);
	while(w>=0){
		if(visited[w]==FALSE) DFS(G,w,visited);
		w=NextAdjVex(G,v,w);
	}
}
void DFSTras(MGraph *G){
	int visited[MAX_VERTEX_NUM];
	int i;
	for(i=0;i<G->vexnum;i++) visited[i]=FALSE;
	for(i=0;i<G->vexnum;i++){
		if(visited[i]!=1) DFS(G,i,visited);
	}
	printf("\n");
}
void BFSTras(MGraph *G){
	int i,v,w,visited[MAX_VERTEX_NUM];
	SqQueue Q;
	for(i=0;i<G->vexnum;i++) visited[i]=FALSE;
	initqueue(&Q);
	for(i=0;i<G->vexnum;i++){
		if(visited[i]==FALSE){
			visited[i]=TRUE;
			printf("%c ",G->vexs[i]);
			enqueue(&Q,i);
			while(!SqQueueempty(&Q)){
				dequeue(&Q,&v);
				w=FirstAdjVex(G,v);
				while(w>=0){
					if(visited[w]==FALSE){
						visited[w]=TRUE;
						printf("%c ",G->vexs[w]);
						enqueue(&Q,w);
					}
					w=NextAdjVex(G,v,w);
				}
			}/*end while empty*/
		}/*end if visited*/
	}/*end for*/
	printf("\n");
}
void main(){
	MGraph g1;
	int i,j;

	CreateGraph(&g1);
	for(i=0;i<g1.vexnum;i++){
		for(j=0;j<g1.vexnum;j++) printf("%7d ",g1.arcs[i][j]);
		printf("\n");
	}
	DFSTras(&g1);
	BFSTras(&g1);
	getch();
}