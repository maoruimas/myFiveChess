#ifndef MYTOOLS
#define MYTOOLS
//include
#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include<ctype.h>
//const
#define INF 0x3f3f3f3f
#define EPS 1e-6
//min/max/abs
int min(int,int);
int max(int,int);
int abs(int);
//queue
void qClear();
bool qEmpty();
int qSize();
int qFront();
int qBack();
void qPush(int);
void qPop();
//stack
void sClear();
bool sEmpty();
int sSize();
int sTop();
void sPush(int);
void sPop();
//acauto
void acBuild(char[][10],int[],int);
int acSearch(char[]);
#endif
