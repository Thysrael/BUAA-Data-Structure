#include<stdio.h>

typedef struct sentence
{
	int start;
	int sum;
	int end;
}sen;

typedef struct bucket
{
	int cnt;
	int order[20];
}bucket;

sen SList[1000005];
bucket BucketList[220000];
sen heap[1000005];
int* SentenceWord[1000005];
int SenPosWord[1000005];

FILE *FileIn, *FileOut, *Stop;

char word[200];
int StopWords[1000005];
int times[1000005];
char Article[10000050]; 

int NumOfPreFix=1;
int trie[1000005][30];


int main()
{
	int n,index,child,ArticleLen,IsBegain=1,SenPos=0,WordPos=0,max=-1,j,sum,k,pos;
	char* w;
	scanf("%d",&n);

	Stop=fopen("stopwords.txt", "r");
	while( fscanf(Stop, "%s", word) != EOF )
	{
		w=word;
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
	ArticleLen=fread(Article, 1, 10000050, FileIn);		

	index=1;

	for(register int i=0; i<ArticleLen; ++i)
	{ 
		if(IsBegain && Article[i] == ' ')continue;
		if(IsBegain)
		{
			SList[SenPos].start=i;
			IsBegain=0;
		}
		//if( ( ( (Article[i]-'a') | ('z'-Article[i]) ) & ( (Article[i]-'A') | ('Z'-Article[i]) ) )>=0 )
		if(( (Article[i]-'a') | ('z'-Article[i]) ) >=0 || ( (Article[i]-'A') | ('Z'-Article[i]) ) >=0 )
		//if((Article[i]>='a' && Article[i]<='z') || (Article[i]>='A' && Article[i]<='Z'))
		{
			child=(Article[i]|32)-'a';
			if(trie[index][child] == 0)
				trie[index][child]=++NumOfPreFix;
			index=trie[index][child];			
		}
		else if(index-1)
		{
			++times[index];
			if(StopWords[index] == 0)
			{
				SentenceWord[++WordPos]=&times[index];
				++SenPosWord[SenPos];
			}	
			index=1;
		}
		
		if(Article[i] == '.' || Article[i] == '?' || Article[i] == '!')
		{
			IsBegain=1;
			SList[SenPos].end=i;
			++SenPos;
		}	
	}
	
	WordPos=0;
	for(register int i=0; i<SenPos; ++i)
	{
		for(j=0; j<SenPosWord[i]; ++j)
			SList[i].sum+=*(SentenceWord[++WordPos]);		
		sum=SList[i].sum;
		BucketList[sum].order[BucketList[sum].cnt]=i;
		++BucketList[sum].cnt;
		
		max=max>sum?max:sum;
	}
	
	k=5;
	for(register int i=max; k ; --i)
	{
		pos=0;
		while(pos<BucketList[i].cnt)
		{
			sen record=SList[BucketList[i].order[pos]];
			printf("%d ", record.sum);
			for(j=record.start; j <= record.end; ++j)
				putchar(Article[j]);
			printf("\n");
		
			++pos;
			--k;
			if(!k)break;
		}
	}

	freopen("results.txt", "w", stdout);
	k=n;
	for(register int i=max; k ; --i)
	{
		pos=0;
		while(pos<BucketList[i].cnt)
		{
			sen record=SList[BucketList[i].order[pos]];
			printf("%d ", record.sum);			
			for(j=record.start; j <= record.end; ++j)
				putchar(Article[j]);
			putchar('\n');
			++pos;
			--k;
			if(!k)break;
		}
	}
	
	return 0;
}

