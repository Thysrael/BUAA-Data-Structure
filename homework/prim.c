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

#define MAX 1000
#define INF	65535
#define EPS 1e-6
/*
采用的是Prim方法实现，兄弟你自己在纸上手写模拟一下，就很容易明白了
图这里的算法都抽象，多做几遍就好了 
*/
//边的结构体，储存的是边的编号ID和距离weight 
typedef struct edge
{
	int id;
	int weight;
}edge;
//这个结构体邻接矩阵储存着边的编号和距离 
edge adjm[MAX][MAX];
//下面三个是prim算法的辅助数组
//若 vis[i]=1，说明 i 节点已经加入最小生成树 
int vis[MAX];
//dis 记录的是在为加入生成树时到生成树各点的最小距离
//dis最后的总和就是最小生成树路径之和，这条性质时后面计算距离和的依据，很好理解 
int dis[MAX];
//记录该节点的父节点是谁，比如 par[1]=2，说明 1 节点是通过2节点连接在最小生成树上的 
int par[MAX];

//GetSeq的辅助数组，用于记录最小生成树的路径编号 
int IdList[MAX];

//顶点数 
int NumOfVertex;
//边数 
int NumOfEdge;

//dis最后的总和就是最小生成树路径之和 
void Prim()
{
	//说明从 0 号节点开始遍历 
	vis[0]=1;
	//先更新一遍 dis 数组 
	for(int i=0; i<NumOfVertex; i++)
	{
		dis[i]=adjm[0][i].weight;
	}
	//因为有一个已经考虑过了，所以只需要更新三个辅助数组 NumOfVertex-1 次就够了 
	for(int i=0; i<NumOfVertex-1; i++)
	{
		//65-76 行是在选出新的节点加入生成树，选择的标准是距离最小生成书节点距离最短 
		int min=INF;
		int child=-1;
		for(int j=0; j<NumOfVertex; j++)
		{
			if(vis[j] == 0 && dis[j] < min)
			{
				min=dis[j];
				child=j;
			}
		}
		vis[child]=1;
		
		//因为新加入了一个节点，所以要更新一下dis数组和par数组 
		for(int j=0; j<NumOfVertex; j++)
		{
			if(vis[j] == 0 && dis[j] > adjm[child][j].weight)
			{
				dis[j]=adjm[child][j].weight;
				par[j]=child;
			}
		}
	}	
}

//qsort 的辅助函数，从小到大排列 
int Cmp(const void* a, const void* b)
{
	int* x=(int*)a;
	int* y=(int*)b;
	
	return *x-*y;
}

void GetSeq()
{
	int cur=0;
	int ans=0;
	
	for(int i=1; i<NumOfVertex; i++)
	{
		//这是一个利用par数组实现过程，挺简单的 
		IdList[cur++]=adjm[i][par[i]].id;
		ans+=adjm[i][par[i]].weight;
	}
	
	printf("%d\n", ans);
	
	qsort(IdList, NumOfVertex-1, sizeof(int), Cmp);
	
	for(int i=0; i<NumOfVertex-1; i++)
	{
		printf("%d ",IdList[i]);
	}
}

int main()
{
	
	scanf("%d%d", &NumOfVertex, &NumOfEdge);
	
	//初始化邻接矩阵，把距离都设为 INF（无穷） 
	for(int i=0; i<NumOfVertex; i++)
	{
		for(int j=0; j<NumOfVertex; j++)
		{
			adjm[i][j].weight=INF;
		}
	}
	//录入边的信息，并根据边的信息修改邻接矩阵 
	for(int i=0; i<NumOfEdge; i++)
	{
		int v,u,order,w;
		scanf("%d%d%d%d", &order, &v, &u, &w);
		adjm[v][u].id=adjm[u][v].id=order;
		adjm[v][u].weight=adjm[u][v].weight=w;
	}
	//进行 Prim 算法 
	Prim();
	//得到输出顺序，挺简单的 
	GetSeq();

	return 0;
}


