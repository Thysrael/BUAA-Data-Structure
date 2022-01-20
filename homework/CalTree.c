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

#define NUM 0
#define OP 1
//script1.exe < input.txt
/*
24 / ( 1 + 2 + 36 / 6 / 2 - 2) * ( 12 / 2 / 2 )     =
*/

typedef struct node
{
	int value;
	struct node* lchild;
	struct node* rchild;
}node,*tree;

typedef struct snode
{
	tree array[100];
	int top;
}stack;

tree GetTop(stack *a)
{
	return a->array[a->top-1];
}

void Push(tree value, stack *a)
{
	a->array[a->top++]=value;
}

tree Pop(stack * a)
{
	return a->array[--(a->top)];
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
		ungetc(c,stdin);
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

void MakeTree(stack* forest, stack* op, tree tmp)
{
	tree tmp1,tmp2;
	
	tmp1=Pop(forest);
	tmp2=Pop(forest);
	
	tmp->lchild=tmp2;
	tmp->rchild=tmp1;
	
	Push(tmp,forest);
}

void Process(char c, stack* forest, stack* op)
{
	tree tmp,tmp1;
	
	if(c == '=')
	{
		while(1)
		{
			tmp=Pop(op);
			if(tmp->value == '#')break;

			MakeTree(forest, op, tmp);			
		}
	}
	
	else if(c == ')')
	{
		while(1)
		{
			tmp=Pop(op);
			if(tmp->value == '(')break;
			
			MakeTree(forest, op, tmp);			
		}
	}
	
	else if(c == '(')
	{
		tmp1=(tree)malloc(sizeof(node));
		tmp1->value=c;
		tmp1->rchild=NULL;
		tmp1->rchild=NULL;
		
		Push(tmp1, op);
	}
	
	else
	{
		while(1)
		{
			tmp=GetTop(op);

			if(Order(tmp->value) < Order(c))
			{
				tmp1=(tree)malloc(sizeof(node));
				tmp1->value=c;
				tmp1->lchild=NULL;
				tmp1->rchild=NULL;
				
				Push(tmp1, op);
				break;
			}
			
			else
			{
				tmp=Pop(op);

				MakeTree(forest, op, tmp);					
			}
		}
	}
		
}

int Cal(int a, int b, int c)
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

int CalTree(tree root)
{
	if(root->lchild == NULL && root->rchild == NULL)
	{
		return root->value;
	}
	else
	{
		return Cal(CalTree(root->lchild), CalTree(root->rchild), root->value);
	}
}

int main(){
	//freopen("input.txt","r",stdin);
	tree tmp;
	tree root;
	tree first;
	
	int ans;
	
	stack* forest=InitStack();
	stack* op=InitStack();
	
	first=(tree)malloc(sizeof(node));
	first->lchild=NULL;
	first->rchild=NULL;
	first->value='#';
	Push(first, op);
	
	while(1)
	{
		int buff;
		int flag=GetSym(&buff);
		
		if(flag == OP)
		{
			Process(buff, forest, op);
			if(buff == '=')break;
		}
		
		if(flag == NUM)
		{
			tmp=(tree)malloc(sizeof(node));
			tmp->lchild=NULL;
			tmp->rchild=NULL;
			tmp->value=buff;
			
			Push(tmp, forest);
		}
	}
	
	root=Pop(forest);
	//输出计算符 
	printf("%c ",root->value);
	if(root->lchild->lchild == NULL && root->lchild->rchild == NULL)
	{
		printf("%d ",root->lchild->value);
	}
	else
	{
		printf("%c ",root->lchild->value);
	}
	if(root->rchild->lchild == NULL && root->rchild->rchild == NULL)
	{
		printf("%d ",root->rchild->value);
	}
	else
	{
		printf("%c ",root->rchild->value);
	}
	printf("\n");	
	//输出计算值 
	ans=CalTree(root);
	
	printf("%d",ans);
	
	//fclose(stdin);
	return 0;
}

