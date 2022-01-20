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

#define MAX 1000
#define INF	65535
#define EPS 1e-6
/*
���õ���Prim����ʵ�֣��ֵ����Լ���ֽ����дģ��һ�£��ͺ�����������
ͼ������㷨�����󣬶�������ͺ��� 
*/
//�ߵĽṹ�壬������Ǳߵı��ID�;���weight 
typedef struct edge
{
	int id;
	int weight;
}edge;
//����ṹ���ڽӾ��󴢴��űߵı�ź;��� 
edge adjm[MAX][MAX];
//����������prim�㷨�ĸ�������
//�� vis[i]=1��˵�� i �ڵ��Ѿ�������С������ 
int vis[MAX];
//dis ��¼������Ϊ����������ʱ���������������С����
//dis�����ܺ;�����С������·��֮�ͣ���������ʱ����������͵����ݣ��ܺ���� 
int dis[MAX];
//��¼�ýڵ�ĸ��ڵ���˭������ par[1]=2��˵�� 1 �ڵ���ͨ��2�ڵ���������С�������ϵ� 
int par[MAX];

//GetSeq�ĸ������飬���ڼ�¼��С��������·����� 
int IdList[MAX];

//������ 
int NumOfVertex;
//���� 
int NumOfEdge;

//dis�����ܺ;�����С������·��֮�� 
void Prim()
{
	//˵���� 0 �Žڵ㿪ʼ���� 
	vis[0]=1;
	//�ȸ���һ�� dis ���� 
	for(int i=0; i<NumOfVertex; i++)
	{
		dis[i]=adjm[0][i].weight;
	}
	//��Ϊ��һ���Ѿ����ǹ��ˣ�����ֻ��Ҫ���������������� NumOfVertex-1 �ξ͹��� 
	for(int i=0; i<NumOfVertex-1; i++)
	{
		//65-76 ������ѡ���µĽڵ������������ѡ��ı�׼�Ǿ�����С������ڵ������� 
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
		
		//��Ϊ�¼�����һ���ڵ㣬����Ҫ����һ��dis�����par���� 
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

//qsort �ĸ�����������С�������� 
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
		//����һ������par����ʵ�ֹ��̣�ͦ�򵥵� 
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
	
	//��ʼ���ڽӾ��󣬰Ѿ��붼��Ϊ INF����� 
	for(int i=0; i<NumOfVertex; i++)
	{
		for(int j=0; j<NumOfVertex; j++)
		{
			adjm[i][j].weight=INF;
		}
	}
	//¼��ߵ���Ϣ�������ݱߵ���Ϣ�޸��ڽӾ��� 
	for(int i=0; i<NumOfEdge; i++)
	{
		int v,u,order,w;
		scanf("%d%d%d%d", &order, &v, &u, &w);
		adjm[v][u].id=adjm[u][v].id=order;
		adjm[v][u].weight=adjm[u][v].weight=w;
	}
	//���� Prim �㷨 
	Prim();
	//�õ����˳��ͦ�򵥵� 
	GetSeq();

	return 0;
}


