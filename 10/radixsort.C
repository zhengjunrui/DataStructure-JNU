/************************************************************************/
/*   The code demostrates radix sort!					*/
/*   Author: John Lee                                                   */
/*   E-mail: paperbakup@163.com                                         */
/*   Date : 2004-12-19                                                  */
/************************************************************************/
#include <stdio.h>
#include <limits.h>
typedef struct{
	int key;
	int next;
}RecordType;
#define RADIX 10
#define MAX_NUM 1000
#define MAX_LEN 50
int front[RADIX];
int rear[RADIX];
void Distribute(RecordType r[],int w /*weight of interge*/){
	int j,p;
	for(j=0;j<RADIX;j++) front[j]=0;
	for(p=r[0].next;p!=0;p=r[p].next){
		j=r[p].key%(w*10)/w; /* No.i number of the key*/
		if(front[j]==0) front[j]=p;
		else r[rear[j]].next=p;
		rear[j]=p;
	}
}
void Collect(RecordType r[]){
	int j,t;
	for(j=0;front[j]==0;j++);
	r[0].next=front[j];
	t=rear[j];
	while(j<RADIX){
		for(j=j+1;j<RADIX&&front[j]==0;j++);
		if(front[j]!=0) {
			r[t].next=front[j];
			t=rear[j];
		}
	}
	r[t].next=0;
}
void main()
{
	/*key words saved by a Static list*/
	RecordType r[MAX_LEN]={{INT_MAX,1},{278,2},{109,3},{63,4},
			      {930,5},{589,6},{184,7},{505,8},{269,9},
			      {8,10},{83,0}};
	int i;
	printf("\nThe inputed records are:\n");
	i=0;
	while(r[i].next!=0){
		 i=r[i].next;
		 printf("%d\t",r[i].key);
	}
	for(i=1;i<MAX_NUM;i*=10){
		Distribute(r,i);
		Collect(r);
	}

	printf("\nThe sorted records are:\n");
	i=0;
	while(r[i].next!=0){
		 i=r[i].next;
		 printf("%d\t",r[i].key);
	}
	getch();
}
