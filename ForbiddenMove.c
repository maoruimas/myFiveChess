#include"myChess.h"
bool isForbidden(char board[][BOARD_SIZE],struct Move mv)
{

}
bool isLegal(char board[][BOARD_SIZE],struct Move mv)
{
	return (mv.x>=0&&mv.x<=BOARD_SIZE&&mv.y>=0&&mv.y<=BOARD_SIZE&&(mv.role==BLACK||mv.role==WHITE)&&board[mv.x][mv.y]==EMPTY&&((!FORBIDDEN_MOVE)||(FORBIDDEN_MOVE&&!isForbidden(board,mv))));
}
