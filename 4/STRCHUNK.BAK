#include <stdio.h>
typedef struct {
	char *ch;
	int length;
} HString;
typedef enum{OK,ERROR,OVERFLOW,CUT,UNCUT}Status;
Status strassign(HString *t)
{
	int i,n;
	if(t->ch) free(t->ch);
	printf("Please input the length of string:\n");
	scanf("%d",&n);
	if(n<1) {t->ch=NULL;t->length=0;}
	else{
		t->ch=(char*)malloc(n*sizeof(char));
		if(t->ch==NULL) exit(OVERFLOW);
		printf("Please input the string ended by ENTER\n");
		flushall();
		for(i=0;i<n;i++) t->ch[i]=getchar();
		t->length=n;
		flushall();
	}
	return OK;
}
Status strassignError(HString *t, char *chars)
{
	int i,j;
	char *c;
	/*if(t->ch) free(t->ch);*/
	for(i=0,c=chars; *c; ++i,++c);
	if(!i) {t->ch=NULL; t->length=0;}
	else{
		t->ch=(char*)malloc(i*sizeof(char));
		if(t->ch==NULL) exit(OVERFLOW);
		for(j=0;j<i;j++) t->ch[j]=chars[j];
		t->length=i;
	}
	return OK;
}
Status concat(HString *t,HString *s1,HString *s2)
{
	int i;
	if(t->ch!=NULL) free(t->ch);
	t->ch=(char*)malloc(sizeof(char)*(s1->length+s2->length));/*over flow?*/
	for(i=0;i<s1->length;i++) t->ch[i]=s1->ch[i];
	/*for(i=s1->length+1;i<s1->length+s2->length;i++) t->ch[i]=s2[i-s1->length-1];*/
	for(i=0;i<s2->length;i++) t->ch[i+s1->length]=s2->ch[i];
	t->length=s1->length+s2->length;
	return OK;
}
void strdisplay(HString *s){
	int i;
	printf("The string is:");
	for(i=0;i<s->length;i++) printf("%c",s->ch[i]);
	printf("\n");
}
Status substr(HString *sub,HString *s,int pos, int len){
	int i;
	if(pos<1||pos>s->length||len<0||len>s->length-pos+1) return ERROR;
	if(sub->ch!=NULL) free(sub->ch);
	if(len==0) {sub->length=0;sub->ch=NULL;}
	else{
		sub->ch=(char*)malloc(sizeof(char)*len);/*over flow?*/
		for(i=0;i<len;i++) sub->ch[i]=s->ch[pos-1+i];
		sub->length=len;
	}
	return OK;
}
int strlength(HString *s){
	return s->length;
}
int strcompare(HString *s,HString *t){
	int i;
	for(i=0;i<s->length&&i<t->length;i++){
		if(s->ch[i]!=t->ch[i]) return s->ch[i]-t->ch[i];
	}
	return s->length-t->length;
}
void clearstring(HString *s){
	if(s->length>0){
		s->length=0;
		free(s->ch);
	}
}
void main() {
	HString s1,s2,s3,sub;
	char *s="I am a student!";

	strassignError(&s1,s);
	strdisplay(&s1);
	getch();
/*	int compare_result;
	printf("This program tests string stored by chunk.\n");
	strassign(&s1);
	strassign(&s2);
	s3.ch=sub.ch=NULL;
	printf("Comparing s1 and s2 ...  :");
	compare_result=strcompare(&s1,&s2);
	if(compare_result==0) printf("s1==s2\n");
	else if(compare_result<0) printf("s1<s2\n");
	else printf("s1>s2\n");

	printf("Concating s1 and s2 ... :");
	concat(&s3,&s1,&s2);
	printf("s1+s2=");
	strdisplay(&s3);
	printf("The length of Concated string is %d\n",strlength(&s3));

	printf("Get a substring  from s1...\n");
	if(OK==substr(&sub,&s1,3,3)) strdisplay(&sub);
	else printf("error!!\n");*/
}
