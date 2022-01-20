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
/*
5 6
1 0 1
2 0 2
3 1 2
4 1 3
5 3 4
6 1 4

*/

typedef struct edge
{
	int v;
	int w;
}edge;

edge EdgeList[10000];

int NumOfEdge;
int NumOfVertex;

int vis[20000];
int path[20000];
int flag[20000];

void DFS(int pos, int step)
{

	if(pos == NumOfVertex-1)
	{
		for(int i=0; i<step; i++)
		{
			printf("%d ", path[i]);
		}
		printf("\n");
		
		return;
	}
	
	for(int i=0; i<2000; i++)
	{
		if(EdgeList[i].v == pos && flag[i] == 1 && vis[EdgeList[i].w] == 0)
		{
			vis[EdgeList[i].w]=1;
			path[step]=i;
			DFS(EdgeList[i].w, step+1);
			vis[EdgeList[i].w]=0;
		}
		
		if(EdgeList[i].w == pos && flag[i] == 1 && vis[EdgeList[i].v] == 0)
		{
			vis[EdgeList[i].v]=1;
			path[step]=i;
			DFS(EdgeList[i].v, step+1);
			vis[EdgeList[i].v]=0;
		}
	}
}

int main()
{
	scanf("%d %d", &NumOfVertex, &NumOfEdge);
	
	for(int i=0; i<NumOfEdge; i++)
	{
		int order,start,end;
		scanf("%d%d%d",&order, &start, &end);
		
		EdgeList[order].v=start;
		EdgeList[order].w=end;
		flag[order]=1;
	}
	
	//e1(EdgeList[3].v)
	vis[0]=1;
	DFS(0, 0);

	return 0;
}


