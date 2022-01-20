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

#define MAX 1000005
#define BUKETN 220000
/*

*/
typedef struct sentence
{
	int start;
	int sum;
	int end;
}sentence;

typedef struct bucket
{
	int cnt;
	int order[20];
}bucket;

sentence SentenceList[MAX];
bucket BucketList[BUKETN];
sentence heap[MAX];


FILE* FileIn;
FILE* FileOut;

char word[200];
int StopWords[MAX];
int times[MAX];
char Article[10000050]; 

int NumOfPreFix=1;
int trie[MAX][30];

int Hash(char* word)
{	
	int index=1;	
	int len=strlen(word);
	
	for(int i=0; i<len; i++)
	{
		if( trie[index][word[i]-'a'] == 0 )
		{
			trie[index][word[i]-'a'] = ++NumOfPreFix;
		}
		
		index=trie[index][word[i]-'a'];
	}
	
	return index;
}

int Find(char* word)
{
	int index=1;
	int len=strlen(word);
	
	for(int i=0; i<len; i++)
	{
		index=trie[index][word[i]-'a'];
	}
	
	if(StopWords[index])
		return 0;
	else
		return times[index];
}



int main()
{
	//freopen("input.txt","r",stdin);
	int n,index;
	scanf("%d",&n);
	
	//FILE* Stop=fopen("stopwords.txt", "r");
	freopen("stopwords.txt", "r", stdin);
	while( scanf("%s", word) != EOF )
	{
		index=Hash(word);
		StopWords[index]=1;
	}
	fclose(stdin);

	
	FileIn=fopen("article.txt","rb");
	int ArticleLen;
	ArticleLen=fread(Article, 1, 10000050, FileIn);		

	int IsSentneceBegain=1;
	int NumOfSentence=0;
	
	index=1;
	int child;

	for(register int i=0; i<ArticleLen; i++)
	{ 
		if(IsSentneceBegain && Article[i] == ' ')continue;
		if(IsSentneceBegain)
		{
			SentenceList[NumOfSentence].start=i;
			IsSentneceBegain=0;
		}
		
		if(isalpha(Article[i]))
		{
			child=tolower(Article[i])-'a';
			
			if(trie[index][child] == 0)
			{
				trie[index][child]=++NumOfPreFix;
			}
			
			index=trie[index][child];			
		}
		else if(index != 1)
		{
			//e1(index)
			
			times[index]++;
			index=1;
		}
		
		if(Article[i] == '.' || Article[i] == '?' || Article[i] == '!')
		{
			IsSentneceBegain=1;
			SentenceList[NumOfSentence].end=i;
			NumOfSentence++;
		}	
	}
	

	index=1;
	int max=-1;
	for(register int i=0; i<NumOfSentence; i++)
	{
		for(register int j=SentenceList[i].start; j<=SentenceList[i].end; j++)
		{
			if( isalpha(Article[j]) )
			{
				child=tolower(Article[j])-'a';
				index=trie[index][child];
			}
			else if(index != 1)
			{
				
				if(StopWords[index] == 0)
				{
					e1(times[index])
					SentenceList[i].sum+=times[index];
				}
					
				index=1;
			}
		}
		printf("\n");
		BucketList[SentenceList[i].sum].order[BucketList[SentenceList[i].sum].cnt]=i;
		BucketList[SentenceList[i].sum].cnt++;
		
		max=max>SentenceList[i].sum?max:SentenceList[i].sum;
	}
	
	int k=5;
	for(register int i=max; k ; i--)
	{
		int pos=0;
	
		while(pos<BucketList[i].cnt)
		{
			sentence record=SentenceList[BucketList[i].order[pos]];
			
			printf("%d ", record.sum);
			
			int j=record.start;
			
			for(; j <= record.end; j++)
			{
				putchar(Article[j]);
			}
			printf("\n");
		
			pos++;
			k--;
			
			if(k == 0)break;
		}
		pos=0;
	}

	freopen("results.txt", "w", stdout);
	k=n;
	for(register int i=max; k ; i--)
	{
		int pos=0;
		
		while(pos<BucketList[i].cnt)
		{
			sentence record=SentenceList[BucketList[i].order[pos]];
			
			printf("%d ", record.sum);
			
			int j=record.start;
			
			for(; j <= record.end; j++)
			{
				putchar(Article[j]);
			}
			printf("\n");
		
			pos++;
			k--;
			
			if(k == 0)break;
		}
		pos=0;
	}

	fclose(stdout);
	
	
	//fclose(stdin);
	return 0;
}

