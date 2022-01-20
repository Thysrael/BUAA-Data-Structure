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
/*

*/
//˵��ջԪ�ص����� 
typedef 
char 
Selement;
//˵������Ԫ�ص����� 
typedef 
char 
Qelement;

//�����ṹ�壬���ù� 
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

stack InitStack(int StackSize);//��ʼ��һ��ջ 
int IsStackEmpty(stack s);//���ջ�Ƿ�Ϊ�� 
int IsStackFull(stack s);//���ջ�Ƿ�Ϊ�� 
void Push(stack s, Selement value);//��ջ 
Selement Pop(stack s);//��ջ������ջ��Ԫ�� 
Selement GetTop(stack s);//����ջ��Ԫ�� 

queue InitQueue(int QueueSize);//��ʼ��һ������ 
int IsQueueEmpty(queue q);//�������Ƿ�Ϊ�� 
int IsQueueFull(queue q);//�������Ƿ�Ϊ�� 
void Enqueue(queue q, Qelement value);//��� 
Qelement Dequeue(queue q);//���ӣ����ض�ͷԪ�� 
Qelement GetFront(queue q);//���ض�ͷԪ�� 
 

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



