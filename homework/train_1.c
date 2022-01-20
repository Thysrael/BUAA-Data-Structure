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
#define MOD 11881376
/*

*/
//说明栈元素的类型 
typedef struct element
{
	char name[50];
	char order[10];
	int dis;
} 
Selement;
//说明队列元素的类型 
typedef char 
Qelement;
//声明结构体，不用管 
typedef struct Queue
{
	Qelement* base;
	int front;
	int rear;
	int QueueSize;
}*queue;

typedef struct Stack
{
	Selement* base;
	int top;
	int StackSize;
}*stack;

stack InitStack(int StackSize);//初始化一个栈 
int IsStackEmpty(stack s);//检测栈是否为空 
int IsStackFull(stack s);//检测栈是否为满 
void Push(stack s, Selement value);//入栈 
Selement Pop(stack s);//弹栈，返回栈顶元素 
Selement GetTop(stack s);//返回栈顶元素 

queue InitQueue(int QueueSize);//初始化一个队列 
int IsQueueEmpty(queue q);//检测队列是否为空 
int IsQueueFull(queue q);//检测队列是否为满 
void Enqueue(queue q, Qelement value);//入队 
Qelement Dequeue(queue q);//出队，返回队头元素 
Qelement GetFront(queue q);//返回队头元素 

int board[MOD];

int GetKey(char* name)
{
	int i,key=0;
	
	for(i=0; i<5; i++)
	{
		key=(key*26+name[i]-'a');
	}
	
	return key;
}
 
void GetBoard()
{
	int n,dis;
	char name[50];
	scanf("%d",&n);
	
	while(n--)
	{
		scanf("%s %d",name,&dis);
		board[GetKey(name)]=dis;
	}
	
}

void InitB(stack a, stack b)
{
	int n;
	Selement tmp;
	scanf("%d", &n);
	
	for(int i=0; i<n; i++)
	{
		scanf("%s %s",tmp.order,tmp.name);
		tmp.dis=board[GetKey(tmp.name)];
		Push(a, tmp);
	}
	for(int i=0; i<n; i++)
	{
		Push(b,Pop(a));
	}
}

int FindMax(stack b)
{
	int max=-1;
	for(int i=0; i<b->top; i++)
	{
		if(b->base[i].dis > max)max=b->base[i].dis;
	}
	
	return max;
}

int main()
{
	stack a=InitStack(100);
	stack b=InitStack(100);
	stack c=InitStack(100);
	
	GetBoard();
	
	InitB(a,b);
	
	int cnt=0,ans=0,max;
	Selement tmp;
	
	while(!IsStackEmpty(b))
	{
		max=FindMax(b);
		cnt=0;
		while(1)
		{
			tmp=Pop(b);
			Push(a, tmp);
			cnt++;
			
			if(tmp.dis == max)
			{
				break;
			}
		}
		
		if(cnt != 1)
		{
			Push(c, Pop(a));
			
			for(int i=0; i<cnt-1; i++)
			{
				Push(b, Pop(a));
			}
			
			Push(a, Pop(c));
			cnt++;
		}
		
		ans+=cnt;
	}

	e1(ans)
	return 0;
}

stack InitStack(int StackSize)
{
	stack s=(stack)malloc(sizeof(struct Stack));
	s->base=(Selement*)malloc(StackSize*sizeof(Selement));
	s->top=0;
	s->StackSize=StackSize;
	return s;
}

int IsStackEmpty(stack s)
{
	if(s->top == 0)return 1;
	else return 0;
}

int IsStackFull(stack s)
{
	if(s->top == s->StackSize)return 1;
	else return 0;
}

void Push(stack s, Selement value)
{
	if(!IsStackFull(s))
		s->base[s->top++]=value;
	else
	{
		printf("%s is full.\n", ValueName(s));
		exit(0);
	}	
}

Selement Pop(stack s)
{
	if(!IsStackEmpty(s))
		return s->base[--s->top];
	else
	{
		printf("%s is empty.\n", ValueName(s));
		exit(0);
	}
}

Selement GetTop(stack s)
{
	if(!IsStackEmpty(s))
		return s->base[s->top-1];
	else
	{
		printf("%s is empty.\n", ValueName(s));
		exit(0);
	}
}

queue InitQueue(int QueueSize)
{
	queue q=(queue)malloc(sizeof(struct Queue));
	q->base=(Qelement*)malloc((QueueSize+1)*sizeof(Qelement));
	q->front=0;
	q->rear=0;
	q->QueueSize=QueueSize;
	return q;
}

int IsQueueEmpty(queue q)
{
	if(q->front == q->rear) return 1;	
	else return 0;
}

int IsQueueFull(queue q)
{
	if((q->rear+1)%q->QueueSize == q->front) return 1;
	else return 0;
}

void Enqueue(queue q, Qelement value)
{
	if(!IsQueueFull(q))
	{
		q->base[q->rear]=value;
		q->rear=(q->rear+1)%q->QueueSize;	
	}
	else
	{
		printf("%s is full.\n",ValueName(q));
		exit(0);
	} 			
}

Qelement Dequeue(queue q)
{
	if(!IsQueueEmpty(q))
	{
		int tmp=q->front;
		q->front=(q->front+1)%q->QueueSize;
		return q->base[tmp];
	}
	else
	{
		printf("%s is empty.\n", ValueName(q));
		exit(0);
	}
} 

Qelement GetFront(queue q)
{
	if(!IsQueueEmpty(q))
	{
		return q->base[q->front];
	}
	else
	{
		printf("%s is empty.\n", ValueName(q));
		exit(0);
	}
} 



