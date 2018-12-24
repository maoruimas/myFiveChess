#ifndef MYCHESS
#define MYCHESS
//include
#include"myTools.h"
//const
#define BLACK '1'
#define WHITE '0'
#define EMPTY '2'
#define BOARD_SIZE 15
#define PATTERN_SIZE 20
#define PATTERN_LENTH 10
#define SEARCH_RANGE 2
//variables
bool FORBIDDEN_MOVE;
int COMPUTER_ROLE,HUMAN_ROLE;
//type
struct Move
{
	int x,y,role,score;
};
struct moveStack
{
	struct Move sta[BOARD_SIZE*BOARD_SIZE+5];
	int top;
};
//evaluator
void evaInit();
void revRole(char[]);
int evaLine(char[][BOARD_SIZE],int,int,int,int);
int evaPoint(char[][BOARD_SIZE],int,int,int);
int evaBoard(char[][BOARD_SIZE],int);
//engine
struct Move getNextMove(char[][BOARD_SIZE],int);
int alphaBeta(char[][BOARD_SIZE],int,int,int,int);
//move generator
void movInit();
void genLegalMoves(char[][BOARD_SIZE],int,struct moveStack*);
bool movesLeft(struct moveStack*);
void updateRange();
bool makeMove(char[][BOARD_SIZE],struct Move);
bool unmakeMove(char[][BOARD_SIZE],struct Move);
//forbidden move
bool isForbidden(char[][BOARD_SIZE],struct Move);
bool isLegal(char[][BOARD_SIZE],struct Move);
//printer
void printBoard(char[][BOARD_SIZE]);
//main
int setGame(char[][BOARD_SIZE]);
#endif
