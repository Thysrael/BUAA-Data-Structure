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
A(B(E(K,L),F,G),C(H,I(M,N)),X(J))
A
B(E(K,L),F,G)
C(H,I(M,N))
X(J)

分治算法
拆成子问题
给出基本情况 
合成子答案
 
 
F(100)
max{F(i)+F(100-i)}
table[]
int f(int len)
{
	int max=table[len];
	for(int i=1; i<len; i++)
	{
		if(max<f(i)+f(len-i))max=f(i)+f(len-i);
	}
	return max;
} 
100
0+100
1 99
2 98
3 97
99
0 99
1 98
2 

*/
typedef struct node
{
	char sign;
	struct node* child[10];
}node;

void Insert(char* s, int pos, char c)
{
	int len=strlen(s);
	
	for(int i=len+1; i>pos; i--)
	{
		s[i]=s[i-1];
	}
	
	s[pos]=c;
}

void PreProcess(char* s)
{
	int len=strlen(s);
	
	for(int i=0; i<len; i++)
	{
		if(s[i] == ')')
		{
			Insert(s, i, ',');
			i++;
			len++;
		}
	}
}


node* CreateNode(char c)
{
	node* t=(node*)malloc(sizeof(node));
	t->sign=c;
	for(int i=0; i<10; i++)
	{
		t->child[i]=NULL;
	}
	
	return t;
}

node* BuildTree(char* start, char* end)
{
	node* t=CreateNode(*start);
	char *s,*e;
	int cnt=0;
	int ChildPos=0;
	
	if(start != end)
	{
		char* cur=start+2;
		s=cur;
		
		while(cur != end+1)
		{
			if(*cur == '(')cnt++;
			if(*cur == ')')cnt--;
			
			if((*cur == ',') && cnt == 0)
			{
				e=cur-1;
				t->child[ChildPos++]=BuildTree(s, e);
				s=cur+1;
			}
			
			cur++;
		}
	}
	
	return t;
}


void PostTrav(node* t)
{
	for(int i=0; i<10; i++)
	{
		if(t->child[i] != NULL)
		{
			PostTrav(t->child[i]);
		}
	}
	
	printf("%c ", t->sign);
}

int main()
{
	char s[100];
	scanf("%s", s);
	
	PreProcess(s);
	e2(s)
	char *start, *end;
	start=s;
	end=start+strlen(s)-1;
	
	node* root=BuildTree(start, end);

	PostTrav(root);

	return 0;
}


