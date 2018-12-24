#include"myTools.h"
//min/max/abs
int min(int x,int y)
{
	return x>y?y:x;
}
int max(int x,int y)
{
	return x>y?x:y;
}
int abs(int x)
{
	return x<0?-x:x;
}
//queue
#define MAX_QUEUE_SIZE 1000
int que[MAX_QUEUE_SIZE];
int head,tail;
void qClear()
{
	head=tail=0;
}
bool qEmpty()
{
	return head>=tail;
}
int qSize()
{
	return tail-head;
}
int qFront()
{
	if(qEmpty())return -INF;
	return que[head];
}
int qBack()
{
	if(qEmpty())return -INF;
	return que[tail-1];
}
void qPush(int x)
{
	if(tail>=MAX_QUEUE_SIZE)return;
	que[tail++]=x;
}
void qPop()
{
	if(qEmpty())return;
	head++;
}
//stack
#define MAX_STACK_SIZE 1000
int sta[MAX_STACK_SIZE];
int top;
void sClear()
{
	top=0;
}
bool sEmpty()
{
	return top==0;
}
int sSize()
{
	return top;
}
int sTop()
{
	if(sEmpty())return -INF;
	return sta[top-1];
}
void sPush(int x)
{
	if(top>=MAX_STACK_SIZE)return;
	sta[top++]=x;
}
void sPop()
{
	if(sEmpty())return;
	top--;
}
//acauto
#define MAX_NODE 200
#define SIGMA_SIZE 128
int trie[MAX_NODE][SIGMA_SIZE];
int trieVal[MAX_NODE];
int fail[MAX_NODE];
void acBuild(char set[][10],int val[],int n)
{
	int i,j,size;
	char *p;
	size=0;
	memset(trie[0],-1,sizeof trie[0]);
	trieVal[0]=-1;
	//insert strings
	for(i=0;i<n;++i)
	{
		for(p=set[i],j=0;*p;++p)
		{
			if(trie[j][*p]==-1)
			{
				trie[j][*p]=++size;
				memset(trie[size],-1,sizeof trie[size]);
				trieVal[size]=-1;
			}
			j=trie[j][*p];
		}
		trieVal[j]=val[i];
	}
	//construct fail[]
	qClear();
	for(i=0;i<SIGMA_SIZE;++i)
	{
		int *t=&trie[0][i];
		if(*t==-1)*t=0;
		else
		{
			fail[*t]=0;
			qPush(*t);
		}
	}
	while(!qEmpty())
	{
		j=qFront();
		qPop();
		for(i=0;i<SIGMA_SIZE;++i)
		{
			int *t=&trie[j][i];
			if(*t==-1)*t=trie[fail[j]][i];
			else
			{
				fail[*t]=trie[fail[j]][i];
				qPush(*t);
			}
		}
	}
}
int acSearch(char s[])
{
	int i,j,ret=0;
	for(i,j=0;*s;++s)
	{
		i=j=trie[j][*s];
		while(i)
		{
			//printf("i:%d\n",i);
			if(trieVal[i]!=-1)ret+=trieVal[i];
			i=fail[i];
		}
	}
	return ret;
}
