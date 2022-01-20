#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>

#define ValueName(name) (#name)

#define e1(name) printf("%s的值是%d\n",ValueName(name),name);
#define e2(name) printf("%s的值是%f\n",ValueName(name),name);
#define e3(name) printf("%s的值是%c\n",ValueName(name),name);
#define e4(name,n) for(int o=0;o<n;o++)printf("%s[%d]的值是%d\n",ValueName(name),o,name[o]);
#define e5(name,n) for(int o=0;o<n;o++)printf("%s[%d]的值是%f\n",ValueName(name),o,name[o]);
#define e7(name,n) for(int o=0;o<n;o++)printf("%s[%d]的值是%c\n",ValueName(name),o,name[o]);
#define e6 printf("alouha\n");
#define e8(name,value) if(name != value)printf("%s的值不是%d，而是%d\n",ValueName(name),value,name);

#define status int
#define true 1
#define false 0

#define MAX 100000
#define INF	65535
#define EPS 1e-6
#define MOD 99999

#define EX 0
#define COM 1
#define PRINT 2
//script1.exe < input.txt
/*

*/

typedef struct node
{
	int type;
	
	int port[9];
	
	int order;
	
	int step;
	int pre;
	
}node;

node tree[MOD];
int num=1;
int min=0;
int vis[MOD];

int queue[MAX];
int front=0;
int rear=0;

int IfEmpty()
{
	if(rear == front)return 1;
	else return 0;
}

void EnQueue(int value)
{
	queue[rear]=value;
	rear=(rear+1)%MAX;
}

int DeQueue()
{
	int tmp=front;
	front=(front+1)%MAX;
	return queue[tmp];
}

void TravPre(int start)
{
	tree[start].order=num;
	num++;
	
	/*e1(start)
	e1(tree[start].order)
	printf("\n");*/
	
	for(int i=0; i<8; i++)
	{
		if(tree[start].port[i] != -1)
		{
			TravPre(tree[start].port[i]);
		}
	}
}

int Check(int tmp)
{
	if(tmp == -1)return 0;
	else if(vis[tmp] == 1)return 0;
	else
		return 1;
}


void BFS(int start)
{
	vis[start]=1;
	tree[start].pre=-1;
	tree[start].step=0;
	
	EnQueue(start);
	
	while(IfEmpty() == 0)
	{
		int tmp=DeQueue();
		
		for(int i=0; i<9; i++)
		{
			if(Check(tree[tmp].port[i]))
			{
				//e1(tree[tmp].port[i])
				
				vis[tree[tmp].port[i]]=1;
				tree[tree[tmp].port[i]].pre=tmp;
				tree[tree[tmp].port[i]].step=tree[tmp].step+1;
				
				EnQueue(tree[tmp].port[i]);
			}
		}
	}
}

void TravPrint(int start)
{
	/*e1(start)
	e1(tree[start].step)
	printf("\n");*/
	
	for(int i=0; i<8; i++)
	{
		if(tree[start].port[i] != -1)
		{
			TravPrint(tree[start].port[i]);
		}
	}
}

int FindMin(int start)
{
	/*e1(start)
	e1(tree[start].step)
	e1(min)
	e1(tree[min].step)
	printf("\n");*/
	
	if(tree[start].step<tree[min].step && tree[start].type == PRINT)
	{
		min=start;
	}
	else if(tree[start].step == tree[min].step && tree[start].type == PRINT && tree[start].order < tree[min].order)
	{
		min=start;
	}
	for(int i=0; i<8; i++)
	{
		if(tree[start].port[i] != -1)
		{
			//e1(tree[start].port[i])
			FindMin(tree[start].port[i]);
		}
	}
}

void Recall()
{
	int cur=min;
	int path[300];
	int i,j;
	
	for(i=0; cur != -1; cur=tree[cur].pre,i++)
	{
		path[i]=cur;
		//e1(cur)
	}
	//e1(i)
	for(j=i-2; j>=1; j--)
	{
		printf("%d ",path[j]);
	}
}

int main(){
	//freopen("input.txt","r",stdin);
	FILE* fp=fopen("in.txt","r");
	int n,start,id,type,par,port,i;
	
	scanf("%d %d",&n,&start);
	
	fscanf(fp,"%d %d %d %d",&id,&type,&par,&port);
	for(i=0; i<9; i++)
	{
		tree[0].port[i]=-1;
	}
	tree[0].type=EX;
	n--;
	
	while(n--)
	{
		fscanf(fp,"%d %d %d %d",&id,&type,&par,&port);
		id%=MOD;
		par%=MOD;
		
		tree[id].type=type;
		tree[par].port[port]=id;
		
		if(type == PRINT)min=id;
		
		for(i=0; i<8; i++)
		{
			tree[id].port[i]=-1;
		}
		tree[id].port[8]=par;
		tree[id].pre=-1;
	}

	TravPre(0);
	
	BFS(start);
	
	TravPrint(0);
	
	FindMin(0);
	
	printf("%d ",min);
	
	Recall();
	
	fclose(fp);
	return 0;
}

