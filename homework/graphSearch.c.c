#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>

#define ValueName(name) (#name)
#define e1(name) printf("%s��ֵ��%d\n",ValueName(name),name);
#define e2(name) printf("%s��ֵ��%s\n",ValueName(name),name);
#define e3(name) printf("%s��ֵ��%c\n",ValueName(name),name);
#define e4(name,n) for(int o=0;o<n;o++)printf("%s[%d]��ֵ��%d\n",ValueName(name),o,name[o]);
#define e5(name,n) for(int o=0;o<n;o++)printf("%s[%d]��ֵ��%f\n",ValueName(name),o,name[o]);
#define e7(name,n) for(int o=0;o<n;o++)printf("%s[%d]��ֵ��%c\n",ValueName(name),o,name[o]);
#define e6 printf("alouha\n");
#define e8(name,value) if(name != value)printf("%s��ֵ����%d������%d\n",ValueName(name),value,name);

#define MAX 100000
#define INF	65535
#define EPS 1e-6
#define QLEN 200
/*

*/
//�ڽӾ��󣬵�adjm[u][v]�� 1 ��ʱ�����u��v��������ͨ 
int adjm[200][200];
//�����������մ𰸵�˳�� 
int seq[200];
//����ĸ��� 
int n;
//һ���������У�����ʵ�� BFS 
int queue[200];
int front;
int rear;
//һ���������飬���ڱ���Ƿ��Ѿ�����������㣬vis[i]=1 ˵�� i ����ڵ��Ѿ����������� 
int vis[200];
//����˵�� DFS �Ѿ��������Ľڵ�ĸ���������DFSCur=2��˵���Ѿ���������2���ڵ� 
int DFSCur;
//��صĶ��в�������Ϊ�˸�������BFS
//��� 
void Enqueue(int value)
{
	queue[rear]=value;
	rear=(rear+1)%QLEN;	
}
//���� 
int Dequeue()
{
	int tmp=front;
	front=(front+1)%QLEN;
	return queue[tmp];	
}
//����ӿ� 
int IfEmpty()
{
	if(rear == front)return 1;
	else return 0;
}
//��������ڵ��Ƿ�������ӵ�Ҫ����BFS�ĸ������� 
int Check(int start, int end)
{
	//���start���� end �յ�֮����ͨ·���� end �ڵ㻹û������������end��� 
	if(adjm[start][end] == 1 && vis[end] == 0)return 1;
	else return 0;
}
//��ӡ������������������ 
void Print(int k)
{
	for(int i=0 ;i<k; i++)
	{
		printf("%d ",seq[i]);
	}
	
	printf("\n");
}
//start ��ʾ��start�ڵ㿪ʼ���� 
void BFS(int start)
{
	//SeqCur �� DFSCur ���ƣ�����˵��BFS�Ѿ��������Ľڵ���������ڸ���seq����ļ�¼ 
	int SeqCur=0;
	//Ҫ���㣬��Ϊseq�ᱻBFS��DFS���ã�����Ҫ�������ʷ��¼�� 
	memset(seq, 0, n*sizeof(int));
	memset(vis, 0, n*sizeof(int));
	//�Կ�ʼ�ڵ���������Ĳ��� 
	seq[SeqCur++]=start;
	vis[start]=1;
	//�����ڵ���� 
	Enqueue(start);
	//ѭ��֪���ӿ�Ϊֹ 
	while(IfEmpty() == 0)
	{
		//���� 
		int tmp=Dequeue();
		//���μ���ÿ���ڵ� 
		for(int i=0; i<n; i++)
		{
			if(Check(tmp,i))
			{
				//���������������������Check����������ô�Ϳ��Ա��� 
				seq[SeqCur++]=i;
				//���һ���Ѿ����ʹ��� 
				vis[i]=1;
				//���µĽڵ���ӣ����ﲻ����⣬�㻭��ͼ�Լ�ģ��һ�� BFS ���в��������һ�¹������ 
				Enqueue(i);
			}
		}
	}
}

//pos �ڵ��¼���ǵ�ǰ�ķ���λ�ã�num���� n���ܹ��Ľڵ���� 
void DFS(int pos, int num)
{	
	//��¼һ�µ�ǰ�Ѿ��������� 
	seq[DFSCur++]=pos;
	//��¼һ�±������� 
	vis[pos]=1;
	
	if(DFSCur == num)
	{
		//����Ѿ����ʽڵ����DFSCur�� num��ȣ�˵����������� 
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
			//������Ա�������DFS�µĽڵ㣬���ǵݹ��˼�� 
			DFS(i, num);
		}
	}
}

//ɾ���ڵ㣬�ܺ���⣬���ǰ��ڽӾ������������0�� 
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


