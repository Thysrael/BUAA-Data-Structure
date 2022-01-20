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

*/
typedef struct node
{
	int data;
	struct node *lchild, *rchild;
}node;

node* Insert(node* t, int value)
{
	if(t == NULL)
	{
		t=(node*)malloc(sizeof(node));
		t->data=value;
		t->lchild=t->rchild=NULL;
	}
	else if(value < t->data)
	{
		
		t->lchild=Insert(t->lchild, value);
	}
	else
	{
		t->rchild=Insert(t->rchild, value);
	}
	
	return t;
}

void PreTrav(node* t)
{
	if(t)
	{
		printf("%d ", t->data);
		PreTrav(t->lchild);
		PreTrav(t->rchild);
	}
}

node* FindMin(node* t)
{
	if(t == NULL)
	{
		return NULL;
	}
	else if(t->lchild == NULL)
	{
		return t;
	}
	else
	{
		return FindMin(t->lchild);
	}
}

node* Delete(node* t, int value)
{
	node* tmp;
	
	if(t == NULL)
	{
		printf("Not found.\n");
	}
	else if(value < t->data)
	{
		t->lchild=Delete(t->lchild, value);
	}
	else if(value > t->data)
	{
		t->rchild=Delete(t->rchild, value);
	}
	//对应有两个子树的节点别删除的情况 
	else if(t->lchild && t->rchild)
	{
		//如果让从左子树上找，你就要找左子树的最大值了，只有这个代码块里的内容需要更改 
		tmp=FindMin(t->rchild);
		t->data=tmp->data;
		t->rchild=Delete(t->rchild, tmp->data);
	}
	//对应只有 0 或者 1 棵子树被删除的情况 
	else
	{
		tmp=t;
		if(t->lchild == NULL)
		{
			t=t->rchild;
		}
		else if(t->rchild == NULL)
		{
			t=t->lchild;
		}
		
		free(tmp);
	}
	
	return t;
}

int main()
{
	int num;
	node* root=NULL;
	
	for(int i=0; i<6; i++)
	{
		scanf("%d", &num);
		root=Insert(root, num);
	}
	
	//Delete(root, 2);


	PreTrav(root);
	
	return 0;
}


