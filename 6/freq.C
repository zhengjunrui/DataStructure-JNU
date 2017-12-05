#include <stdio.h>
char* table="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\
,!;.- \n";
void main(){
	FILE *fp;
	char ch,*pch;
	long *frequency;
	int pos,i;
	frequency=(long*)malloc(sizeof(long)*strlen(table));
	for(i=0;i<strlen(table);i++) frequency[i]=0;
	fp=fopen("data.txt","rt");
	while((ch=fgetc(fp))!=EOF){
		pch=strchr(table,ch);
		if(pch==NULL){
			printf("The text includes bad char... Terminated\n");
			exit(0);
		}
		pos=pch-table;
		frequency[pos]++;
	}
	for(i=0;i<strlen(table);i++){
		printf("%c: %d\t",table[i],frequency[i]);
		if((i+1)%8==0) printf("\n");
	}
	printf("\n");
	fclose(fp);
	getch();

}