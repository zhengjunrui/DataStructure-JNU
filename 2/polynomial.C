#include <stdio.h>
#include <stdlib.h>
typedef  struct {
	int coef;
	int expn;
}ElemType;
typedef struct node     /*结点类型定义*/
{
	ElemType data;               /*数据域*/
   	struct node *next; /*next为指针域，指向该结点的后继*/
}POLYNOMIAL;
void createpoly(POLYNOMIAL** phead,int n)
{
	int i;
	POLYNOMIAL *p;
	*phead=NULL;
	for(i=0;i<n;i++)
	{
	      p=(POLYNOMIAL*)malloc(sizeof(POLYNOMIAL));
	      printf("please input coef\n");
	      scanf("%d",&(p->data.coef));
	      printf("please input expn\n");
	      scanf("%d",&(p->data.expn));
	      p->next=*phead;
	      *phead=p;
	}
	p=(POLYNOMIAL*)malloc(sizeof(POLYNOMIAL));
	p->next=*phead;
	*phead=p;
}
void printpoly(POLYNOMIAL* phead)
{
	POLYNOMIAL* p;
	int j=0;
	p=phead->next;
	printf("p(x)=");
	while(p!=NULL){
		printf("(%d)x*exp(%d) + ", p->data.coef,p->data.expn);
		p=p->next;
		j++;
	}
	printf("\n");
}
void polyadd(POLYNOMIAL* La,POLYNOMIAL* Lb,POLYNOMIAL** Lc)
{
	POLYNOMIAL *pa,*pb,*pc;
	pa=La->next;
	pb=Lb->next;
	pc=La;
	*Lc=La;
	while(pa&&pb){
		if(pa->data.expn<pb->data.expn){
			pc->next=pa;pc=pa;pa=pa->next;
		}
		else if(pa->data.expn>pb->data.expn)
		{
			pc->next=pb;pc=pb;pb=pb->next;
		}
		else
		{
			pa->data.coef+=pb->data.coef;
			if(pa->data.coef!=0) {pc->next=pa;pc=pa;}
			pa=pa->next;pb=pb->next;
		}
	}
	pc->next=pa?pa:pb;
	free(Lb);
}
void main()
{
	POLYNOMIAL *poly1, *poly2, *poly3;
	createpoly(&poly1,4);
	printpoly(poly1);

	createpoly(&poly2,3);
	polyadd(poly1,poly2,&poly3);
	printpoly(poly3);
}