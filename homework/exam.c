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
if(s[i] == '/' && s[i+1] == '/')
			{
				flag1=0;
			}
			else if(flag1 == 1 && ((s[i] =='/' && s[i+1] == '*' && flag2 == 1) || (s[i] =='*' && s[i+1] == '/' && flag2 == 0)))
			{
				flag2^=1;
			}
			
			else if(flag == 1 && flag2 == 1 && s[i] == '\"')
			{
				flag3^=flag3;
			}
			
			else if(flag == 1 && flag2 == 1 && flag3 == 1 && s[i] == '\'')
			{
				flag4^=flag4;
			}
			
			else if((IfLeftBrace(buff[i]) || IfRightBrace(buff[i])) && flag1 && flag2 && flag3 && flag4)
			{
				sign[p].brace=buff[i];
				sign[p].line=cnt;
				p++;
			}
*/

typedef struct node
{
	char brace;
	int line;
}node;

node sign[5000];
char buff[1000];
node stack[5000];
int top;

int IfLeftBrace(char c)
{
	if(c == '(' || c == '{')return 1;
	else return 0;
}

int IfRightBrace(char c)
{
	if( c == ')' || c == '}')return 1;
	else return 0;
}

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

int IfMatch(char left, char right)
{
	if(left == '(' && right == ')')return 1;
	if(left == '{' && right == '}')return 1;
	return 0;
}

node GetTop()
{
	return stack[top-1];
}

int GetSign()
{
	FILE *fp=fopen("example.c","r");
	int cnt=0,len,p=0,i;
	int flag1=1,flag2=1,flag3=1,flag4=1;
	
	while(fgets(buff,MAX,fp) != NULL)
	{	
		cnt++;
		len=strlen(buff);
		
		flag3=1;
		
		for(i=0; i<len; i++)
		{
			/*if(buff[i] == '\'' )
			{
				if(flag1 == 1)flag1=0;
				else flag1=1;
			}*/
			if(buff[i] == '\"')
			{
				flag2=flag2^1;
			}
			else if(buff[i] == '/' && buff[i+1] == '/')
			{
				flag3=0;
			}
			else if((buff[i] == '/' && buff[i+1] == '*' && flag4 == 1) || (buff[i] == '*' && buff[i+1] == '/' && flag4 == 0))
			{
				flag4=flag4^1;
			}
			
			else if((IfLeftBrace(buff[i]) || IfRightBrace(buff[i])) && flag1 && flag2 && flag3 && flag4)
			{
				sign[p].brace=buff[i];
				sign[p].line=cnt;
				p++;
			}
		}
	}
	return p;
}

int Match(int p)
{
	int i;
	node tmp;
	
	for(i=0; i<p; i++)
	{
		
		if(IfLeftBrace(sign[i].brace))
		{
			
			if(IfEmpty() != 1)
			{
				tmp=GetTop();
				if(tmp.brace == '(' && sign[i].brace == '{')
				{
					printf("without maching '(' at line %d",stack[top-1].line);
					return 0;
				}
				else
				{
					Push(sign[i]);
				}
				
			}
			else
			{
				Push(sign[i]);
			}
		}
		
		if(IfRightBrace(sign[i].brace))
		{
			if(IfEmpty())
			{
				printf("without maching '%c' at line %d",sign[i].brace,sign[i].line);
				return 0;
			}
			else
			{
				tmp=Pop();
				if(IfMatch(tmp.brace,sign[i].brace) == 0)
				{
					printf("without maching '%c' at line %d",sign[i].brace,sign[i].line);
					return 0;
				}
			}
		}
	}
	
	if(IfEmpty() != 1)
	{
		tmp=Pop();
		printf("without maching '%c' at line %d",tmp.brace,tmp.line);
		return 0;
	}
	
	return 1;
		
}

int main(){
	//freopen("input.txt","r",stdin);
	
	
	int i,p,flag;

	
	p=GetSign();

	flag=Match(p);
	
	if(flag == 1)
		for(i=0; i<p; i++)
		{
			printf("%c",sign[i].brace);
		}

	//fclose(stdin);
	return 0;
}

