#include"myChess.h"
#define MAX_REF_TIME 1000000
struct Move nextMove;
int DEPTH;
struct Move getNextMove(char board[][BOARD_SIZE],int role)
{
    int begTime,endTime,cntTime;
    begTime=clock();
    for(DEPTH=1; DEPTH; ++DEPTH)
    {
        printf("thinking level %d:\n",DEPTH);
        cntTime=clock();
        alphaBeta(board,DEPTH,-INF,INF,role);
        endTime=clock();
        printf("Total: %dms\n",(endTime-cntTime)/1000);
        if(endTime-begTime>=MAX_REF_TIME)
        {
            printf("Time is out. %d leyer(s) searched. %dms used totally.\n",DEPTH,(endTime-begTime)/1000);
            break;
        }
    }
    return nextMove;
}
int alphaBeta(char board[][BOARD_SIZE],int depth,int alpha,int beta,int role)
{
    int totScore;
    totScore=evaBoard(board,role);
    if(depth<=0||abs(totScore)>25000)
        return totScore;
    int val;
    struct moveStack mst;
    genLegalMoves(board,role,&mst);
    while(movesLeft(&mst))
    {
        if(!makeMove(board,mst.sta[mst.top-1]))
        {
            //printf("cant make move(%c,%d) at %d\n",mst.sta[mst.top-1].y+'A',15-mst.sta[mst.top-1].x,mst.top);
            mst.top--;
            continue;
        }
        val=-alphaBeta(board,depth-1,-beta,-alpha,role==BLACK?WHITE:BLACK);
        unmakeMove(board,mst.sta[--mst.top]);
        /*
        int i;
        for(i=depth; i<DEPTH; ++i)
            printf("\t");
        printf("move(%c,%d)=%d\n",mst.sta[mst.top].y+'A',15-mst.sta[mst.top].x,val);
        */
        if(val>=beta)
        {
            //printf("val>=beta(%d),break\n",beta);
            return beta;
        }
        if(val>alpha)
        {
            if(depth==DEPTH)
            {
                nextMove=mst.sta[mst.top];
                //printf("nextMove(%c,%d)=%d\n",nextMove.y+'A',15-nextMove.x,val);
            }
            alpha=val;
        }
    }
    return alpha;
}
