#include"myChess.h"
char pattern[PATTERN_SIZE][PATTERN_LENTH]={
	"11111",
	"211112",
	"211122",
	"221112",
	"211212",
	"212112",
   	"11112",
   	"21111",
   	"11211",
   	"12111",
	"11121",
   	"221122",
   	"221212",
   	"212122",
   	"222122",
   	"221222"
};
int patternScore[PATTERN_SIZE]={
	50000,
	432,
	72,
	72,
	72,
	72,
	72,
	72,
	72,
	72,
	72,
	12,
	12,
	12,
	2,
	2
};
void evaInit()
{
	acBuild(pattern,patternScore,PATTERN_SIZE);
}
void revRole(char s[])
{
	for(;*s;++s)*s=(*s=='2'?'2':(*s=='1'?'0':'1'));
}
int evaLine(char board[][BOARD_SIZE],int x,int y,int type,int role)
{
	int i,j,ret;
	char tp[BOARD_SIZE];
	ret=0;
	switch(type)
	{
		case 1:
			for(j=0;j<BOARD_SIZE;++j)
        		tp[j]=board[x][j];
    		tp[BOARD_SIZE]=0;
			break;
		case 2:
    		for(i=0;i<BOARD_SIZE;++i)
        		tp[i]=board[i][y];
    		tp[BOARD_SIZE]=0;
			break;
		case 3:
			i=x+y;
			for(j=0;j<BOARD_SIZE-abs(i-BOARD_SIZE+1);++j)
				tp[j]=board[min(i,BOARD_SIZE-1)-j][max(0,i-BOARD_SIZE+1)+j];
			tp[BOARD_SIZE-abs(i-BOARD_SIZE+1)]=0;
			break;
		case 4:
			i=x-y+BOARD_SIZE-1;
			for(j=0;j<BOARD_SIZE-abs(i-BOARD_SIZE+1);++j)
				tp[j]=board[min(i,BOARD_SIZE-1)-j][min(BOARD_SIZE-1,2*BOARD_SIZE-2-i)-j];
			tp[BOARD_SIZE-abs(i-BOARD_SIZE+1)]=0;
			break;
		default:
			break;
	}
	if(role==WHITE)revRole(tp);
	ret+=acSearch(tp);
	revRole(tp);
	ret-=acSearch(tp);
	return ret;
}
int evaPoint(char board[][BOARD_SIZE],int x,int y,int role)
{
	int i,ret=0;
	for(i=1;i<=4;++i)
		ret+=evaLine(board,x,y,i,role);
	return ret;
}
int evaBoard(char board[][BOARD_SIZE],int role)
{
    int i,j,ret=0;
	for(i=0;i<BOARD_SIZE;++i)
	{
		for(j=2;j<5;++j)
			ret+=evaLine(board,0,i,j,role);
		ret+=evaLine(board,i,0,1,role);
		ret+=evaLine(board,i,0,4,role);
		ret+=evaLine(board,i,BOARD_SIZE-1,3,role);
	}
	return ret;
}
