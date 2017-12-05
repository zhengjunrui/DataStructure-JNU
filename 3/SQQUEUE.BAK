#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH  50
typedef int ElemType;
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
void main()
{
	SqQueue s;
	ElemType e;
	int i;
	initqueue(&s);
	printf("----The program tests queue!!!-----\n");
	printf("please input 4 interger:\n");
       	for(i=0;i<4;i++) {
		scanf("%d",&e);
                enqueue(&s,e);
	}
	printf("Get element from the queue...\n");
	for(i=0;i<4;i++) {
		dequeue(&s,&e);
                printf("%d  ", e);
	}
	printf("\n");
	free(s.base);
}
