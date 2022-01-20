#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>

#define ValueName(name) (#name)
#define e1(name) printf("%s的值是%d\n",ValueName(name),name);
#define e2(name) printf("%s的值是%s\n",ValueName(name),name);
#define e3(name) printf("%s的值是%c\n",ValueName(name),name);
#define e4(name,n) for(int o=0;o<n;o++)printf("%s[%d]的值是%d\n",ValueName(name),o,name[o]);
#define e5(name,n) for(int o=0;o<n;o++)printf("%s[%d]的值是%f\n",ValueName(name),o,name[o]);
#define e7(name,n) for(int o=0;o<n;o++)printf("%s[%d]的值是%c\n",ValueName(name),o,name[o]);
#define e6 printf("alouha\n");
#define e8(name,value) if(name != value)printf("%s的值不是%d，而是%d\n",ValueName(name),value,name);

#define MAX 100000
#define INF	65535
#define EPS 1e-6
#define QLEN 200
/*

*/

typedef struct vertex
{
	int ischange;
	char name[50];
}vertex;

vertex StationList[1000];
int adjm[1000][1000];

int queue[200];
int rear;
int front;
int path[200];

int dis[1000];
int par[1000];

char name[50];
int VerNum;

void Enqueue(int value)
{
	queue[rear]=value;
	rear=(rear+1)%QLEN;	
}

int Dequeue()
{
	int tmp=front;
	front=(front+1)%QLEN;
	return queue[tmp];	
}

int IfEmpty()
{
	if(rear == front)return 1;
	else return 0;
}

int FindId(char* name)
{
	for(int i=0; i<VerNum; i++)
	{
		if(strcmp(StationList[i].name, name) == 0)
		{
			return i;
		}
	}
	
	return -1;
}

void DrawGraph()
{
	FILE* fp=fopen("bgstations.txt", "r");
	int NumOfLine,LineId,NumOfStation;
	
	fscanf(fp, "%d", &NumOfLine);
	
	for(int i=0; i<NumOfLine; i++)
	{
		int PreStation=-1;
		int ischange,CurStation;
		
		fscanf(fp, "%d%d", &LineId, &NumOfStation);
		
		for(int j=0; j<NumOfStation; j++)
		{
			fscanf(fp, "%s %d", name, &ischange);
			
			CurStation=FindId(name);
			if(CurStation == -1)
			{
				CurStation=VerNum;
				strcpy(StationList[CurStation].name, name);
				StationList[CurStation].ischange=ischange;
				
				if(PreStation != -1)
				{
					adjm[PreStation][CurStation]=adjm[CurStation][PreStation]=LineId;
				}
				
				PreStation=CurStation;
				VerNum++;
			}
			else
			{
				if(PreStation != -1)
				{
					adjm[PreStation][CurStation]=adjm[CurStation][PreStation]=LineId;
				}
				
				PreStation=CurStation;
			}
		}
	}
	fclose(fp);
}

void Unweighted(int StartId, int EndId)
{
	int v,w;
	
	for(int i=0; i<VerNum; i++)
	{
		dis[i]=INF;
	}
	dis[StartId]=0;
	par[StartId]=-1;
	Enqueue(StartId);
	
	while(IfEmpty() == 0)
	{
		v=Dequeue();
		
		for(w=0; w<VerNum; w++)
		{
			if(adjm[v][w] != 0 && dis[w] == INF)
			{
				dis[w]=dis[v]+1;
				par[w]=v;
				
				if(w == EndId) return ;
				
				Enqueue(w);
			}
		}
	}
}

int Recall(int EndId)
{
	int cur=EndId;
	int PathCur=0;
	
	while(cur != -1)
	{
		path[PathCur++]=cur;
		cur=par[cur];
	}
	
	return PathCur;
}

void Print(int PathLen)
{
	int PreStation=path[PathLen-1];
	int CurStation=path[PathLen-2];
	int PreLineId=adjm[PreStation][CurStation];
	printf("%s-%d", StationList[PreStation].name, PreLineId);
	int LineLen=0;
	
	for(int i=PathLen-2; i>=0; i--)
	{
		CurStation=path[i];

		if(PreLineId != adjm[PreStation][CurStation])
		{
			printf("(%d)-%s-%d", LineLen, StationList[PreStation].name, adjm[PreStation][CurStation]);
			PreLineId=adjm[PreStation][CurStation];	
			LineLen=0;
		}
		
		LineLen++;
		PreStation=CurStation;	
	}
	
	printf("(%d)-%s", LineLen, StationList[PreStation].name);
}

int main()
{
	DrawGraph();
	
	scanf("%s", name);
	int StartId=FindId(name);
	scanf("%s", name);
	int EndId=FindId(name);
	
	Unweighted(StartId, EndId);
	
	int PathLen=Recall(EndId);
	
	Print(PathLen);

	
	return 0;
}


