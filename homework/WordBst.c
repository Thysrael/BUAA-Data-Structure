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
	char word[100];
	int times;
	struct node* lchild;
	struct node* rchild;
}node;

int GetWord(char* buff, FILE* fp)
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

int Search(node* root, char* buff, node** pre)
{
	node* cur=root;
	
	while(cur)
	{
		*pre=cur;
		if(strcmp(cur->word, buff) == 0)
		{
			return 1;
		}
		else if(strcmp(buff, cur->word) < 0)
		{
			cur=cur->lchild;
		}
		else
		{
			cur=cur->rchild;
		}
	}
	
	return 0;
}

void TravIn(node* cur)
{
	if(cur)
	{
		TravIn(cur->lchild);
		printf("%s %d\n",cur->word,cur->times);
		TravIn(cur->rchild);
	}
}

int main(){
	//freopen("input.txt","r",stdin);
	FILE* fp=fopen("article.txt","r");
	char buff[200];
	node* pre=NULL;
	node* root=NULL;
	
	root=(node*)malloc(sizeof(node));
	root->word[0]='\0';
	root->lchild=NULL;
	root->rchild=NULL;
	
	while(GetWord(buff,fp) != EOF)
	{
		if(Search(root, buff, &pre) == 1)
		{
			pre->times++;
		}
		else
		{
			node* tmp=(node*)malloc(sizeof(node));
			tmp->lchild=NULL;
			tmp->rchild=NULL;
			tmp->times=1;
			strcpy(tmp->word,buff);
			
			if(strcmp(tmp->word, pre->word) < 0)
			{
				pre->lchild=tmp;
			}
			else
			{
				pre->rchild=tmp;
			}
		}
	}

	node* cur=root;
	for(int i=0; i<3; i++)
	{
		cur=cur->rchild;
		if(cur)
		{
			printf("%s ",cur->word);
		}
		else
		{
			break;
		}
	}
	printf("\n");
	
	
	TravIn(root->rchild);



	fclose(fp);
	return 0;
}

