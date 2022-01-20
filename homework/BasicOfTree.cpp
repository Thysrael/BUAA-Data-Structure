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
	//��Ӧ�����������Ľڵ��ɾ������� 
	else if(t->lchild && t->rchild)
	{
		//����ô����������ң����Ҫ�������������ֵ�ˣ�ֻ�������������������Ҫ���� 
		tmp=FindMin(t->rchild);
		t->data=tmp->data;
		t->rchild=Delete(t->rchild, tmp->data);
	}
	//��Ӧֻ�� 0 ���� 1 ��������ɾ������� 
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


