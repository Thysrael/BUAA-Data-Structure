#include<stdio.h>

typedef struct sentence
{
	char* start;
	int sum;
	char end;
}sen;

typedef struct bucket
{
	int cnt;
	int order[20];
}bucket;

sen SList[1000005];
bucket BucketList[1000000];
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
	int n,index,child,IsBegain=1,SenPos=0,WordPos=0,max=-1,j,sum,k,pos;
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
	fread(Article, 1, 10000050, FileIn);		

	index=1;

	for(register char* i=Article; *i; ++i)
	{ 
		if(*i == ' ' && IsBegain)continue;
		else if(IsBegain)
		{
			SList[SenPos].start=i;
			IsBegain=0;
		}
		//isalpha
		if((unsigned int)(((*i)|0x20)-'a') < 26u)
		{
			//tolower 
			child=(*i|32)-'a';
			if(trie[index][child] == 0)
				trie[index][child]=++NumOfPreFix;
			index=trie[index][child];			
		}
		else 
		{
			if(index-1)
			{
				++times[index];
				if(StopWords[index] == 0)
				{
					SentenceWord[++WordPos]=&times[index];
					++SenPosWord[SenPos];
				}	
				index=1;
			}
			
			if(*i == '.' || *i == '?' || *i == '!')
			{
				IsBegain=1;
				SList[SenPos].end=*i;
				*i=0;
				++SenPos;
			}	
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

	FileOut=fopen("results.txt", "w");
	k=5;
	for(register int i=max; n ; --i)
	{
		pos=0;
		while(pos<BucketList[i].cnt)
		{
			sen record=SList[BucketList[i].order[pos]];
			fprintf(FileOut, "%d %s%c\n",record.sum, record.start, record.end);
			if(k)
			{
				printf("%d %s%c\n",record.sum, record.start, record.end);
				k--;
			}
			++pos;
			--n;
			if(!n)break;
		}
	}
	
	return 0;
}

