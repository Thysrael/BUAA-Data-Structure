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
#define MOD 11881376
/*

*/
//˵��ջԪ�ص����� 
typedef struct element
{
	char name[50];
	char order[10];
	int dis;
} 
Selement;
//˵������Ԫ�ص����� 
typedef char 
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



