#include <stdio.h>
typedef enum {OK,ERROR,OVERFLOW} status;
status compare(int a,int b)
{
	if(a>b) return OK;
	else return ERROR;
}
void main() {
    if (compare(5,4)==OK)
	printf("5>4\n");
}