/************************************************************************/
/*   The code demostrates Insertion Sort!				*/
/*   Author: John Lee                                                   */
/*   E-mail: paperbakup@163.com                                         */
/*   Date : 2004-12-12                                                  */
/************************************************************************/
#include <stdio.h>
#include <limits.h>
#define MAX_LENGTH  50
void InsertSort(int record[],int length){
       int i,j;
       for(i=2;i<=length;i++){
       		if(record[i]<record[i-1]){
       			record[0]=record[i];
       			record[i]=record[i-1];
       			for(j=i-2;record[0]< record[j];j--) record[j+1]=record[j];
       			record[j+1]=record[0];
       		}
       }
}
void BInsertSort(int record[],int length){
       int i,j,low,high,mid;
       for(i=2;i<=length;i++){
       		record[0]=record[i];
       		low=1;high=i-1;
       		while(low<=high){
       			mid=(low+high)/2;
			if(record[0]<record[mid]) high=mid-1;
       			else low=mid+1;
       		}
		for(j=i-1;j>=low;j--) record[j+1]=record[j];
		record[low]=record[0];
       	}
}
void ShellInsert(int record[],int length,int gap){
	int i,j;
	for(i=gap+1;i<=length;i++){
		if(record[i]<record[i-gap]){
			record[0]=record[i];
			for(j=i-gap;j>0&&record[0]<record[j];j=j-gap) record[j+gap]=record[j];
			record[j+gap]=record[0];
		}
	}
}
void ShellSort(int record[],int length){
	int dlta[MAX_LENGTH];
	int dlta_len,i,k;
	for(k=length/2,dlta_len=0;k>0;k=k/2) dlta[dlta_len++]=k;
	for(k=0;k<dlta_len;k++) ShellInsert(record,length,dlta[k]);
}
void main()
{
	int record1[]={INT_MAX,49,38,65,97,76,13,27,49}; /*record[0] not used*/
	int record2[]={INT_MAX,49,38,65,97,76,13,27,49}; /*record[0] not used*/
	int record3[]={INT_MAX,49,38,65,97,76,13,27,49}; /*record[0] not used*/
	int length=8,i;

	printf("\nThe inputed records are:\n");
	for(i=1;i<=length;i++) printf("%d\t",record1[i]);

	InsertSort(record1,length);
	printf("\nThe sorted records are:\n");
	for(i=1;i<=length;i++) printf("%d\t",record1[i]);

	BInsertSort(record2,length);
	printf("\nThe binary insertion sorted records are:\n");
	for(i=1;i<=length;i++) printf("%d\t",record2[i]);


	ShellSort(record3,length);
	printf("\nThe binary insertion sorted records are:\n");
	for(i=1;i<=length;i++) printf("%d\t",record3[i]);
	getch();
}
