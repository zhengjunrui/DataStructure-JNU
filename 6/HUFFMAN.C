typedef struct{
	int weight;
	int parent,lchild,rchild;
}HTNode,*HuffmanTree;
typedef char ** HuffmanCode;
void select(HuffmanTree HT, int n,int *s1,int *s2){
	int i,tmp;
	i=0;
	while(HT[++i].parent!=0);
	*s1=i;
	while(HT[++i].parent!=0);
	*s2=i;
	if(HT[*s1].weight>HT[*s2].weight){
		tmp=*s1;
		*s1=*s2;
		*s2=tmp;
	}
	for(i=i+1;i<=n;i++){
		if(HT[i].parent==0){
			if(HT[i].weight<HT[*s2].weight){
				if(HT[*s1].weight>HT[i].weight){
					*s2=*s1;
					*s1=i;
				}
				else{
					*s2=i;
				}
			}/*end if HT[i].weight<*/
		}/*end if ht[i].parent=0*/
	}
}
void huffmancoding(HuffmanTree *HHT,HuffmanCode *HHC,int *w,int total_leaf){
	int total_node,i,start,curent,parent;
	int min1,min2;
	char *code;
	HuffmanTree HT;
	HuffmanCode HC;
	/*construct huffman tree*/
	if(total_leaf<=1) return;
	total_node=2*total_leaf-1;
	HT=(HuffmanTree)malloc((total_node+1)*sizeof(HTNode));
	*HHT=HT;
	for(i=1;i<=total_leaf;i++){
		HT[i].weight=*w++;
		HT[i].parent=0;
		HT[i].lchild=0;
		HT[i].rchild=0;
	}
	for(i=total_leaf+1;i<=total_node;i++){
		HT[i].weight=0;
		HT[i].parent=0;
		HT[i].lchild=0;
		HT[i].rchild=0;
	}
	for(i=total_leaf+1;i<=total_node;i++){
		select(HT,i-1,&min1,&min2);
		HT[min1].parent=i;
		HT[min2].parent=i;
		HT[i].lchild=min1;
		HT[i].rchild=min2;
		HT[i].weight=HT[min1].weight+HT[min2].weight;
	}/*end for i=total_leaf*/

	/*creat code book*/
	HC=(HuffmanCode)malloc((total_leaf+1)*sizeof(char*));
	*HHC=HC;
	code=(char*)malloc(total_leaf*sizeof(char));
	code[total_leaf-1]='\0';
	for(i=1;i<=total_leaf;i++){
		start=total_leaf-1;
		curent=i;
		for(parent=HT[curent].parent;parent!=0;parent=HT[curent].parent){
			if(HT[parent].lchild==curent) code[--start]='0';
			else code[--start]='1';
			curent=parent;
		}
		HC[i]=(char*)malloc((total_leaf-start)*sizeof(char));
		strcpy(HC[i],&code[start]);
	}
	free(code);
}
void huffmancoding2(HuffmanTree *HHT,HuffmanCode *HHC,int *w,int total_leaf){
	int total_node,i,start;
	int min1,min2,*tag;
	char *code;
	HuffmanTree HT;
	HuffmanCode HC;
	/*construct huffman tree*/
	if(total_leaf<=1) return;
	total_node=2*total_leaf-1;
	HT=(HuffmanTree)malloc((total_node+1)*sizeof(HTNode));
	*HHT=HT;
	for(i=1;i<=total_leaf;i++){
		HT[i].weight=*w++;
		HT[i].parent=0;
		HT[i].lchild=0;
		HT[i].rchild=0;
	}
	for(i=total_leaf+1;i<=total_node;i++){
		HT[i].weight=0;
		HT[i].parent=0;
		HT[i].lchild=0;
		HT[i].rchild=0;
	}
	for(i=total_leaf+1;i<=total_node;i++){
		select(HT,i-1,&min1,&min2);
		HT[min1].parent=i;
		HT[min2].parent=i;
		HT[i].lchild=min1;
		HT[i].rchild=min2;
		HT[i].weight=HT[min1].weight+HT[min2].weight;
	}/*end for i=total_leaf*/

	/*creat code book*/
	HC=(HuffmanCode)malloc((total_leaf+1)*sizeof(char*));
	*HHC=HC;
	code=(char*)malloc(total_leaf*sizeof(char));
	tag=(int*)malloc((total_node+1)*sizeof(int));
	for(i=1;i<=total_node;i++) tag[i]=0;
	start=0;
	i=total_node;
	while(i!=0){
		if(tag[i]==0){
			tag[i]=1;
			if(HT[i].lchild!=0){
				i=HT[i].lchild;
				code[start++]='0';
			}
			else if(HT[i].rchild==0){
				HC[i]=(char*)malloc((start+1)*sizeof(char));
				code[start]='\0';
				strcpy(HC[i],code);
			}
		}
		else if(tag[i]==1){
			tag[i]=2;
			if(HT[i].rchild!=0){
				i=HT[i].rchild;
				code[start++]='1';
			}
		}
		else{
			tag[i]=0;
			i=HT[i].parent;
			start--;
		}
	}
	free(code);
}
void main(){
	int w[]={5,29,7,8,14,23,3,11};
	int total_leaf=8;
	int i;
	HuffmanTree HT,HT2;
	HuffmanCode HC,HC2;
	huffmancoding(&HT,&HC,w,total_leaf);
	printf("\t\tweight\tparent\tlchild\trchild\n");
	for(i=1;i<=2*total_leaf-1;i++){
		printf("node %2d:\t%d\t%d\t%d\t%d\n",i,HT[i].weight,HT[i].parent,HT[i].lchild,HT[i].rchild);
	}
	for(i=1;i<=total_leaf;i++){
		printf("Leaf %2d: %s\n",i,HC[i]);
	}
	huffmancoding2(&HT2,&HC2,w,total_leaf);
	printf("\t\tweight\tparent\tlchild\trchild\n");
	for(i=1;i<=2*total_leaf-1;i++){
		printf("node %2d:\t%d\t%d\t%d\t%d\n",i,HT2[i].weight,HT2[i].parent,HT2[i].lchild,HT2[i].rchild);
	}
	for(i=1;i<=total_leaf;i++){
		printf("Leaf %2d: %s\n",i,HC2[i]);
	}
	getch();
}