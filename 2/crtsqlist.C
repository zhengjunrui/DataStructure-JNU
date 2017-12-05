#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH  50
typedef int ElemType;
typedef struct {
   ElemType *elem; /*首地址*/
   int length; /*当前长度*/
   int listsize;/*最大长度*/
}SqList;
void main()
{
	SqList *a,b; /*创建*/
	a=&b;
	a->listsize=MAX_LENGTH;
	a->elem=(ElemType *)malloc(sizeof(ElemType)* a->listsize);
	a->length=0;
        /*以上3条语句为初始化*/

        /*输入数据*/
        a->elem[0]=12;
        a->length=a->length+1;
	a->elem[1]=34;
        a->length=a->length+1;
	a->elem[2]=56;
        a->length=a->length+1;

	/*输出数据*/
	printf("%d  %d   %d\n",a->elem[0],a->elem[1],a->elem[2]);
	free(a->elem);
}
/*建议用循环来输入和输出数据，这样在不增加代码的情况下，可以处理任意多的数据；否则
如上面程序中，每处理一个数据，都要增加两条语句*/