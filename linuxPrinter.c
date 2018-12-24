#include"myChess.h"
void printBoard(char board[][BOARD_SIZE])
{
	int i,j;
	for(i=0;i<BOARD_SIZE;++i)
	{
		printf("%2d",15-i);
		for(j=0;j<BOARD_SIZE;++j)
		{
			if(board[i][j]==BLACK)printf("●");
			else if(board[i][j]==WHITE)printf("○");
			else if(board[i][j]==EMPTY)
			{
				if(i==0&&j==0)printf("┏");
				else if(i==0&&j==BOARD_SIZE-1)printf("┓");
				else if(i==BOARD_SIZE-1&&j==0)printf("┗");
				else if(i==BOARD_SIZE-1&&j==BOARD_SIZE-1)printf("┛");
				else if(i==0)printf("┯");
				else if(i==BOARD_SIZE-1)printf("┷");
				else if(j==0)printf("┠");
				else if(j==BOARD_SIZE-1)printf("┨");
				else printf("┼");
			}
			else printf("%c",board[i][j]);
		}
		printf("\n");
	}
	printf("  ");
	for(int i='A';i<'A'+BOARD_SIZE;++i)
		printf("%c ",i);
	printf("\n");
}