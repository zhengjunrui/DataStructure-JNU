#include <stdio.h>
#define MAXSTRLEN 255
typedef unsigned char SString[MAXSTRLEN+1];
typedef enum{OK,ERROR,OVERFLOW,CUT,UNCUT}Status;
Status strassign(SString t)
{
	unsigned char c;
	t[0]=0;
	printf("Please input a string ended by ENTER\n");
	while((c=getchar())!='\n') {
		t[0]++;
		t[t[0]]=c;
		if(t[0]==MAXSTRLEN) {flushall();break;}
	}
}
Status concat(SString t,SString s1,SString s2)
{
	int i;
	if(s1[0]+s2[0]<=MAXSTRLEN) {
		t[0]=s1[0]+s2[0];
		for(i=1;i<=s1[0];i++) t[i]=s1[i];
		for(i=1;i<=s2[0];i++) t[i+s1[0]]=s2[i];
		return UNCUT;
	}
	else if(s1[0]<MAXSTRLEN) {
		for(i=1;i<=s1[0];i++) t[i]=s1[i];
		for(i=s1[0]+1;i<=MAXSTRLEN;i++) t[i]=s2[i-s1[0]];
                t[0]=MAXSTRLEN;
		return CUT;
	}
	else {
		for(i=0;i<=s1[0];i++) t[i]=s1[i];
		t[0]=MAXSTRLEN;
		return CUT;
	}
}
void strdisplay(SString s){
	int i;
	for(i=1;i<=s[0];i++) printf("%c",s[i]);
	printf("\n");
}
Status substr(SString sub,SString s,int pos, int len){
	int i;
	if(pos<1||pos>s[0]||len<0||len>s[0]-pos+1) return ERROR;
	for(i=1;i<=len;i++) sub[i]=s[pos-1+i];
	sub[0]=len;
	return OK;
}
int strlength(SString s){
	return s[0];
}
int strcompare(SString s,SString t){
	int i;
	for(i=1;i<=s[0]&&i<=t[0];i++){
		if(s[i]!=t[i]) return s[i]-t[i];
	}
	return s[0]-t[0];
}
void clearstring(SString s){
	s[0]=0;
}
int index(SString s,SString t,int pos)
{
	int m,n,i;
	SString sub;
	if(pos>0) {
		n=strlength(s);
		m=strlength(t);
		i=pos;
		while (i<=n-m+1){
			substr(sub,s,i,m);
			if(strcompare(sub,t)!=0) i++;
			else return i;
		}
	}
	return 0;
}
void main() {
	SString s1,s2,s3;
	int compare_result;
	int index_result;
	printf("This program for constant length sequtial string.\n");
	strassign(s1);
	strassign(s2);
	printf("Comparing s1 and s2 ...  :");
	compare_result=strcompare(s1,s2);
	if(compare_result==0) printf("s1==s2\n");
	else if(compare_result<0) printf("s1<s2\n");
	else printf("s1>s2\n");

	printf("Concating s1 and s2 ... :");
	concat(s3,s1,s2);
	printf("s1+s2=");
	strdisplay(s3);
	printf("The length of Concated string is %d\n",strlength(s3));

	printf("Get a substring  from s1...\n");
	if(OK==substr(s3,s1,3,3)) strdisplay(s3);
	else printf("error!!\n");

	printf("Testing Index ...\n");
	index_result=index(s1,s2,1);
	if(index_result!=0)
		printf("The position of substring is %d.\n",index_result);
	else printf("Do not find substring\n");
}
