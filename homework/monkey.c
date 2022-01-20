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
	int seq;
	struct node *next;
}node;

int n,m,q;

node* Init()
{
	int i;
	
	node* head=malloc(sizeof(node));
	
	node* pre=head;
	
	for(i=1; i<=n; i++)
	{
		node *cur=malloc(sizeof(node));
		cur->seq=i;
		cur->next=NULL;
		
		pre->next=cur;
		pre=cur;
	}
	pre->next=head;
	
	return head;
}

int CallName(node *head)
{
	int i;
	node *cur=head->next;
	node *pre=head;
	
	for(i=1; i<q; i++)
	{
		cur=cur->next;
		pre=pre->next;
	}
	
		
	
	i=0;
	
	while(1)
	{
		if(cur != head)
		{
			i++;
			
			if(i%m == 0)
			{
				pre->next=cur->next;
				free(cur);
				cur=pre->next;
			}
			else
			{
				pre=cur;
				cur=cur->next;
			}
		}
		else
		{
			pre=cur;
			cur=cur->next;
		}
		

		
		if(cur->next == pre)
		{
			break;
		}
			
	}
}

int main(){
	//freopen("input.txt","r",stdin);
	int ans;
	node* list;
	
	scanf("%d%d%d",&n,&m,&q);

	list=Init();
	
	CallName(list);
	
	printf("%d",list->next->seq);


	//fclose(stdin);
	return 0;
}

