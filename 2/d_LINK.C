#include <stdio.h>
#include <stdlib.h>
typedef  int ElemType;
typedef struct node     /*结点类型定义*/
{
	ElemType data;               /*数据域*/
   	struct node *next; /*next为指针域，指向该结点的后继*/
        struct node* prior;
}JD;
JD* initlist()/*建立仅含头结点的双向链表*/
{
      	JD* p;
    	p=(JD*)malloc(sizeof(JD));
	p->next=p;
        p->prior=p;
        return p;
}
void insertlist(JD* L,int i, ElemType e)
{
	int j;
	JD *p,*q;
	j=1;
        p=L->next; /*越过头结点*/
	while(p!=L&&j<i) {p=p->next; j++;}/*找到插入位置*/
        q=(JD*)malloc(sizeof(JD));
        q->data=e;
        q->next=p;
	q->prior=p->prior;
        p->prior->next=q;
        p->prior=q;
}
void inputdata(JD* L,int n)
{
	int i;
	ElemType e;
	for(i=0;i<n;i++)
	{
	      scanf("%d",&e);
	      insertlist(L,1,e);
	}
}
void printlist(JD* phead)
{
	JD* p;
	int j=0;
	p=phead->next;
	printf("This list is:");
	while(p!=phead){
		printf("%d  ", p->data);
		p=p->next;
		j++;
	}
	printf("\nThe length of list is:%d\n",j);
}

void dellist(JD* L,int i)
{
	JD *p;
	int j=1;
	p=L->next;
	while(p!=L&&j<i) {p=p->next; j++;}/*找到删除位置*/
	p->prior->next=p->next;
        p->next->prior=p->prior;
        free(p);
}

void main()
{
	JD *list1;
        list1=initlist();
        inputdata(list1,5);
	printlist(list1);
	insertlist(list1,4,456);
	printlist(list1);
	dellist(list1,3);
	printlist(list1);

}
