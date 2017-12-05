/************************************************************************/
/*   The code creates a hash table.   		                        */
/*   The data for testing can be finded on Page 260			*/
/*   Author: John Lee                                                   */
/*   E-mail: paperbakup@163.com                                         */
/*   Date : 2004-12-05                                                  */
/************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAXSIZE 13
typedef int ElemType;
typedef struct{
	ElemType *elem;
	int listsize;
	int hashsize;
}HashTable;

typedef enum{FOUND,NOFOUND,SUCCESS,UNSUCCESS,DUPLICATE} Status;
Status collision(int *ptr_pos){
	static int count=0;

	if(++count==MAXSIZE) return UNSUCCESS;
	else{
		*ptr_pos=(*ptr_pos+1)%MAXSIZE;
		return SUCCESS;
	}
}
Status SearchHashTable(HashTable *H,ElemType key,int *ptr_pos){
	int pos;
	Status sch;

	pos=key%H->hashsize;
	while(H->elem[pos]!=INT_MAX&&key!=H->elem[pos]) sch=collision(&pos);
	if(key==H->elem[pos]) return FOUND;
	else if(sch==UNSUCCESS) return UNSUCCESS;
	else{
		*ptr_pos=pos;
		return NOFOUND;
	}
}

Status InsertHashTable(HashTable *H,ElemType key){
	int pos;
	Status sch;

	if((sch=SearchHashTable(H,key,&pos))==FOUND) return DUPLICATE;
	else if(sch==UNSUCCESS) return UNSUCCESS;
	else{
		H->elem[pos]=key;
		H->listsize++;
		return SUCCESS;
	}
}
void init(HashTable *H){
	int i;
	H->hashsize=MAXSIZE;
	H->listsize=0;
	H->elem=(ElemType*)malloc(sizeof(ElemType)*H->hashsize);
	for(i=0;i<H->hashsize;i++) H->elem[i]=INT_MAX; /*if ==INT_MAX,the address 'i' not used*/
}

void main(){
	int key,i,j;
	HashTable HT;
	int record[]={19,14,23,1,68,20,84,27,55,11,10,79};
	int total=12;/*The number of records*/

        printf("The test data is (can modified in the program) :\n");
        for(i=0;i<total;i++) printf("%d\t",record[i]);
        printf("\n");

        init(&HT);
	for(j=0;j<total;j++){
		switch(InsertHashTable(&HT,record[j])) {
			case UNSUCCESS:
				printf("The max volume of hash talbe is reached,can not insert!\n");
				break;
			case DUPLICATE:
			        printf("The key exsited in the hash table\n");
			        break;
			case SUCCESS:
				printf("Insert successfully.The new table is:\n");
				for(i=0;i<HT.hashsize;i++) printf("%d ",HT.elem[i]);
				printf("\n");
				break;
		}
	}
	free(HT.elem);
	getch();
}