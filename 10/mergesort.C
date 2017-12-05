/************************************************************************/
/*   The code demostrates merging sort!					*/
/*   Author: John Lee                                                   */
/*   E-mail: paperbakup@163.com                                         */
/*   Date : 2004-12-18                                                  */
/************************************************************************/
#include <stdio.h>
#include <limits.h>
#define CUR_LEN  8

void merge(int SR[],int TR[], int i, int m, int n){
       int k,j;

       k=i;
       j=m+1;
       while(i<=m&&j<=n){
       		if(SR[i]<=SR[j]) TR[k++]=SR[i++];
       		else TR[k++]=SR[j++];
       	}
       while(i<=m) TR[k++]=SR[i++];
       while(j<=n) TR[k++]=SR[j++];
}
void MergeSort(int SR[], int TR1[], int TR2[],int s, int t){
       int m;

       if(s==t) TR1[s]=SR[s];
       else{
       		m=(s+t)/2;
		MergeSort(SR, TR2,TR1, s,m);
		MergeSort(SR, TR2,TR1, m+1,t);
       		merge(TR2,TR1, s,m,t);
	}
}
void main()
{
	int record1[]={INT_MAX,49,38,65,97,76,13,27,49}; /*record[0] not used*/
	int length=CUR_LEN,i;
        int TR2[CUR_LEN+1];

	printf("\nThe inputed records are:\n");
	for(i=1;i<=length;i++) printf("%d\t",record1[i]);

	MergeSort(record1,record1,TR2,1,CUR_LEN);
	printf("\nThe sorted records are:\n");
	for(i=1;i<=length;i++) printf("%d\t",record1[i]);

	getch();
}
