/*该程序建立3个结点的链表，然后输出*/
#include <stdio.h>
#include <stdlib.h>
typedef  int ElemType;
typedef struct node     /*结点类型定义*/
{
	ElemType data;               /*数据域*/
   	struct node *next; /*next为指针域，指向该结点的后继*/
}JD;
void main()
{
	int j;
	JD *p,*phead,*ptail;

	/*建立第1个结点*/
 	p=(JD*)malloc(sizeof(JD));
	scanf("%d",&(p->data));
	ptail=p; /*在建立与其后继的连接关系时，需要该结点的地址，因此要存放在临时变量内*/
        phead=p;/*表头指针指向第1个结点*/

	/*建立第2个结点*/
 	p=(JD*)malloc(sizeof(JD));
	scanf("%d",&(p->data));
	ptail->next=p; /*前面建立的结点指向当前结点*/
	ptail=p;

	/*建立第3个结点*/
 	p=(JD*)malloc(sizeof(JD));
	scanf("%d",&(p->data));
	ptail->next=p; /*前面建立的结点指向当前结点*/
        p->next=NULL; /*表尾结点指针域为空*/

	/*输出*/
	 p=phead;
	 j=0;
	while(p!=NULL){
		printf("%d  ", p->data);
		p=p->next;
		j++;
	}
	printf("\nThe length of list is:%d\n",j);
}
