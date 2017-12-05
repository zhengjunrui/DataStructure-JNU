/************************************************************************/
/*   The code creates minimum cost spanning tree by Prim algorithm.     */
/*   The source graph is saved by adjacency matrix.                     */
/*   Author: John Lee                                                   */
/*   E-mail: paperbakup@163.com                                         */
/*   Date : 2004-11-17                                                  */
/************************************************************************/
#include <limits.h>
#include <stdio.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTEX_NUM 20
#define SELECTED 0
#define UNSELECTED 1
#define CONNECTED  1
#define UNCONNECTED 0
#define USED        1
#define UNUSED      0
typedef enum {DG,DN,UDG,UDN} GraphKind;
typedef struct {
	char vexs[MAX_VERTEX_NUM+1];
	int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int vexnum,arcnum;
	GraphKind kind;
}MGraph;

void CreateUDN(MGraph *G){
	int i,j,k,weight;
	char v1,v2;

	G->kind=UDN;
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
int minimum(int lowcost[],int total){
	int mini,i,j;
	mini=INT_MAX;
	for(i=0;i<total;i++){
		if(lowcost[i]!=SELECTED&&lowcost[i]<mini){
			mini=lowcost[i];
			j=i;
		}
	}
	return j;
}
void minitree_prim(MGraph *G, int u){
	int i,j,k,lowcost[MAX_VERTEX_NUM],nearvex[MAX_VERTEX_NUM];
	for(i=0;i<G->vexnum;i++){
		lowcost[i]=G->arcs[i][u];
		nearvex[i]=u;
	}
	lowcost[u]=SELECTED;
	for(i=1;i<G->vexnum;i++){
		k=minimum(lowcost,G->vexnum);
		lowcost[k]=SELECTED;
		printf("[%c, %c]\n",G->vexs[k],G->vexs[nearvex[k]]);
		for(j=0;j<G->vexnum;j++){
			if(lowcost[j]!=SELECTED&&lowcost[j]>G->arcs[j][k]){
				lowcost[j]=G->arcs[j][k];
				nearvex[j]=k;
			}
		}
	}
}
void modifyconnect(int con1,int con2,int total,int connect[MAX_VERTEX_NUM+1][MAX_VERTEX_NUM+1]){
	int k;
	for(k=0;k<total;k++)
		if(connect[con2][k]==CONNECTED) connect[con1][k]=CONNECTED;
	connect[con2][total]=UNUSED;
}
int testconnect(int i,int j,int *con1,int *con2,int total,int connect[MAX_VERTEX_NUM+1][MAX_VERTEX_NUM+1]){
	int k;
	for(k=0;k<total;k++){
		if(connect[k][total]==USED&&connect[k][i]==CONNECTED) *con1=k;
		if(connect[k][total]==USED&&connect[k][j]==CONNECTED) *con2=k;
	}
	if(*con1==*con2) return 1;
	else return 0;

}
void miniedge(MGraph *G,int connect[MAX_VERTEX_NUM+1][MAX_VERTEX_NUM+1],int *m,int *n){
	int mini,i,j,con1,con2;
	mini=INT_MAX;
	for(i=0;i<G->vexnum;i++)
		for(j=0;j<G->vexnum;j++)
			if(G->arcs[i][j]<mini&&!testconnect(i,j,&con1,&con2,G->vexnum,connect)){
				 mini=G->arcs[i][j];
				 *m=i;
				 *n=j;
			}
	testconnect(*m,*n,&con1,&con2,G->vexnum,connect);/*get con1 and con2*/
	modifyconnect(con1,con2,G->vexnum,connect);

}
void minitree_Kruskal(MGraph *G){
	int i,j,m,n,connect[MAX_VERTEX_NUM+1][MAX_VERTEX_NUM+1];

	/*initializing . the matrix connected reorder which edges is connected*/
	for(i=0;i<G->vexnum;i++){
		connect[i][G->vexnum]=USED;/* A tag */
		for(j=0;j<G->vexnum;j++) {
			/*6 connected components,each includes a vertex*/
			if(j==i) connect[i][j]=CONNECTED;
			else connect[i][j]=UNCONNECTED;
		}
	}
	for(i=1;i<=G->vexnum-1;i++){/*select G->vexnum-1 edge for minitree*/
		miniedge(G,connect,&m,&n);
		printf("[%c, %c]\n",G->vexs[m],G->vexs[n]);
	}
}
void main(){
	MGraph g1;
	int i,j;

	CreateUDN(&g1);
	printf("The minimum spanning tree created by Prim algorithm is:\n");
	minitree_prim(&g1,0);
	printf("\nThe minimum spanning tree created by Kruskal algorithm is:\n");
	minitree_Kruskal(&g1);
	printf("\n");
	getch();
}