#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>

#define ValueName(name) (#name)
#define e1(name) printf("%s��ֵ��%d\n",ValueName(name),name);
#define e2(name) printf("%s��ֵ��%f\n",ValueName(name),name);
#define e3(name) printf("%s��ֵ��%c\n",ValueName(name),name);
#define e4(name,n) for(int o=0;o<n;o++)printf("%s[%d]��ֵ��%d\n",ValueName(name),o,name[o]);
#define e5(name,n) for(int o=0;o<n;o++)printf("%s[%d]��ֵ��%f\n",ValueName(name),o,name[o]);
#define e7(name,n) for(int o=0;o<n;o++)printf("%s[%d]��ֵ��%c\n",ValueName(name),o,name[o]);
#define e6 printf("alouha\n");
#define e8(name,value) if(name != value)printf("%s��ֵ����%d������%d\n",ValueName(name),value,name);

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

//�������д�� bug ��࣬��ͻ���Ĺ�ע��������ִ��˳�����⣬�����뵱Ȼ
//�㷨��������ѭ�������ԣ�����������ʶ 
node* Move(node *pre, int step, node* head)
{
	//����ҪԤ���ж�һ�£���Ϊɾ�����һ���ڵ㣬�п���curһ������ָ��head 
	if(pre->next == head)
	{
		pre=pre->next;
	}
	
	for(int i=0; i<step-1; i++)
	{
		pre=pre->next;
		
		//ÿ�ζ�Ҫ���cur��û����head�� 
		if(pre->next == head)
		{
			pre=pre->next;
		}
	}
	//���ε�λ���Ǻܽ����ģ�����ǰ��飬���ں��飬Ҳ��������ǰ�����ں��� 

	code[step]=pre->next->value;
	
	return pre;
}

void GetCode(node *head)
{
	node *cur=head->next;
	node *pre=head;
	int tmp;
	//����������Ҫע�⣬����Ҫ��� 
	int first=cur->value;
	
	//ѭ��������ֹ���������漰 head�ڵ㣬�漰head�ڵ��������� 
	//���д˫������������ȻһЩ��preʵ����̫�鷳�� 
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

//��������Ϊ����ϤIO���������²����ţ�Ӧ������ 
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
			//�����⵼�´��� 
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

