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

#define NUM 0
#define OP 1
/*
��׺תǰ׺

1+((2+3)��4)-5

��ѭ���²��裺
(1) ��ʼ������ջ�������ջS1�ʹ����м�����ջS2��
(2) ��������ɨ����׺���ʽ��


(3) ����������ʱ������ѹ��S2��


(4) ���������ʱ���Ƚ�����S1ջ������������ȼ���
(4-1) ���S1Ϊ�գ���ջ�������Ϊ�����š�)������ֱ�ӽ����������ջ��
(4-2) ���������ȼ���ջ��������Ľϸ߻���ȣ�Ҳ�������ѹ��S1��
(4-3) ���򣬽�S1ջ���������������ѹ�뵽S2�У��ٴ�ת��(4-1)��S1���µ�ջ���������Ƚϣ�


(5) ��������ʱ��
(5-1) ����������š�)������ֱ��ѹ��S1��
(5-2) ����������š�(���������ε���S1ջ�������������ѹ��S2��ֱ������������Ϊֹ����ʱ����һ�����Ŷ�����


(6) �ظ�����(2)��(5)��ֱ�����ʽ������ߣ�


(7) ��S1��ʣ�����������ε�����ѹ��S2��
(8) ���ε���S2�е�Ԫ�ز�����������Ϊ��׺���ʽ��Ӧ��ǰ׺���ʽ��
*/
//˵��ջԪ�ص����� 
typedef struct snode
{
	int sign;
	int flag;	
} 
Selement;
//˵������Ԫ�ص����� 
/*typedef struct qnode
{
	int sign;
	int flag;	
} 
Qelement;*/

typedef Selement Qelement;

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
 

int GetSym(int* buff)
{
	int c;
	int num=0;
	
	do
	{
		c=getchar();
	}while(c != '=' && c != '+' && c != '-' && c != '*' && c != '/' && c != '(' && c != ')' && c != '%' && isdigit(c) == 0);
	
	if(isdigit(c))
	{
		num=0;
		
		do
		{
			num=num*10+c-'0';
		}while(isdigit(c=getchar()));
		
		*buff=num;
		ungetc(c, stdin);
		return NUM;
	}
	else
	{
		*buff=c;
		return OP;
	}
}

int Order(int c)
{
	switch(c)
	{
		case '#':
			return 0;
		case '(':
			return 1;
		case '+':
		case '-':
			return 2;
		case '*':
		case '/':
		case '%':
			return 3;
	}
}

void Process(Selement value, stack sign, queue postfix)
{
	//e3(value.sign)
	Selement tmp;
	//������ֵȺţ���ô��Ҫ�ѷ���ջ��� 
	if(value.sign == '=')
	{
		while(1)
		{
			tmp=Pop(sign);
			if(tmp.sign == '#')break;
			Enqueue(postfix, tmp);
		}
	}
	//������֣�����Ҫ�� ( ֮�ϵ�ջ���
	//(��Ҫ�����������۵�ԭ�����������ȼ������� = �����ã��������ǲ�ϣ�������ġ� 
	else if(value.sign == ')')
	{
		while(1)
		{
			tmp=Pop(sign);
			if(tmp.sign == '(')break;			
			Enqueue(postfix, tmp);
		}
	}
	//������Ϊ�� ������ջ���Ҳ���ջ���⵼�����ȼ��Ǹ����ģ���������������ء� 
	else if(value.sign == '(')
	{
		Push(sign, value);
	}
	else
	{
		while(Order(GetTop(sign).sign) >= Order(value.sign))
		{
			tmp=Pop(sign);
			//e3(tmp.sign)
			Enqueue(postfix, tmp);
		}
		Push(sign, value);
	}
	//printf("\n");
} 

int main()
{
	queue postfix=InitQueue(200);
	stack sign=InitStack(200);
	
	Selement tmp;
	tmp.flag=OP;
	tmp.sign='#';
	Push(sign, tmp);
	
	while(1)
	{
		tmp.flag=GetSym(&(tmp.sign));
		
		if(tmp.flag == NUM)
		{
			Enqueue(postfix, tmp);	
		}
		if(tmp.flag == OP)
		{
			Process(tmp, sign, postfix);
			
			if(tmp.sign == '=')
				break;
		} 
	}
	
	while(!IsQueueEmpty(postfix))
	{
		tmp=Dequeue(postfix);
		if(tmp.flag == NUM)
		{
			printf("%d ", tmp.sign);
		}
		else
		{
			printf("%c ", tmp.sign);
		}
	}

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



