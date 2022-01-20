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


#define MAX 1000005
#define BUCKETN 220000
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
bucket BucketList[BUCKETN];
sentence heap[MAX];
int* SentenceWord[MAX];
int NumOfSentenceWord[MAX];

FILE* FileIn;
FILE* FileOut;

char word[200];
int StopWords[MAX];
int times[MAX];
char Article[10000050]; 

int NumOfPreFix=1;
int trie[MAX][30];


int main()
{
	int n,index;
	scanf("%d",&n);
	int child;	

	FILE* Stop=fopen("stopwords.txt", "r");
	//freopen("stopwords.txt", "r", stdin);
	while( fscanf(Stop, "%s", word) != EOF )
	{
		char* w=word;
		index=1;
		while(*w)
		{
			child=*w-'a';
			if(trie[index][child] == 0)
				trie[index][child]=++NumOfPreFix;
			index=trie[index][child];
			++w;
		}

		StopWords[index]=1;
	}
	fclose(stdin);

	
	FileIn=fopen("article.txt","rb");
	int ArticleLen;
	ArticleLen=fread(Article, 1, 10000050, FileIn);		

	int IsSentneceBegain=1;
	int NumOfSentence=0;

	index=1;

	int SentenceWordCur=0;
	for(int i=0; i<ArticleLen; i++)
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
			times[index]++;

			if(StopWords[index] == 0)
			{
				SentenceWord[SentenceWordCur++]=&times[index];
				NumOfSentenceWord[NumOfSentence]++;
			}
				
				
			index=1;
		}
		
		if(Article[i] == '.' || Article[i] == '?' || Article[i] == '!')
		{
			IsSentneceBegain=1;
			SentenceList[NumOfSentence].end=i;
			//NumOfSentenceWord[NumOfSentence]=SentenceWordCur;
			
			
			//SentenceWordCur=0;
			NumOfSentence++;
		}	
	}
	

	index=1;
	int max=-1;
	SentenceWordCur=0;
	
	for(int i=0; i<NumOfSentence; i++)
	{
		for(int j=0; j<NumOfSentenceWord[i]; j++)
		{
			SentenceList[i].sum+=*(SentenceWord[SentenceWordCur++]);
		}
		
		int sum=SentenceList[i].sum;
		BucketList[sum].order[BucketList[sum].cnt]=i;
		BucketList[sum].cnt++;
		
		max=max>sum?max:sum;
	}
	
	int k=5;
	for(int i=max; k ; i--)
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
	for(int i=max; k ; i--)
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

