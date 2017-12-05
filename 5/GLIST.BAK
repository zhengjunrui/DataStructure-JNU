#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum{OK,ERROR,OVERFLOW}Status;
typedef  enum {ATOM, LIST} Elemtag;
typedef char ElemType;
typedef  struct  GLNode {
    Elemtag  tag;
    union {
      ElemType  data;
      struct {
	 struct GLNode  *hp, *tp;
      }ptr;
    }atom_or_lists;
}GLNode,*GList;
/*GList Head(GList ls)
{
	if (ls->tag == 1)
		return ls->hp;
}
GList Tail(GList ls)
{
	GList p;
	if (ls->tag == 1)
    	then  p = ls->tp;
   	return  p;
  }  */
Status  Create(GList *ls, char * S)
{
	GList  p,q;
	char  sub[100],hsub[100];

	if(strcmp(S,"()")==0)  *ls = NULL;
   	else {
		*ls = (GList)malloc(sizeof(GLNode));
		if (*ls==NULL)  exit(OVERFLOW);
		if (strlen(S) == 1) {
      			(*ls)->tag = 0;
			(*ls)->atom_or_lists.data = S[0];
    		 }
		 else {
      			(*ls)->tag = 1;
      			p = *ls;
			strncpy(sub,S+1,strlen(S)-2);
      			do {
		        	sever(sub,hsub);
				Create(&(p->atom_or_lists.ptr.hp), sub);
        			q = p;
				if (strlen(sub)!=0){
					p = (GList)malloc(sizeof(GLNode));
					p->tag = 1;
					q->atom_or_lists.ptr.tp = p;
         			}
			 }while (strlen(sub));
			 q->atom_or_lists.ptr.tp = NULL;
		}/*end if-else strlen==1*/
    	}
	return OK;
}
int  sever(char *str, char *hstr)
{
	int  n,i,k;
	char ch;
	n=strlen(str);
	i= 0; k = 0;
	do{
		i++;
		ch=str[i];
		if(ch=='(') k++;
		else if(ch==')') k--;
	}while(i < n && (ch!=','|| k != 0));
	if (i < n) {
		strncpy(hstr,str,i-1);
		strncpy(str,str,i+1);
    	}
   	else {
		strcpy(hstr,str);
		str[0]='\0';
    	}
}
void display(GList ls){

}
/*int Depth(GList ls)
  {
   if (!ls)
     return  1;
   if (ls->tag = = 0)
     return  0;
   for (max = 0,p = ls; p; p = p->ptr.tp) {
     dep = Depth(p->ptr.hp);
     if (dep > max)  max = dep;
    }
   return max+1;
  }
int  CopyGList(GList ls1, GList *ls2)
  {
   if (!ls1)  *ls2 = NULL;
   else {
     if (!(*ls2 = (Glist)malloc(sizeof(Glnode)))) return 0;
     (*ls2)->tag = ls1->tag;
     if (ls1->tag = = 0) (*ls2)->data = ls1->data;
     else {
       CopyGList(&((*ls2)->ptr.hp), ls1->ptr.hp);
       CopyGList(&((*ls2)->ptr.tp) , ls1->ptr.tp);
     }
   }
   return 1;
  }
*/
void main(){
	char *lists="(a,(b,c,d))";
	GList *a;
	creat(&a,lists);
	display(a);
}