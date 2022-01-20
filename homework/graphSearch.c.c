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
//邻接矩阵，当adjm[u][v]是 1 的时候就是u，v两个点联通 
int adjm[200][200];
//用来储存最终答案的顺序 
int seq[200];
//顶点的个数 
int n;
//一个辅助队列，用于实现 BFS 
int queue[200];
int front;
int rear;
//一个辅助数组，用于标记是否已经遍历过这个点，vis[i]=1 说明 i 这个节点已经被遍历过了 
int vis[200];
//用来说明 DFS 已经遍历过的节点的个数，比如DFSCur=2，说明已经遍历过了2个节点 
int DFSCur;
//相关的队列操作都是为了辅助进行BFS
//入队 
void Enqueue(int value)
{
	queue[rear]=value;
	rear=(rear+1)%QLEN;	
}
//出队 
int Dequeue()
{
	int tmp=front;
	front=(front+1)%QLEN;
	return queue[tmp];	
}
//检验队空 
int IfEmpty()
{
	if(rear == front)return 1;
	else return 0;
}
//检验这个节点是否满足入队的要求，是BFS的辅助函数 
int Check(int start, int end)
{
	//如果start起点和 end 终点之间有通路，且 end 节点还没被遍历，就让end入队 
	if(adjm[start][end] == 1 && vis[end] == 0)return 1;
	else return 0;
}
//打印函数，用于输出最后结果 
void Print(int k)
{
	for(int i=0 ;i<k; i++)
	{
		printf("%d ",seq[i]);
	}
	
	printf("\n");
}
//start 表示从start节点开始遍历 
void BFS(int start)
{
	//SeqCur 与 DFSCur 类似，用于说明BFS已经遍历过的节点个数，用于辅助seq数组的记录 
	int SeqCur=0;
	//要清零，因为seq会被BFS和DFS公用，所以要清出“历史记录” 
	memset(seq, 0, n*sizeof(int));
	memset(vis, 0, n*sizeof(int));
	//对开始节点进行这样的操作 
	seq[SeqCur++]=start;
	vis[start]=1;
	//操作节点入队 
	Enqueue(start);
	//循环知道队空为止 
	while(IfEmpty() == 0)
	{
		//出队 
		int tmp=Dequeue();
		//依次检验每个节点 
		for(int i=0; i<n; i++)
		{
			if(Check(tmp,i))
			{
				//如果符合条件（条件就是Check函数），那么就可以遍历 
				seq[SeqCur++]=i;
				//标记一下已经访问过了 
				vis[i]=1;
				//把新的节点入队，这里不好理解，你画个图自己模拟一遍 BFS 队列操作，体会一下广度优先 
				Enqueue(i);
			}
		}
	}
}

//pos 节点记录的是当前的访问位置，num就是 n，总共的节点个数 
void DFS(int pos, int num)
{	
	//记录一下当前已经被访问了 
	seq[DFSCur++]=pos;
	//记录一下被访问了 
	vis[pos]=1;
	
	if(DFSCur == num)
	{
		//如果已经访问节点个数DFSCur和 num相等，说明可以输出了 
		for(int i=0; i<num; i++)
		{
			printf("%d ", seq[i]);
		}
		printf("\n");
		
		return ;
	}
	
	for(int i=0; i<n; i++)
	{
		if(Check(pos,i))
		{
			//如果可以遍历，就DFS新的节点，这是递归的思想 
			DFS(i, num);
		}
	}
}

//删除节点，很好理解，就是把邻接矩阵相关行列置0。 
void DeleteVertex(int pos)
{
	for(int i=0; i<n; i++)
	{
		adjm[pos][i]=adjm[i][pos]=0;	
	}	
} 

int main()
{
	int m;
	int v,w;
	int point;
	
	scanf("%d%d",&n,&m);
	
	for(int i=0; i<m; i++)
	{
		scanf("%d%d",&v,&w);
		adjm[v][w]=adjm[w][v]=1;
	}
	
	scanf("%d",&point);
	
	DFS(0, n);	
	BFS(0);
	Print(n);

	DeleteVertex(point);

	memset(seq, 0, n*sizeof(int));
	memset(vis, 0, n*sizeof(int));
	DFSCur=0;
		
	DFS(0, n-1);
	BFS(0);
	Print(n-1);





	return 0;
}


