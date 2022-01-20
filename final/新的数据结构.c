#include<stdio.h>

#include<ctype.h>
#include<string.h>


#define MAX 1000005
#define BUCKETN 220000
/*

*/
typedef struct word
{
	int weight;
	struct word* child[26];	
}word; 

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

char WordTmp[200];

char Article[10000050]; 

word trie[MAX];
int* WordPtr[MAX];



int main()
{
	int n,index;
	scanf("%d",&n);
	
	word* prefix=trie;
	
	freopen("stopwords.txt", "r", stdin);
	
	word* cur;

	while( scanf("%s", WordTmp) != EOF )
	{
		cur=trie;
		char* w=WordTmp;
		while(*w)
		{
			index=*w-'a';
			if(cur->child[index] == NULL)
			{
				cur->child[index]=++prefix;
			}
			cur=cur->child[index];
			w++;
		}
		
		cur->weight=-1;
	}
	fclose(stdin);

	
	FileIn=fopen("article.txt","rb");
	int ArticleLen;
	ArticleLen=fread(Article, 1, 10000050, FileIn);		

	int IsSentneceBegain=1;
	int NumOfSentence=0;

	cur=trie;
	//int child;
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
			index=tolower(Article[i])-'a';
			
			if(cur->child[index] == 0)
			{
				cur->child[index]=++prefix;
			}
			
			cur=cur->child[index];			
		}
		else if(cur != trie)
		{
			if(cur->weight != -1)
			{
				cur->weight++;
				WordPtr[SentenceWordCur++]=&(cur->weight);
				NumOfSentenceWord[NumOfSentence]++;
			}	
			cur=trie;
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
	SentenceWordCur=0;
	
	for(int i=0; i<NumOfSentence; i++)
	{
		for(int j=0; j<NumOfSentenceWord[i]; j++)
		{
			SentenceList[i].sum+=*(WordPtr[SentenceWordCur++]);
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
	
	return 0;
}

