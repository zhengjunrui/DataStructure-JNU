#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH  50
typedef struct{
	int x,y;
}PosType;
typedef struct{
	int ord;
	PosType seat;
	int di;
}ElemType;
typedef struct {
   ElemType *base;
   ElemType *top;
   int stacksize; /*×î´óÈÝÁ¿*/
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
PosType nextpos(PosType pos,int direct) {
	switch(direct) {
		case 1: pos.x+=1;break;
		case 2: pos.y+=1;break;
		case 3: pos.x-=1;break;
		case 4: pos.y-=1;break;
	}
	return pos;
}
int mazepath(int maze[10][10],PosType start,PosType end,STACK* s){
	PosType curpos;
	int curstep=1;
	ElemType e;
	curpos=start;
	do{
		if(maze[curpos.x][curpos.y]==0){
			maze[curpos.x][curpos.y]=-1;/*Can't through once*/
			e.ord=curstep;e.seat=curpos;e.di=1;
			push(s,e);
			if(curpos.x==end.x&&curpos.y==end.y) return 1;
			curpos=nextpos(curpos,1);
			curstep++;
		}
		else{
			if(!stackempty(s)){
				pop(s,&e);
				while(e.di==4&&!stackempty(s)){
					maze[e.seat.x][e.seat.y]=-1;
					pop(s,&e);
				}
				if(e.di<4){
					e.di++;
					push(s,e);
					curpos=nextpos(e.seat,e.di);
				}
			}/*end if*/
		}
	}while(!stackempty(s));
	return 0;
}

void main()
{
	STACK s;
	static int maze[10][10]={{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
				 {-1, 0, 0,-1, 0, 0, 0,-1, 0,-1},
				 {-1, 0, 0,-1, 0, 0, 0,-1, 0,-1},
				 {-1, 0, 0, 0, 0,-1,-1, 0, 0,-1},
				 {-1, 0,-1,-1,-1, 0, 0, 0, 0,-1},
				 {-1, 0, 0, 0,-1, 0, 0, 0, 0,-1},
				 {-1, 0,-1, 0, 0, 0,-1, 0, 0,-1},
				 {-1, 0,-1,-1,-1, 0,-1,-1, 0,-1},
				 {-1,-1, 0, 0, 0, 0, 0, 0, 0,-1},
				 {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}};
	int i,j;
	PosType start,end;
	ElemType e;

	start.x=start.y=1;
	end.x=end.y=8;
      	initstack(&s);
	printf("----The program find a path from the maze-----\n");
	printf("Maze:\n");
	for(i=0;i<10;i++){
		for(j=0;j<10;j++) printf("%2d",maze[i][j]);
		printf("\n");
	}
	if(!mazepath(maze,start,end,&s))printf("No path for the maze\n");
	else{
		while(!stackempty(&s)){
		pop(&s,&e);
		printf("Step %d: (%d,%d)\t",e.ord,e.seat.x,e.seat.y);
		}
	}
	free(s.base);
}
