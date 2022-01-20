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

#define NHASH  3001
#define MULT  37
//script1.exe < input.txt
/*

*/

typedef struct index
{
	int start;
	int end;
}index;

typedef struct node
{
	char word[100];
	struct node* next;
}node;

char dic[5000][100];
index cat[26];
node* HashList[4000];

int flag;

int SetDic()
{
	int NumOfWord=0;
	
	FILE* in=fopen("dictionary3000.txt", "r");
	
	while(fscanf(in, "%s", dic[NumOfWord]) != EOF)
	{
		NumOfWord++;
	}
	
	fclose(in);
	
	return NumOfWord;
}

void SetCat(int n)
{
	int len=0;;
	char now=dic[0][0];
	
	cat[now-'a'].start=0;
	
	for(int i=0; i<n; i++)
	{
		if(now != dic[i][0])
		{
			cat[now-'a'].end=i-1;
			now=dic[i][0];
			cat[now-'a'].start=i;
		}
	}
	
	cat[now-'a'].end=n-1;
	cat['x'-'a'].start=1;
	cat['x'-'a'].end=0;
}

unsigned int hash(char *str)
{
       unsigned int h=0;
       char *p;

       for(p=str; *p!='\0'; p++)
              h = MULT*h + *p;

       return h % NHASH;
}

void Insert(int HashIndex, char* s)
{
	node* tmp=(node*)malloc(sizeof(node));
	strcpy(tmp->word,s);

	node* pre=HashList[HashIndex];
	
	while(pre->next != NULL && strcmp(pre->next->word, s)<0)
		pre=pre->next;
	
	tmp->next=pre->next;
	pre->next=tmp;
}

void SetHash(int n)
{
	for(int i=0; i<4000; i++)
	{
		HashList[i]=(node*)malloc(sizeof(node));
		HashList[i]->next=NULL;
	}
	
	for(int i=0; i<n; i++)
	{
		int HashIndex=hash(dic[i]);
		Insert(HashIndex, dic[i]);

	}
}

int LinearSearch(int n, char* s)
{	
	int i;

	for(i=0; i<n; i++)
	{

		if(strcmp(dic[i], s) == 0)
		{
			flag=1;
			break;
		}
		else if(strcmp(dic[i], s) > 0)
		{
			break;
		}
	}
	
	return i+1;
}

int BinarySearch(int start, int end, char* s)
{
	int i=0;
	
	//if(start == end)return 0;
	
	while(start <= end)
	{
		int mid=(start+end)>>1;
		i++;
				
		if(strcmp(dic[mid],s) == 0)
		{
			flag=1;
			break;
		}
		else if(strcmp(dic[mid],s) < 0)
		{
			start=mid+1;
		}
		else
		{
			end=mid-1;
		}
	}
	
	return i;
}

int IndexSearch(char* s)
{
	return BinarySearch(cat[s[0]-'a'].start, cat[s[0]-'a'].end, s);
}

int HashSearch(char* s)
{
	int index=hash(s);
	
	node* cur=HashList[index]->next;
	
	int i=0;
	
	while(cur != NULL && strcmp(cur->word, s) < 0)
	{
		cur=cur->next;
		i++;
	}
	
	if(cur == NULL) return i;
	if(strcmp(cur->word, s) == 0)
	{
		flag=1;
		i++;
	}
	
	return i;
}

int main()
{
	int NumOfWord=0;
	int order;
	char WordTmp[100];
	int cnt;
	
	NumOfWord=SetDic();

	SetCat(NumOfWord);
	
	SetHash(NumOfWord);
	
	
	while(scanf("%s %d", WordTmp, &order) != EOF)
	{
		flag=0;
		
		switch(order)
		{
			case 1:
				cnt=LinearSearch(NumOfWord, WordTmp);
				break;
				
			case 2:
				cnt=BinarySearch(0, NumOfWord-1, WordTmp);
				break;
				
			case 3:
				cnt=IndexSearch(WordTmp);
				break;
				
			case 4:
				cnt=HashSearch(WordTmp);
				break;
		}
		
		printf("%d %d\n",flag, cnt);
	}
	
	return 0;
}

