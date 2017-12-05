#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH  50
typedef int ElemType;
typedef struct {
   ElemType *elem; /*首地址*/
   int length; /*当前长度*/
   int listsize;/*最大长度*/
}SqList;
void initlist(SqList *a)
{
	a->listsize=MAX_LENGTH;
	a->elem=(ElemType *)malloc(sizeof(ElemType)* a->listsize);
	a->length=0;
}
void inputdata(SqList *a,int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		scanf("%d",&a->elem[i]);
		a->length++;
	}
}
void printlist(SqList *a)
{
	int i;
	printf("List is:");
	for(i=0;i<a->length;i++)
	{
		printf("%d  ",a->elem[i]);
	}
	printf("\n");
	printf("The length of list is:%d\n",a->length);
}
void listinsert(SqList *L,int i,ElemType e)
{
	int j;
	for(j=L->length;j>=i;j--) L->elem[j]=L->elem[j-1];
	L->elem[i-1]=e;
	L->length++;
}
void listdelete(SqList *L,int i)
{
	int j;
	for(j=i;j<L->length;j++) L->elem[j-1]=L->elem[j];
	L->length--;
}
void mergelist(SqList *a,SqList* b,SqList* c)
{
	int pa,pb,pc;
	pa=pb=pc=0;
	while(pa<a->length&&pb<b->length)
	{
		if(a->elem[pa]<=b->elem[pb]){
			c->elem[pc]=a->elem[pa];
			pa++;
			pc++;
		}
		else{
			c->elem[pc]=b->elem[pb];
			pb++;
			pc++;
		}
	}

	while(pa<a->length)
	{
	     c->elem[pc]=a->elem[pa];
	     pa++;
	     pc++;
	}
	while(pb<b->length)
	{
	     c->elem[pc]=b->elem[pb];
	     pb++;
	     pc++;
	}
	c->length=a->length+b->length;
}
void main()
{
	SqList a,b,c;
	initlist(&a);
	inputdata(&a,6);
	listinsert(&a,3,5);
	printlist(&a);
	/*listdelete(&a,5);
	printlist(&a);*/

	/*merge list*/
	/*initlist(&b);
	inputdata(&b,3);
	initlist(&c);
	mergelist(&a,&b,&c);
	printlist(&c);
	free(a.elem);
	free(b.elem);
	free(c.elem);*/
}

