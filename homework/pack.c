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

*/
//说明栈元素的类型 
typedef 
char 
Selement;
//说明队列元素的类型 
typedef 
char 
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
 

queue QueueList[200];
char s[2000];


int main()
{
	int n,m,StackSize,order,AnsPos=0;
	
	char tmp;
	
	scanf("%d%d%d", &n, &m, &StackSize);

	for(int i=1; i<=n; i++)
	{
		QueueList[i]=InitQueue(m+100);
		scanf("%s", s);
		
		for(int j=0; j<m; j++)
		{
			Enqueue(QueueList[i], s[j]);
		}
	}
	
	stack bucket=InitStack(StackSize);
	
	while(1)
	{
		scanf("%d", &order);

		if(order == -1)
		{
			break;
		}
		else if(order == 0)
		{
			if(IsStackEmpty(bucket) == 1)continue;
			else
			{
				printf("%c", Pop(bucket));
			}

		}
		else
		{
			if(!IsQueueEmpty(QueueList[order]))
				tmp=Dequeue(QueueList[order]);
			else
				continue;
				
			if(IsStackFull(bucket))
			{
				printf("%c", Pop(bucket));
				//ans[AnsPos++]=Pop(bucket);
			}
			
			Push(bucket, tmp);

		}
	}
	/*e1(AnsPos)
	for(int i=1; i<n; i++)
	{
		printf("%d ",i);
		e1(QueueList[i]->front)
	}*/

	/*for(int i=0; i<AnsPos; i++)
	{
		printf("%c",ans[i]);
	}*/
	

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
		printf("Stack is full.\n");
		exit(0);
	}	
}

Selement Pop(stack s)
{
	if(!IsStackEmpty(s))
		return s->base[--s->top];
	else
	{
		printf("Stack is empty.\n");
		exit(0);
	}
}

Selement GetTop(stack s)
{
	if(!IsStackEmpty(s))
		return s->base[s->top-1];
	else
	{
		printf("Stack is empty.\n");
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
		printf("Queue is full.\n");
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
		printf("Queue is empty.\n");
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
		printf("Queue is empty.\n");
		exit(0);
	}
} 



