#include <conio.h>
#include <dos.h>
#include <stdio.h>
#define STARTX 20
#define STARTY 5
#define WIDTH 40
#define HEIGHT 10
#define COMMAND 1
#define EDIT    0
#define MAX_COMMAND_LEN 20
#define MAX_PAGE   100
#define ENTER  13 /*'\n'==10*/
#define BACKSPACE    8
#define F1     0x3b
#define F2     0x3c
#define DOWN   80
#define UP     72
#define LEFT   75
#define RIGHT  77
struct {
	int mode;
	int insert;
}cur_status;
typedef struct {
	char *ch;
	int length;
	int max_length;
} HString;
struct {
	int begin;
	int length;
}table_line[MAX_PAGE*HEIGHT];
struct {
	int page[MAX_PAGE];
	int ptr_page;
	int ptr_line;
	int ptr_char;
	int total_line;
	int total_page;
}table_page;
int cursor_x=1; int cursor_y=1;
typedef enum{OK,ERROR,OVERFLOW,CUT,UNCUT}Status;
void strinit(HString *t){
	t->max_length=255;
	t->ch=(char*)malloc(sizeof(char)*t->max_length);
	if(t->ch==NULL) exit(OVERFLOW);
	t->length=0;
}
void strinsert(HString *t,int c,int pos)
{
	int i;
	if(t->length==t->max_length){
		t->ch=(char*)malloc(t->ch,t->max_length*2);
		if(t->ch==NULL) exit(OVERFLOW);
	}
/*	for(i=t->length-1;i>=pos-1;i--) t->ch[i+1]=t->ch[i];*/
	t->ch[pos]=(char)c;
	t->length++;
}
void strdel(HString *t,int pos)
{
	int i;
	for(i=pos-1;i<t->length-1;i++) t->ch[i]=t->ch[i+1];
	t->length--;
}
Status concat(HString *t,HString *s1,HString *s2)
{
	int i;
	if(t->ch!=NULL) free(t->ch);
	t->ch=(char*)malloc(sizeof(char)*(s1->length+s2->length));/*over flow?*/
	for(i=0;i<s1->length;i++) t->ch[i]=s1->ch[i];
	for(i=0;i<s2->length;i++) t->ch[i+s1->length]=s2->ch[i];
	t->length=s1->length+s2->length;
	return OK;
}
void strdisplay(int key){
	putch(key);

}
Status substr(HString *sub,HString *s,int pos, int len){
	int i;
	if(pos<1||pos>s->length||len<0||len>s->length-pos+1) return ERROR;
	if(sub->ch!=NULL) free(sub->ch);
	if(len==0) {sub->length=0;sub->ch=NULL;}
	else{
		s->ch=(char*)malloc(sizeof(char)*len);/*over flow?*/
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
void strclear(HString *s){
	if(s->length>0){
		s->length=0;
	}
}
void strdestroy(HString *s){
	free(s->ch);
}
void box(int startx,int starty,int width, int height){
	int i;
	gotoxy(startx,starty);
	putch(0xda);
	for(i=1;i<width;i++) putch(0xc4);
	putch(0xbf);
	for(i=starty+1;i<starty+height-1;i++){
		gotoxy(startx,i);putch(0xb3);
		gotoxy(startx+width, i);putch(0xb3);
	}
	gotoxy(startx,starty+height-1);
	putch(0xc0);
	for(i=1;i<width;i++) putch(0xc4);
	putch(0xd9);

}
void gotowindow(int mode){
	switch(mode){
		case 0:
			window(STARTX,STARTY,STARTX+WIDTH-1,STARTY+HEIGHT-1);
			textbackground(BLACK);
			textcolor(WHITE);
			break;
		case 1:
			window(STARTX+10,STARTY+HEIGHT+1,\
			STARTX+WIDTH-1,STARTY+HEIGHT+1);
			textbackground(BLACK);
			textcolor(WHITE);
			break;
	}/*end switch(mode)*/
}
void initwindow(){
	int i,j;
	textmode(C80);
	textbackground(BLACK);
	textcolor(WHITE);
	clrscr();
	box(STARTX-1,STARTY-1,WIDTH+2,HEIGHT+2);
	window(STARTX+(WIDTH-12)/2,STARTY-2,\
	       STARTX+(WIDTH+12)/2,STARTY-1);
	textbackground(LIGHTGRAY);
	textcolor(BLACK);
	cprintf(" EDIT  DEMO ");
	window(STARTX,STARTY+HEIGHT+1,\
	       STARTX+9,STARTY+HEIGHT+1);
	cprintf(" Command:");
	gotowindow(EDIT);
}
int get_key(){
	union REGS rg;
	rg.h.ah=0;
	int86(0x16,&rg,&rg);
	return rg.h.ah;
}
int findcommand(HString *t){
	static HString command[3];
	int i;
	for(i=0;i<3;i++) strinit(&command[i]);
	{command[0].ch[0]='q',command[0].ch[1]='u',command[0].ch[2]='i',command[0].ch[3]='t',command[0].length=4;
	 command[1].ch[0]='s',command[1].ch[1]='a',command[1].ch[2]='v',command[1].ch[3]='e',command[1].length=4;
	 command[2].ch[0]='l',command[2].ch[1]='o',command[2].ch[2]='a',command[2].ch[3]='d',command[2].length=4;
	}
	for(i=0;i<3;i++){
		if(strcompare(&command[i],t)==0) break;
	}
	if(i<3) return i;
	else return 100;
}
void savefile(){
}
void loadfile(){

}
void inputdata(HString *s,int key){
	int position,tmp1,tmp2;
	/*	if(key==BACKSPACE)*/
	if(table_page.ptr_char==WIDTH){
		table_page.ptr_char=1;
		if(table_page.ptr_line==HEIGHT){
			table_page.ptr_line=1;
			table_page.ptr_page++;
			if(table_page.ptr_page==MAX_PAGE) return;
		}
		else table_page.ptr_line++;
	}
	else table_page.ptr_char++;
	tmp1=table_page.page[table_page.ptr_page];/*first line of cur page */
	tmp2=tmp1+table_page.ptr_line-1;/*current line*/
	position=table_line[tmp2].begin+table_page.ptr_char-1;/*position of current char*/

	strinsert(s,key,position);
}
void main(){
	int key,key1,key2,cur_command;
	HString command,data;
	struct text_info cur_info;
	strinit(&command);
	strinit(&data);
	table_page.ptr_char=table_page.ptr_line=table_page.total_line=0;
	table_page.total_page=table_page.ptr_page=0;
	initwindow();
	gotowindow(EDIT);
	while(1){
		key=0;
		while(bioskey(1)==0);
		key=bioskey(0);
		key1=key&0xff;
		key2=(key&0xff00)>>8;
		if(key1!=0){
			if(cur_status.mode==COMMAND){
				if(key1==ENTER){
					cur_command=findcommand(&command);
					switch(cur_command){
						case 0: exit(OK);
						case 1:
							savefile();
							gotowindow(COMMAND);
							delline();
							strclear(&command);
							break;
						case 2: loadfile();
							gotowindow(COMMAND);
							delline();
							strclear(&command);
							break;
						default:
							gotowindow(COMMAND);
							delline();
							strclear(&command);
					}
				}
				else{
					if(command.length<MAX_COMMAND_LEN){
						strinsert(&command,(char)key1,command.length);
						putch(key1);
					}
				}
			}/*end if(cur_status==COMMAND)*/
			else{
				if(key1!=BACKSPACE) inputdata(&data,key1);
				strdisplay(key1);
			}
		}
		else{ /*function key pressed*/
			switch(key2){
				case F1:
					if(cur_status.mode==COMMAND){
						strclear(&command);
						delline();
						gotowindow(EDIT);
						cur_status.mode=EDIT;
					}
					else{
						gotowindow(COMMAND);
						cur_status.mode=COMMAND;
					}
					break;
				case F2:
					if(cur_status.insert==0)
						cur_status.insert=0;
					else cur_status.insert=1;
					break;
				case UP:
					gettextinfo(&cur_info);
					gotoxy(cur_info.curx,cur_info.cury-1);
					break;
				case DOWN:
					gettextinfo(&cur_info);
					gotoxy(cur_info.curx,cur_info.cury+1);
					break;
				case RIGHT:
					gettextinfo(&cur_info);
					gotoxy(cur_info.curx+1,cur_info.cury);
					break;
				case LEFT:
					gettextinfo(&cur_info);
					gotoxy(cur_info.curx-1,cur_info.cury);
					break;
			}/*end switch(key2)*/
		}/*end if(key1!=0)*/
	}/*end while(1)*/
	getch();
}