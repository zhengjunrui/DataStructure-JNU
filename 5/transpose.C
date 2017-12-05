#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
typedef int ElemType;
typedef struct{
	int i,j;
	ElemType e;
}triple;
typedef struct{
	triple data[MAXSIZE+1];
	int col,row,total;
}TSMatrix;
void init(TSMatrix *m){
	int n,p,max_col=0,max_row=0;
	printf("Please input quantity of element:\n");
	scanf("%d",&n);
	printf("please input elment group by group:\n");
	for(p=1;p<=n;p++){
		scanf("%d",&m->data[p].i);
		scanf("%d",&m->data[p].j);
		scanf("%d",&m->data[p].e);
		if(m->data[p].i>max_row) max_row=m->data[p].i;
		if(m->data[p].j>max_col) max_col=m->data[p].j;
	}
	m->col=max_col;
	m->row=max_row;
	m->total=n;
}
void display(TSMatrix *m){
	int p;
	printf("i\tj\tvalue\n");
	for(p=1;p<=m->total;p++){
		printf("%d\t%d\t%d\n",m->data[p].i,m->data[p].j,m->data[p].e);
	}
}
void transpose(TSMatrix *m,TSMatrix *t){
	int col,p,q=1;
	t->col=m->row;
	t->row=m->col;
	t->total=m->total;
	if(t->total>0){
		for(col=1;col<=m->col;col++)
			for(p=1;p<=m->total;p++)
				if(m->data[p].j==col){
					t->data[q].i=m->data[p].j;
					t->data[q].j=m->data[p].i;
					t->data[q].e=m->data[p].e;
					q++;
				}
	}
}
void fasttranspose(TSMatrix *m,TSMatrix *t){
	int col,p,q;
	int *num,*cpot;
	num=(int*)malloc(sizeof(int)*m->col);
	cpot=(int*)malloc(sizeof(int)*m->col);
	t->col=m->row;
	t->row=m->col;
	t->total=m->total;
	if(t->total>0){
		for(col=1;col<=m->col;col++) num[col]=0;
		for(p=1;p<=m->total;p++) num[m->data[p].j]++;
		cpot[1]=1;
		for(col=2;col<=m->col;col++) cpot[col]=cpot[col-1]+num[col-1];
		for(p=1;p<=m->total;p++){
			col=m->data[p].j;
			q=cpot[col];
			t->data[q].i=m->data[p].j;
			t->data[q].j=m->data[p].i;
			t->data[q].e=m->data[p].e;
			cpot[col]++;
		}
	}
}
void main(){
	TSMatrix a,b;
	printf("This program demostrates array!!!\n");
	init(&a);
	display(&a);
	transpose(&a,&b);
	printf("Transposed Matrix is:\n");
	display(&b);
	fasttranspose(&a,&b);
	printf("Fast Transposed Matrix is:\n");
	display(&b);
	getch();
}