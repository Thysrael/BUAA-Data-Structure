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
	int array[1000];
	int top;
}stack;

char s[MAX];

int GetTop(stack *a)
{
	return a->array[a->top-1];
}

void Push(int value, stack *a)
{
	a->array[a->top++]=value;
}

void Pop(stack * a)
{
	a->top--;
}

status IfEmpty(stack *a)
{
	if(a->top == 0)return true;
	else return false;
}

stack* InitStack()
{
	stack* a=(stack*)malloc(sizeof(stack));
	a->top=0;
	
	return a;
}

int Order(char c)
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

int Cal(int a, int b, char c)
{
	switch (c)
	{
		case '+':
			return a+b;
		case '-':
			return a-b;
		case '*':
			return a*b;
		case '/':
			return a/b;
		case '%':
			return a%b;
	}
	
}

void Operate(stack* num, stack *sign,char tmp)
{
	int tmp1,tmp2,tmp3;
	
	tmp1=GetTop(num);
	Pop(num);
	tmp2=GetTop(num);
	Pop(num);
			
	tmp3=Cal(tmp2,tmp1,tmp);
	Push(tmp3,num);	
}

void Process(char c, stack* num, stack* sign)
{
	char tmp;
	int tmp1,tmp2,tmp3;
	if(c == '=')
	{
		while(1)
		{
			tmp=GetTop(sign);
			Pop(sign);
			if(tmp == '#')break;

			Operate(num,sign,tmp);			
		}
	}
	else if(c == ')')
	{
		while(1)
		{
			tmp=GetTop(sign);
			Pop(sign);
			if(tmp == '(')break;
			
			Operate(num,sign,tmp);			
		}
	}
	else if(c == '(')
	{
		Push(c,sign);
	}
	
	else
	{
		while(1)
		{
			tmp=GetTop(sign);
			if(Order(tmp)<Order(c))
			{
				Push(c,sign);
				break;
			}
			else
			{
				Pop(sign);

				Operate(num,sign,tmp);					
			}
		}
	}
}

int main(){
	//freopen("input.txt","r",stdin);
	int i,tmp=0,len,pre=1;
	
	stack* num=InitStack();
	stack* sign=InitStack();
	Push('#',sign);
	
	gets(s);
	len=strlen(s);

	for(i=0; i<len; i++)
	{
		if(isdigit(s[i]))
		{
			pre=0;
			tmp=tmp*10+s[i]-'0';
		}
		
		else if(s[i] != ' ')
		{
			if(pre == 0)
			{
				Push(tmp,num);
				tmp=0;
				pre=1;
			}
			
			Process(s[i],num,sign);
		}
	}
	
	printf("%d",num->array[0]);	

	//fclose(stdin);
	return 0;
}

