/************************************************************************/
/*   The code demostrates swapping Sort!				*/
/*   Author: John Lee                                                   */
/*   E-mail: paperbakup@163.com                                         */
/*   Date : 2004-12-13                                                  */
/************************************************************************/
#include <stdio.h>
#include <limits.h>
#define MAX_LENGTH  50
int Partition(int record[],int low ,int high){
       record[0]=record[low];
       while(low<high){
       		while(record[high]>=record[0]&&low<high) high--;
		record[low]=record[high];
       		while(record[low]<=record[0]&&low<high) low++;
		record[high]=record[low];
       }
	record[low]=record[0];
	return low;
}

void QSort(int record[],int low, int high){
	int pivotloc;
       if(low<high){
       		pivotloc=Partition(record,low,high);
		QSort(record,low,pivotloc-1);
		QSort(record,pivotloc+1,high);
	}
}
void QuickSort(int record[],int length){
	QSort(record,1,length);
}
void main()
{
	int record1[]={INT_MAX,49,38,65,97,76,13,27,49}; /*record[0] not used*/
	int length=8,i;

	printf("\nThe inputed records are:\n");
	for(i=1;i<=length;i++) printf("%d\t",record1[i]);

	QuickSort(record1,length);
	printf("\nThe sorted records are:\n");
	for(i=1;i<=length;i++) printf("%d\t",record1[i]);

	getch();
}
