/************************************************************************/
/*   The code search a record form a sequential list by its key word.  */
/*   Author: John Lee                                                   */
/*   E-mail: paperbakup@163.com                                         */
/*   Date : 2004-11-23                                                  */
/************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH  50
typedef int KeyType;
typedef struct{
    KeyType key;
    char* name;
    int PhoneNumber;
}RecordType;
typedef RecordType ElemType;
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
	printf("Please input the key of record:\n");
	for(i=1;i<=n;i++)
	{
		scanf("%d",&a->elem[i].key);
		/*******************************/
		/**   You can input the other **/
	        /**   field of RecoderType    **/
	        /*******************************/
		a->length++;
	}
}
void printlist(SqList *a)
{
	int i;
	printf("List is:");
	for(i=1;i<=a->length;i++)
	{
		printf("%d  ",a->elem[i].key);
	}
	printf("\n");
	printf("The length of list is:%d\n",a->length);
}


int search_seq(SqList *L,KeyType key){
       int i;
       L->elem[0].key=key;
       for(i=L->length;key!=L->elem[i].key;i--);
       return i; /*i>0,the position of record;i==0,no found*/
}
void main()
{
	KeyType key;
	int position;
	SqList a;

	initlist(&a);
	inputdata(&a,6);
	printlist(&a);

	printf("Please input a key:\n");
	scanf("%d",&key);
	position=search_seq(&a,key);

	if(position==0)
		printf("No found a key: (%d) from the list!\n",key);
	else
		printf("The position of the record is :%d\n",position);
	free(a.elem);
}

