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

#define MAX 10000
#define INF	65535
#define EPS 1e-6
//script1.exe < input.txt
/*

*/
typedef struct node
{
	int times;
	char word[MAX];
	struct node *next;
}node;


char tmp[MAX];

node* Init()
{
	node *head=(node*)malloc(sizeof(node));
	head->next=NULL;
	
	return head;
}

int GetWord(FILE* fp, char *buff)
{
	int c;

    while(!isalpha(c=fgetc(fp)))
    {
        if(c == EOF)return c;
        else continue;
    }

    do
    {
        *buff++=tolower(c);
    }while(isalpha(c=fgetc(fp)));

    *buff='\0';
    ungetc(c,fp);

    return 1;
}

void Insert(char *buff,node *head)
{	
	
	node *pre=head;
		
	while(pre->next != NULL && strcmp(pre->next->word,buff)<0)
	{	
		pre=pre->next;
	}
	
	if(pre->next != NULL && strcmp(pre->next->word,buff) == 0)
	{
		pre->next->times++;
	}
	else
	{
		node *p=(node*)malloc(sizeof(node));
		strcpy(p->word,buff);
		p->next=pre->next;
		p->times=1;
		pre->next=p;
	}
}

void Print(node *head)
{
	node* cur=head->next;
	while(cur != NULL)
	{
		printf("%s %d\n",cur->word,cur->times);
		cur=cur->next;
	}
}

int main(){
	//freopen("input.txt","r",stdin);

	char buff[MAX];
	node* list=Init();
	FILE *fp=fopen("article.txt","r");

	while(GetWord(fp,buff) != EOF)
	{
		Insert(buff,list);
	}
	
	Print(list);

	fclose(fp);
	//fclose(stdin);
	return 0;
}

