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
//script1.exe < input.txt
/*

*/

typedef struct node
{
	int order;
	int start;
}node;

node queue[MAX];
int rear;
int front;
//front指向的下标就是队头元素的下标，rear指向的下标的前一个是队尾元素的下标
//这样是十分和谐的，是简单的，所有都能过的 

void EnQueue(node value)
{
	queue[rear]=value;
	rear=(rear+1)%MAX;
}

int GetLen()
{
	return (rear-front+MAX)%MAX;
}

node DeQueue()
{
	int tmp=front;
	front=(front+1)%MAX;
	return queue[tmp];
}

int IfEmpty()
{
	if(rear == front)return 1;
	else return 0;
}

int IfFull()
{
	if((rear+1)%MAX == front)return 1;
	else return 0;
}

int AddQueue(int NumOfQueue)
{
	//while 判断真的是重中之重，循环不变性一定要好好保持 
	while(NumOfQueue<5)
	{
		if(NumOfQueue*7>GetLen())
			break;
		
		NumOfQueue++;
	}
	
	return NumOfQueue;	
}

void Print(int NumOfQueue,int TimeNow)
{
	for(int i=0; i<NumOfQueue; i++)
	{
		if(IfEmpty() == 0)
		{
			node tmp=DeQueue();
			printf("%d : %d\n",tmp.order,TimeNow-tmp.start);
		}
	}	
}

int ReduceQueue(int NumOfQueue)
{
	while(NumOfQueue>3)
	{
		if((NumOfQueue)*7<=GetLen())
			break;
		
		NumOfQueue--;
	}
	
	return NumOfQueue;	
}

int EnterBank(int num, int cnt, int TimeNow)
{
	while(num--)
	{
		cnt++;
		
		node tmp;
		tmp.order=cnt;
		tmp.start=TimeNow;
		
		EnQueue(tmp);
	}
	
	return cnt;	
}

int main()
{
	//freopen("input.txt","r",stdin);
	int T,TimeNow=0,num,NumOfQueue=3,cnt=0;
	
	scanf("%d",&T);
	
	while(T--)
	{
		TimeNow++;
		scanf("%d",&num);

		cnt=EnterBank(num,cnt,TimeNow);
		
		NumOfQueue=AddQueue(NumOfQueue);
		
		Print(NumOfQueue,TimeNow);
		
		NumOfQueue=ReduceQueue(NumOfQueue);
	}
	
	while(GetLen())
	{
		TimeNow++;
	
		Print(NumOfQueue,TimeNow);
		
		NumOfQueue=ReduceQueue(NumOfQueue);		
	}
	
	//fclose(stdin);
	return 0;
}

