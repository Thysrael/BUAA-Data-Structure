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
13
50 38 30 64 58 40 10 73 70 50 60 100 35
*/

typedef struct node
{
	int num;
	struct node *lchild;
	struct node *rchild;
}node;


void Insert(int key,node** cur)
{
	if(*cur == NULL)
	{
		*cur=(node*)malloc(sizeof(node));
		(*cur)->num=key;
		(*cur)->lchild=NULL;
		(*cur)->rchild=NULL;
	}
	else
	{
		if((*cur)->num>key)
		{
			Insert(key, &((*cur)->lchild));
		}
		else if((*cur)->num<=key)
		{
			Insert(key, &((*cur)->rchild));
		}
	}
} 

void TravIn(node *cur, int height)
{
	if(cur)
	{
		TravIn(cur->lchild,height+1);
		if(cur->lchild == NULL && cur->rchild == NULL)printf("%d %d\n",cur->num,height);
		TravIn(cur->rchild,height+1);
	}
}


int main(){
	//freopen("input.txt","r",stdin);

	int n;
	int num;
	
	scanf("%d",&n);
	node* tree=NULL;

	while(n--)
	{
		scanf("%d",&num);
		Insert(num,&tree);
	}

	TravIn(tree,1);


	//fclose(stdin);
	return 0;
}

