#include"myChess.h"
#define MAX_SEARCH_NODES 10
int maxI,minI,maxJ,minJ;
int cntMove[2][BOARD_SIZE];
void movInit()
{
    //maxI=maxJ=minI=minJ=BOARD_SIZE/2;
    minI=minJ=0;
    maxI=maxJ=BOARD_SIZE-1;
    memset(cntMove[0],0,sizeof cntMove[0]);
    memset(cntMove[1],0,sizeof cntMove[1]);
}
void swapMove(struct Move *mv1,struct Move *mv2)
{
    struct Move tmv;
    tmv=*mv1;
    *mv1=*mv2;
    *mv2=tmv;
}
void genLegalMoves(char board[][BOARD_SIZE],int role,struct moveStack *pms)
{
    //printf("i(%d,%d),j(%d,%d)\n",minI,maxI,minJ,maxJ);
    int i,j;
    struct Move *pmv,tmv;
    pms->top=0;
    for(i=minI; i<=maxI; ++i)
        for(j=minJ; j<=maxJ; ++j)
        {
            pmv=&pms->sta[pms->top];
            pmv->x=i,pmv->y=j,pmv->role=role;
            if(isLegal(board,*pmv))
            {
                pmv->score=-evaPoint(board,pmv->x,pmv->y,role);
                board[pmv->x][pmv->y]=role;
                pmv->score+=evaPoint(board,pmv->x,pmv->y,role);
                board[pmv->x][pmv->y]=EMPTY;
                pms->top++;
            }
        }
    //printf("stack: %d\n",pms->top);
    for(i=0; i<min(MAX_SEARCH_NODES,pms->top); ++i)
        for(j=pms->top-1; j>i; --j)
            if(pms->sta[j].score>pms->sta[j-1].score)
                swapMove(&pms->sta[j],&pms->sta[j-1]);
    pms->top=min(pms->top,MAX_SEARCH_NODES);
    for(i=0;i<pms->top/2;++i)
        swapMove(&pms->sta[i],&pms->sta[pms->top-1-i]);
    //printf("stack now: %d\n",pms->top);
}
bool movesLeft(struct moveStack *pms)
{
    return pms->top>0;
}
void updateRange()
{
    int i;
    for(i=0; i<BOARD_SIZE&&cntMove[0][i]==0; ++i);
    minI=max(0,i-SEARCH_RANGE);
    for(i=BOARD_SIZE-1; i>=0&&cntMove[0][i]==0; --i);
    maxI=min(BOARD_SIZE-1,i+SEARCH_RANGE);
    for(i=0; i<BOARD_SIZE&&cntMove[1][i]==0; ++i);
    minJ=max(0,i-SEARCH_RANGE);
    for(i=BOARD_SIZE-1; i>=0&&cntMove[1][i]==0; --i);
    maxJ=min(BOARD_SIZE-1,i+SEARCH_RANGE);
}
bool makeMove(char board[][BOARD_SIZE],struct Move mv)
{
    if(!isLegal(board,mv))return false;
    board[mv.x][mv.y]=mv.role;
    cntMove[0][mv.x]++,cntMove[1][mv.y]++;
    updateRange();
    return true;
}
bool unmakeMove(char board[][BOARD_SIZE],struct Move mv)
{
    if(board[mv.x][mv.y]==mv.role)
    {
        board[mv.x][mv.y]=EMPTY;
        cntMove[0][mv.x]--,cntMove[1][mv.y]--;
        updateRange();
        return true;
    }
    return false;
}
