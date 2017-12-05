/************************************************************************/
/*   The code demostrates Heap Sorting, a kind of selection sorting!	*/
/*   Author: John Lee                                                   */
/*   E-mail: paperbakup@163.com                                         */
/*   Date : 2004-12-15                                                  */
/************************************************************************/
#include <stdio.h>
#include <limits.h>
#define MAX_LENGTH  50
void Adjust(int record[],int low ,int high){
       /***************************************************/
       /*  All records are in the heap,except record[1]   */
       /*  Destination: All records become one heap.      */
       /***************************************************/
       int i;
       record[0]=record[low];
       for(i=2*low;i<=high;i*=2){
		if(i<high&&record[i]<record[i+1]) i++;
       		if(record[0]>=record[i]) break;
       		record[low]=record[i];
       		low=i;
	}
	record[low]=record[0];
}
void HeapSort(int record[],int high){
       int i;
       for(i=high/2;i>0;i--) Adjust(record, i,high);
       for(i=high;i>1;i--){
       		record[0]=record[i];
       		record[i]=record[1];
       		record[1]=record[0];
       		Adjust(record, 1, i-1);
       }
}
void main()
{
	int record1[]={INT_MAX,49,38,65,97,76,13,27,49}; /*record[0] not used*/
	int length=8,i;

	printf("\nThe inputed records are:\n");
	for(i=1;i<=length;i++) printf("%d\t",record1[i]);

	HeapSort(record1,length);
	printf("\nThe sorted records are:\n");
	for(i=1;i<=length;i++) printf("%d\t",record1[i]);

	getch();
}
