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
int evaLine(char s[],int role)
{
	int ret=0;
	if(role=='0')revRole(s);
	ret+=acSearch(s);
	revRole(s);
	ret-=acSearch(s);
	return ret;
}
int evaPoint(char board[][BOARD_SIZE],int x,int y,int role)
{
	int i,j,ret;
	char tp[BOARD_SIZE];
	ret=0;
	for(j=0;j<BOARD_SIZE;++j)
        tp[j]=board[x][j];
    tp[BOARD_SIZE]=0;
    ret+=evaLine(tp,role);
    for(i=0;i<BOARD_SIZE;++i)
        tp[i]=board[i][y];
    tp[BOARD_SIZE]=0;
    ret+=evaLine(tp,role);
	if((i=x+y)&&i>=4&&i<2*BOARD_SIZE-5)
    {
		for(j=0;j<BOARD_SIZE-abs(i-BOARD_SIZE+1);++j)
			tp[j]=board[min(i,BOARD_SIZE-1)-j][max(0,i-BOARD_SIZE+1)+j];
		tp[BOARD_SIZE-abs(i-BOARD_SIZE+1)]=0;
		ret+=evaLine(tp,role);
    }
    if((i=x-y+BOARD_SIZE-1)&&i>=4&&i<2*BOARD_SIZE-5)
    {
		for(j=0;j<BOARD_SIZE-abs(i-BOARD_SIZE+1);++j)
			tp[j]=board[min(i,BOARD_SIZE-1)-j][min(BOARD_SIZE-1,2*BOARD_SIZE-2-i)-j];
		tp[BOARD_SIZE-abs(i-BOARD_SIZE+1)]=0;
        ret+=evaLine(tp,role);
	}
	return ret;
}
int s15[15]={0,2,4,1,9,11,13,3,12,8,5,14,6,10,7};
int evaBoard(char board[][BOARD_SIZE],int role)
{
    int i,ret;
    ret=0;
    for(i=0;i<BOARD_SIZE;++i){ret+=evaPoint(board,i,s15[i],role);printf("ret=%d\n",ret);}
    return ret;
}
