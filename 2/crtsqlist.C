#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH  50
typedef int ElemType;
typedef struct {
   ElemType *elem; /*�׵�ַ*/
   int length; /*��ǰ����*/
   int listsize;/*��󳤶�*/
}SqList;
void main()
{
	SqList *a,b; /*����*/
	a=&b;
	a->listsize=MAX_LENGTH;
	a->elem=(ElemType *)malloc(sizeof(ElemType)* a->listsize);
	a->length=0;
        /*����3�����Ϊ��ʼ��*/

        /*��������*/
        a->elem[0]=12;
        a->length=a->length+1;
	a->elem[1]=34;
        a->length=a->length+1;
	a->elem[2]=56;
        a->length=a->length+1;

	/*�������*/
	printf("%d  %d   %d\n",a->elem[0],a->elem[1],a->elem[2]);
	free(a->elem);
}
/*������ѭ���������������ݣ������ڲ����Ӵ��������£����Դ������������ݣ�����
����������У�ÿ����һ�����ݣ���Ҫ�����������*/