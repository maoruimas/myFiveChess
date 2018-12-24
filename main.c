#include"myChess.h"
void testEva(char[][BOARD_SIZE]);
void testEva(char board[][BOARD_SIZE])
{
	int i;
	char j,role;
	char input[10];
	for(i=0;i<BOARD_SIZE;++i)
		for(j=0;j<BOARD_SIZE;++j)
			board[i][j]=EMPTY;
	while(1)
	{
		printBoard(board);
		scanf("%s",input);
		role=input[0],j=input[1]-'a';
		sscanf(input,"%*c%*c%d",&i);
		i=15-i;
		printf("i=%d,j=%d,role=%c\n",i,j,role);
		board[i][j]=role;
		printf("score=%d\n",evaBoard(board,BLACK));
	}
}
int setGame(char board[][BOARD_SIZE])
{
	int i,j;
	struct Move humMove,comMove;
	char command[20];
	bool isHumanMove;
	//init
	for(i=0;i<BOARD_SIZE;++i)
		for(j=0;j<BOARD_SIZE;++j)
			board[i][j]=EMPTY;
	//settings
	printf("1. computer first\n2. human first\n");
	while(~scanf("%d",&i)&&i!=1&&i!=2)printf("E: no such command.\n");
	if(i==1)
	{
		comMove.role=COMPUTER_ROLE=BLACK;
		HUMAN_ROLE=WHITE;
		comMove.x=comMove.y=BOARD_SIZE/2;
		makeMove(board,comMove);
	}else
	{
		COMPUTER_ROLE=WHITE;
		HUMAN_ROLE=BLACK;
	}
	printf("Forbidden move on? (y/n) ");
	while(~scanf("%s",command)&&tolower(command[0])!='y'&&tolower(command[0])!='n')printf("E: no such command.\n");
	FORBIDDEN_MOVE=command[0]=='y'?true:false;
	//begin
	while(1)
	{
		printBoard(board);
		if(evaBoard(board,COMPUTER_ROLE)>25000)return COMPUTER_ROLE;
		printf("Enter your move or command(i.e. regret/yield):\n");
		isHumanMove=false;
		while(~scanf("%s",command))
		{
			command[0]=tolower(command[0]);
			if(strcmp(command,"regret")==0)
			{
				//
			}
			else if(strcmp(command,"yield")==0)return COMPUTER_ROLE;
			else if(command[0]>='a'&&command[0]<'a'+BOARD_SIZE)
			{
				j=command[0]-'a';
				if(strlen(command)>1)sscanf(command,"%*c%d",&i);
				else scanf("%d",&i);
				i=BOARD_SIZE-i;
				if(i>=0&&i<BOARD_SIZE)
				{
					humMove.x=i,humMove.y=j,humMove.role=HUMAN_ROLE;
					if(isLegal(board,humMove))
					{
						printf("Your move: %c %d\n",'A'+j,BOARD_SIZE-i);//...
						makeMove(board,humMove);
						isHumanMove=true;
						printBoard(board);
						break;
					}
				}
			}
			printf("E: no such command or illegal move.\n");
		}
		if(isHumanMove)
		{
			if(evaBoard(board,HUMAN_ROLE)>25000)return HUMAN_ROLE;
			comMove=getNextMove(board,COMPUTER_ROLE);
			makeMove(board,comMove);
		}
	}
	return 0;
}
int main()
{
	//freopen("in.txt","r",stdin);
	char board[BOARD_SIZE][BOARD_SIZE];
	char command[20];
	int winner;
	evaInit();
	movInit();
	testEva(board);
	printf("==welcome to five chess==\n");
	while(winner=setGame(board))
	{
		if(winner==COMPUTER_ROLE)printf("Computer wins!\n");
		else printf("Human wins!\n");
		printf("New game? (y/n) ");
		while(~scanf("%s",command)&&tolower(command[0])!='y'&&tolower(command[0])!='n');
		if(tolower(command[0])=='n')break;
	}
}
