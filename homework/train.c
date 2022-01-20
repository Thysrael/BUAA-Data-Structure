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

#define P 10000019
#define MOD 11881376
//script1.exe < input.txt
/*

*/

typedef struct node
{
	char name[50];
	char order[10];
	int dis;
}node;

typedef struct stack
{
	node array[100];
	int top;
}Stack,*stack;

int board[MOD];

stack InitStack()
{
	stack tmp=(stack)malloc(sizeof(Stack));
	return tmp;
}

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

void Push(stack a, node value)
{
	a->array[a->top++]=value;
}

node Pop(stack a)
{
	return a->array[--a->top];
}

int IfEmpty(stack a)
{
	if(a->top == 0)return 1;
	else return 0;
}

int FindMax(stack a)
{
	int max=-1;
	for(int i=0; i<a->top; i++)
	{
		if(a->array[i].dis>max)max=a->array[i].dis;
	}
	
	return max;
}

void InitB(stack b)
{
	int n;
	node tmp;
	
	scanf("%d",&n);
		
	for(int i=n-1; i>=0; i--)
	{
		scanf("%s %s",tmp.order,tmp.name);
		tmp.dis=board[GetKey(tmp.name)];
		b->array[i]=tmp;	
	}
	b->top=n;
}


void Print(stack a, int ans)
{
	for(int i=0; i<a->top; i++)
	{
		printf("%s ",a->array[i].order);
	}
	printf("\n");
	printf("%d",ans);	
}

int main(){
	//freopen("train.txt","r",stdin);
	stack a,b,c;
	int max=-1;
	node tmp;
	int cnt,ans=0;
	
	
	a=InitStack();
	b=InitStack();
	c=InitStack();
	
	GetBoard();

	InitB(b);
	
	while(IfEmpty(b) != 1)
	{
		max=FindMax(b);
		cnt=0;
		while(1)
		{
			tmp=Pop(b);
			Push(a,tmp);
			cnt++;
			
			if(tmp.dis == max)
			{
				break;
			}
		}

	
		if(cnt != 1)
		{
			Push(c,Pop(a));
			
			for(int i=0; i<cnt-1; i++)
			{
				Push(b,Pop(a));
			}
			
			Push(a,Pop(c));
			cnt++;
		}
		
		ans+=cnt;
		e1(ans)
	}
	
	Print(a,ans);

	//fclose(stdin);
	return 0;
}

