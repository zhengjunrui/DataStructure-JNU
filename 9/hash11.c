/************************************************************************/
/*   The code creates a hash table.   		                        */
/*   Author: John Lee                                                   */
/*   E-mail: paperbakup@163.com                                         */
/*   Date : 2004-12-05                                                  */
/************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX 3
int hashsize[MAX]={13,17,23};
typedef struct{
	ElemType *elem;
	int listsize;
	int sizeindex;
}HashTable;

typedef enum{FOUND,NOFOUND,SUCCESS,UNSUCCESS,DUPLICATE} Status;
Status SearchHash(HashTable *H,ElemType key,int *ptr_pos, int *ptr_count){
	
}
Status InsertHash(HashTable *H,ElemType key){
	int pos,count=0;
	
	if(Search(H,key,&pos,&count)==FOUND) return DUPLICATE;
	else if(count<hashsize[H->sizeindex]/2){
		H->elem[p]=key;
		H->listsize++;
		return SUCCESS;
	}
	else {
		if(RecreateHashTable(H)!=SUCCESS) {
			return UNSUCCESS;	
		}
		return	SUCCESS;
	}
}
void init(HashTable *H,int index){
	int i;
	H->sizeindex=index;
	H->elem=(ElemType*)malloc(sizeof(ElemType)*hashsize[H->sizeindex]);	
	for(i=0;i<hashsize[H->sizeindex];i++) H->elem[i]=INT_MAX;
}

Status RecreateHashTable(HashTable *H){
	int i;
	ElemType *p;
	if(H->sizeindex==MAX-1) return UNSUCESS;
	else{
		p=H->elem;
		init(H,H->sizeindex+1);
		for(i=0;i<hashsize[H->sizeindex-1];i++){
			if(p->elem[i]!=INT_MAX){
					
			}	
		} H->elem[i]=INT_MAX;
	}	
}
void main(){
	
	int key;
	HashTable HT;
	int record[]={19,14,23,1,68,20,84,27,55,11,10,79};
	int total=12;/*The number of records*/

        printf("The test data is (can modified in the program) :\n");
        for(i=0;i<total;i++) printf("%d\t",record[i]);
        printf("\n");
        
        init(&HT);
        
	for(i=0;i<total;i++){
		switch(InsertHashTable(&HT,key)){
			case UNSUCCESS:
				printf("The max volume of hash talbe is reached,can not insert!\n");
				break;
			case DUPLICATE;
			        printf("The key exsited in the hash table\n");
			        break;
			case SUCCESS:
				printf("Insert successfully.The new table is:\n");
				for(i=0;i<hashsize[H.sizeindex];i++) printf("%d\t",H.elem[i]);
				printf("\n");
				break;		
		}
	}
	free(HT.elem);
	getch();
}