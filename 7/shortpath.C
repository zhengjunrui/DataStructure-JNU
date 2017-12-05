/************************************************************************/
/*   The code finds the shortest path form a graph!                     */
/*   The source graph is saved by adjacency matrix.                     */
/*   Author: John Lee                                                   */
/*   E-mail: paperbakup@163.com                                         */
/*   Date : 2004-11-18                                                  */
/************************************************************************/
#include <limits.h>
#include <stdio.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTEX_NUM 20
#define SELECTED 0
#define UNSELECTED 1
typedef enum {DG,DN,UDG,UDN} GraphKind;
typedef struct {
	char vexs[MAX_VERTEX_NUM+1];
	int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int vexnum,arcnum;
	GraphKind kind;
}MGraph;

void CreateDN(MGraph *G){
	int i,j,k,weight;
	char v1,v2;

	G->kind=DN;
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
		G->arcs[i][j]=weight;
	}
}

void shortpath_DIJ(MGraph *G, int u, int path[]){
	int final[MAX_VERTEX_NUM], current_path_len[MAX_VERTEX_NUM];
	int mini,i,j,v;

	/*initializing... */
	for(i=0;i<G->vexnum;i++){
		final[i]=UNSELECTED;
		current_path_len[i]=G->arcs[u][i];
		if(current_path_len[i]<INT_MAX) path[i]=u;
		else path[i]=-1;
	}
	final[u]=SELECTED;
	current_path_len[u]=0;

	/*find shortest path*/
	for(i=1;i<G->vexnum;i++){
		mini=INT_MAX;
		for(j=0;j<G->vexnum;j++){
			if(final[j]==UNSELECTED&&current_path_len[j]<mini){
				mini=current_path_len[j];
				v=j;
			}
		}
		final[v]=SELECTED;
		for(j=0;j<G->vexnum;j++){
			if(final[j]==UNSELECTED&&G->arcs[v][j]!=INT_MAX
			  &&(mini+G->arcs[v][j]<current_path_len[j])){
				current_path_len[j]=mini+G->arcs[v][j];
				path[j]=v;
			}
		}
	}
}

void shortpath_FLD(MGraph *G, int path[MAX_VERTEX_NUM][MAX_VERTEX_NUM]){
	int final[MAX_VERTEX_NUM], current_path_len[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int mini,i,j,v;

	/*initializing... */
	for(i=0;i<G->vexnum;i++){
		for(j=0;j<G->vexnum;j++){
			current_path_len[i][j]=G->arcs[i][j];
			if(current_path_len[i][j]<INT_MAX) path[i][j]=i;
			else path[i][j]=-1;
		}
	}

	/*find shortest path*/
	for(v=0;v<G->vexnum;v++){
		for(i=0;i<G->vexnum;i++){
			for(j=0;j<G->vexnum;j++){
				if(current_path_len[i][v]+current_path_len[v][j]<current_path_len[i][j]&&
				   current_path_len[i][v]!=INT_MAX&&current_path_len[v][j]!=INT_MAX&&i!=j){
					current_path_len[i][j]=current_path_len[i][v]+current_path_len[v][j];
					path[i][j]=path[v][j];
				}
			}/*enf for j*/
		}/*end for i*/
	}/*end for v*/
}
void main(){
	MGraph g1;
	int i,j;
	int path1[MAX_VERTEX_NUM],path2[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

	CreateDN(&g1);
	shortpath_DIJ(&g1,0,path1);
	printf("The shortest path finded by Dijkstra algorithm is :\n");
	for(i=0;i<g1.vexnum;i++) printf("%d ",path1[i]);
	printf("\n");

	shortpath_FLD(&g1,path2);
	printf("The shortest path finded by FLOYD algorithm is :\n");
	for(i=0;i<g1.vexnum;i++) {
		for(j=0;j<g1.vexnum;j++) printf("%d ",path2[i][j]);
		printf("\n");
	}
	getch();
}