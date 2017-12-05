/************************************************************************/
/*   The code search a record  form a sorted list by its key word.      */
/*   Author: John Lee                                                   */
/*   E-mail: paperbakup@163.com                                         */
/*   Date : 2004-11-26                                                  */
/************************************************************************/
#include <stdio.h>
int search_bin(int record[],int total,int key){
       int low=0,high=total-1,mid;

       while(low<=high){
		mid=(low+high)/2;
		if(record[mid]==key) return mid+1;
		else if(record[mid]>key) high=mid-1;
		else low=mid+1;
	}
	return 0;
}
void main()
{
	int record[]={5,13,19,21,37,56,64,75,80,88,92};
	int key,position;

	printf("Please input the key:\n");
	scanf("%d",&key);

	position=search_bin(record,11/*total number of record*/,key);
	if(position==0)
		printf("No found a key: (%d) from the list!\n",key);
	else
		printf("The position of the recoder is :%d\n",position);
	getch();
}

