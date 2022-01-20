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
A Stack is a container of objects that are inserted and removed according to the last-in first-out (LIFO) principle.???
4
1 20 ainer
2 0 ???
1 85 -
1 99 (LIFO)

3
2 110 10
1 110 Objects
2 98 1
2 0 1
2 108 10
3
3
3
-1
*/

typedef struct node
{
	int op;
	int pos;
	char str[100];
}node;

node stack[200];
int top;

char s[1000];

int IfEmpty()
{
	if(top == 0)return 1;
	else return 0;
}

void Push(node value)
{
	stack[top++]=value;
}

node Pop()
{
	return stack[--top];
}

void Move(int len, int pos, int dir)
{
	int lens=strlen(s);
	int i;
	
	if(dir == 1)
	{
		//e1(lens)
		//e1(len)
		//e1(pos)
		
		for(i=lens; i>=pos; i--)
		{
			//e1(s[i])
			//e3(s[i])
			s[i+len]=s[i];
		}
	}

	if(dir == 2)
	{
		if(pos+len>=lens)len=lens-pos;
		for(i=pos+len; i<=lens; i++)
		{
			
			//e1(s[i])
			s[i-len]=s[i];
		}
	}
}

void Init()
{
	int n,i;
	node tmp;
	char buff[100];
	
	gets(s);
	scanf("%d",&n);
		
	for(i=0; i<n; i++)
	{
		scanf("%d %d %s",&tmp.op,&tmp.pos,&tmp.str);
		Push(tmp);
	}
	getchar();
	gets(buff);
}

void Process()
{
	int order,pos,len,i;
	char con[600];
	node tmp;
	
	while(1)
	{
		scanf("%d",&order);
	
		if(order == 1)
		{
			scanf("%d %s",&pos,con);
			len=strlen(con);
			Move(len,pos,1);
			
			for(i=pos; i<pos+len; i++)
			{
				s[i]=con[i-pos];
			}
			
			tmp.op=1;
			tmp.pos=pos;
			strcpy(tmp.str,con);
			
			Push(tmp);
			//printf("%s\n",s);
		}
		
		else if(order == 2)
		{
			scanf("%d %d",&pos,&len);
			
			for(i=pos; i<pos+len; i++)
			{
				tmp.str[i-pos]=s[i];
			}
			tmp.str[i-pos]='\0';
			tmp.op=2;
			tmp.pos=pos;
			Push(tmp);
			
			Move(len,pos,2);
			
			//printf("%s\n",s);
		}
		else if(order == 3)
		{
			if(IfEmpty() == 1)continue;
			
			tmp=Pop();

			if(tmp.op == 1)
			{
				len=strlen(tmp.str);
				Move(len,tmp.pos,2);
			}
			else if(tmp.op == 2)
			{
				len=strlen(tmp.str);

				Move(len,tmp.pos,1);
				for(i=tmp.pos; i<tmp.pos+len; i++)
				{
					s[i]=tmp.str[i-tmp.pos];
				}
			}
			//printf("%s\n",s);
		}
		else
		{
			break;
		}
	}
}

int main(){
	//freopen("example.c","r",stdin);

	Init();
	Process();

	printf("%s",s);


	//fclose(stdin);
	return 0;
}

