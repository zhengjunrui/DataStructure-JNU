#include <stdio.h>
#include <stdlib.h>
typedef  int ElemType;
typedef struct node     /*结点类型定义*/
{
	ElemType data;               /*数据域*/
   	struct node *next; /*next为指针域，指向该结点的后继*/
}JD;
void createlist(JD** phead,int n)
{
	int i;
	JD *p;
	*phead=NULL;
	for(i=0;i<n;i++)
	{
	      p=(JD*)malloc(sizeof(JD));
	      scanf("%d",&(p->data));
	      p->next=*phead;
	      *phead=p;
	}
	p=(JD*)malloc(sizeof(JD));
	p->next=*phead;
	*phead=p;
}
void printlist(JD* phead)
{
	JD* p;
	int j=0;
	p=phead->next;
	printf("This list is:");
	while(p!=NULL){
		printf("%d  ", p->data);
		p=p->next;
		j++;
	}
	printf("\nThe length of list is:%d\n",j);
}
JD* getitem(JD *L,int i)
{
	int j=1;
	L=L->next;
	while(L!=NULL&&j<i){
		L=L->next;
		j++;
	}
	return L;
}
void insertbefore(JD* L,int i, ElemType e)
{
	JD *p,*s;
	ElemType tmp;
	p=getitem(L,i);
	s=(JD*)malloc(sizeof(JD));
	s->data=e;
	s->next=p->next;
	p->next=s;
	tmp=p->data;
	p->data=s->data;
	s->data=tmp;
}
void dellist(JD* L,int i)
{
	JD *p,*s;
	p=getitem(L,i-1);
	s=p->next;
	p->next=s->next;
	free(s);
}
void mergelist(JD* La,JD* Lb,JD** Lc)
{
	JD *pa,*pb,*pc;
	pa=La->next;
	pb=Lb->next;
	pc=La;
	*Lc=La;
	while(pa&&pb){
		if(pa->data<=pb->data){
			pc->next=pa;pc=pa;pa=pa->next;
		}
		else{
			pc->next=pb;pc=pb;pb=pb->next;
		}
	}
	pc->next=pa?pa:pb;
	free(Lb);
}
void destroylist(JD *L)
{
	JD *p;
	while(L!=NULL)
	{
		p=L;
		L=L->next;
		free(p);
	}
}
void main()
{
	JD *list1, *list2, *list3;
	createlist(&list1,5);
	printlist(list1);
	list2=getitem(list1,3);
	printf("The search result is :%d\n",list2->data);
	insertbefore(list1,4,456);
	printlist(list1);
	dellist(list1,3);
	printlist(list1);

	/*test mergerlist*/
/*	createlist(&list2,3);
	mergelist(list1,list2,&list3);
	printlist(list3);*/

/*	destroylist(list1);*/
}
