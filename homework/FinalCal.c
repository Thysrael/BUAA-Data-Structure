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

#define NUM 0
#define OP 1
/*
中缀转前缀

1+((2+3)×4)-5

遵循以下步骤：
(1) 初始化两个栈：运算符栈S1和储存中间结果的栈S2；
(2) 从右至左扫描中缀表达式；


(3) 遇到操作数时，将其压入S2；


(4) 遇到运算符时，比较其与S1栈顶运算符的优先级：
(4-1) 如果S1为空，或栈顶运算符为右括号“)”，则直接将此运算符入栈；
(4-2) 否则，若优先级比栈顶运算符的较高或相等，也将运算符压入S1；
(4-3) 否则，将S1栈顶的运算符弹出并压入到S2中，再次转到(4-1)与S1中新的栈顶运算符相比较；


(5) 遇到括号时：
(5-1) 如果是右括号“)”，则直接压入S1；
(5-2) 如果是左括号“(”，则依次弹出S1栈顶的运算符，并压入S2，直到遇到右括号为止，此时将这一对括号丢弃；


(6) 重复步骤(2)至(5)，直到表达式的最左边；


(7) 将S1中剩余的运算符依次弹出并压入S2；
(8) 依次弹出S2中的元素并输出，结果即为中缀表达式对应的前缀表达式。
*/
//说明栈元素的类型 
typedef struct snode
{
	int sign;
	int flag;	
} 
Selement;
//说明队列元素的类型 
/*typedef struct qnode
{
	int sign;
	int flag;	
} 
Qelement;*/

typedef Selement Qelement;

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
	//如果出现等号，那么就要把符号栈清空 
	if(value.sign == '=')
	{
		while(1)
		{
			tmp=Pop(sign);
			if(tmp.sign == '#')break;
			Enqueue(postfix, tmp);
		}
	}
	//如果出现），就要把 ( 之上的栈清空
	//(需要单独分类讨论的原因是他的优先级会起到如 = 的作用，这是我们不希望见到的。 
	else if(value.sign == ')')
	{
		while(1)
		{
			tmp=Pop(sign);
			if(tmp.sign == '(')break;			
			Enqueue(postfix, tmp);
		}
	}
	//这是因为（ 必须入栈而且不出栈，这导致优先级是浮动的，还不如分类讨论呢。 
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



