#include<stdio.h>

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

sentence SentenceList[1000005];
bucket BucketList[220000];
//sentence heap[1000005];


FILE* FileIn;
FILE* FileOut;

char word[200];
int StopWords[1000005];
int times[1000005];
char Article[10000050]; 

int NumOfPreFix=1;
int trie[1000005][30];

int Strlen(char* s)
{
	int cnt=0;
	while(*s)
	{
		cnt++;
		s++;
	}	
	return cnt;
}


int Insert(char* word)
{	
	int index=1;	
	int len=Strlen(word);
	
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

int main()
{
	int n,index;
	scanf("%d",&n);
	
	freopen("stopwords.txt", "r", stdin);
	while( scanf("%s", word) != EOF )
	{
		index=Insert(word);
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
		
		if((Article[i]>='a' && Article[i]<='z') || (Article[i]>='A' && Article[i]<='Z'))
		{
			if(Article[i]<='Z')
				child=Article[i]-'A';
			else
				child=Article[i]-'a';
			
			if(trie[index][child] == 0)
			{
				trie[index][child]=++NumOfPreFix;
			}
			
			index=trie[index][child];			
		}
		else if(index != 1)
		{
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
			if( (Article[j]>='a' && Article[j]<='z') || (Article[j]>='A' && Article[j]<='Z') )
			{
				if(Article[j]<='Z')
					child=Article[j]-'A';
				else
					child=Article[j]-'a';
				index=trie[index][child];
			}
			else if(index != 1)
			{
				
				if(StopWords[index] == 0)
				{
					SentenceList[i].sum+=times[index];
				}
					
				index=1;
			}
		}

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
	
	return 0;
}

