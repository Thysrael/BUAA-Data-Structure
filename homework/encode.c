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

#define MAX 1000000
#define INF	65535
#define EPS 1e-6
//script1.exe < input.txt
/*

*/

int code[200];
char s[MAX];
char ans[MAX];

typedef struct node
{
	int value;
	struct node *next;
}node;

node* InitKey()
{
	char key[40];
	int len,i;
	int record[150];
	memset(record,0,150*sizeof(int));
	
	node* head=(node*)malloc(sizeof(node));
	node *cur=head;
	
	gets(key);
	
	len=strlen(key);

	for(i=0; i<len; i++)
	{
		if(record[key[i]] == 0)
		{
			record[key[i]]=1;
			
			node* tmp=(node*)malloc(sizeof(node));
			tmp->value=key[i];
			tmp->next=NULL;
			
			cur->next=tmp;
			cur=tmp; 
		}	
	}
	
	for(i=32; i<=126; i++)
	{
		if(record[i] == 0)
		{
			record[i]=1;
			
			node* tmp=(node*)malloc(sizeof(node));
			tmp->value=i;
			tmp->next=NULL;
			
			cur->next=tmp;
			cur=tmp;	
		}	
	}
	
	cur->next=head;
	
	return head; 
}

//这个函数写的 bug 最多，最突出的关注点是语句的执行顺序问题，不能想当然
//算法导论中有循环不变性，当有这种意识 
node* Move(node *pre, int step, node* head)
{
	//这里要预先判断一下，因为删除最后一个节点，有可能cur一上来就指向head 
	if(pre->next == head)
	{
		pre=pre->next;
	}
	
	for(int i=0; i<step-1; i++)
	{
		pre=pre->next;
		
		//每次都要检查cur有没有在head上 
		if(pre->next == head)
		{
			pre=pre->next;
		}
	}
	//两次的位置是很讲究的，外在前检查，内在后检查，也可以内在前，外在后检查 

	code[step]=pre->next->value;
	
	return pre;
}

void GetCode(node *head)
{
	node *cur=head->next;
	node *pre=head;
	int tmp;
	//这里审题需要注意，脑子要清楚 
	int first=cur->value;
	
	//循环链表终止条件，不涉及 head节点，涉及head节点会造成误判 
	//如果写双向链表好像会自然一些，pre实在是太麻烦了 
	while(cur->next != pre)
	{
		tmp=cur->value;

		pre->next=cur->next;
		free(cur);
		
		pre=Move(pre,tmp,head);
		cur=pre->next;
	}
	
	code[cur->value]=first;
}

//在这里因为不熟悉IO函数，导致不自信，应当避免 
void Encode()
{
	freopen("in_crpyt.txt", "w", stdout);
	FILE* f=fopen("in.txt","r");
	
	while(fgets(s,MAX,f) != NULL)
	{
		int len=strlen(s);
		
		for(int i=0; i<len; i++)
		{
			if(isprint((int)s[i]))
				ans[i]=(char)code[s[i]];
			//不审题导致错误 
			else
				ans[i]=s[i];
		}
		
		ans[len]='\0';
		
		printf("%s",ans);
	}

	fclose(f);
	fclose(stdout);
}

void PrintList(node *head)
{
	node* cur=head->next;
	int cnt=0;
	
	while(cur != head)
	{
		cnt++;
		e3(cur->value);
		cur=cur->next;
	}
	e1(cnt)
}

void PrintCode()
{
	for(int i=32; i<=126; i++)
	{
		printf("%c ",(char)i);
	}
	printf("\n");
	
	for(int i=32; i<=126; i++)
	{
		printf("%c ",(char)code[i]);
	}
	printf("\n");
}

int main(){
	//freopen("input.txt","r",stdin);
	node* list;
	
	list=InitKey();
	
	GetCode(list);
	
	Encode();

	//fclose(stdin);
	return 0;
}

