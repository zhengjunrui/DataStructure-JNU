/**************************************************/
/*   The program creats a non-static 2-dim array  */
/*   For demostration only
/*   Author: John Lee                             */
/*   Date : 2004-10-21                            */
/**************************************************/

#include <stdio.h>
#include <stdlib.h>
#define M 4
#define N 5
void main(){
	int **a,i,j;
	a=(int**)malloc(sizeof(int*)*M);
	a[0]=(int*)malloc(sizeof(int)*M*N);
	for(i=1;i<M;i++) a[i]=a[i-1]+N;
	for(i=0;i<M;i++)
		for(j=0;j<N;j++) a[i][j]=i*j;
	for(i=0;i<M;i++){
		for(j=0;j<N;j++) printf("%d\t",a[i][j]);
		printf("\n");
	}
}