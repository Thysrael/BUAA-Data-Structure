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
#define parent(cur) (((cur)-1)/2)
#define lchild(cur) (2*(cur)+1)
/*

*/
typedef struct sentence
{
	int start;
	int sum;
	int order;
	int end;
}sentence;

sentence SentenceList[MAX];
sentence heap[MAX];
int HeapCount; 

FILE* FileIn;
FILE* FileOut;

char word[200];
int StopWords[MAX];
int times[MAX];
char Article[10000050]; 

int NumOfPreFix=1;
int ch[MAX][30];

int Hash(char* word)
{	
	int index=1;	
	int len=strlen(word);
	
	for(int i=0; i<len; i++)
	{
		if( ch[index][word[i]-'a'] == 0 )
		{
			ch[index][word[i]-'a'] = ++NumOfPreFix;
		}
		
		index=ch[index][word[i]-'a'];
	}
	
	return index;
}

int Find(char* word)
{
	int index=1;
	int len=strlen(word);
	
	for(int i=0; i<len; i++)
	{
		index=ch[index][word[i]-'a'];
	}
	
	if(StopWords[index])
		return 0;
	else
		return times[index];
}

int cmp(void* a, void* b)
{
	sentence* x=(sentence*)a;
	sentence* y=(sentence*)b;
	
	if(x->sum != y->sum)
	{
		if(x->sum > y->sum)return -1;
		else return 1;
	}
	else
	{
		return (x->order-y->order);
	}
}

int Cmp(sentence a, sentence b)
{
	if(a.sum < b.sum)
	{
		return -1;
	}
	else if(a.sum == b.sum)
	{
		return b.order-a.order;
	}
	else
	{
		return 1;
	}
}


void AdjustUp(int cur)
{
	sentence tmp=heap[cur];
	
	for(; cur>0; cur=parent(cur))
	{
		if( Cmp(tmp, heap[parent(cur)]) < 0)
		{
			heap[cur]=heap[parent(cur)];
		}
		else
		{
			break;
		}
	}
	
	heap[cur]=tmp;
}

void AdjustDown(int cur)
{
	sentence tmp=heap[cur];
	
	for(int child=lchild(cur); child<HeapCount; cur=child, child=lchild(cur))
	{
		if(Cmp(heap[child], heap[child+1])>0 && child+1<HeapCount)
		{
			child=child+1;
		}
		
		if(Cmp(tmp, heap[child]) > 0)
		{
			heap[cur]=heap[child];
		}
		else
		{
			break;
		}
	}
	
	heap[cur]=tmp;
}

void HeapInsert(sentence value)
{
	heap[HeapCount++]=value;
	
	AdjustUp(HeapCount-1);
}

void HeapSort()
{	
	for(HeapCount-=1; HeapCount>0; HeapCount--)
	{
		sentence tmp=heap[HeapCount];
		heap[HeapCount]=heap[0];
		heap[0]=tmp;
		
		AdjustDown(0);		
	}
}

int main()
{
	//freopen("input.txt","r",stdin);
	int n,index;
	scanf("%d",&n);
	

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

	int end=1;
	int WordCur=0;
	int NumOfSentence=0;

	for(int i=0; i<ArticleLen; i++)
	{ 
		if(end)
		{
			SentenceList[NumOfSentence].start=i;
			end=0;
		}
		
		if(isalpha(Article[i]))
		{
			word[WordCur++]=tolower(Article[i]);
		}
		else if(WordCur)
		{
			word[WordCur]='\0';
			index=Hash(word);
			times[index]++;
			WordCur=0;
		}
		
		if(Article[i] == '.' || Article[i] == '?' || Article[i] == '!')
		{
			end=1;
			SentenceList[NumOfSentence].end=i;
			SentenceList[NumOfSentence].order=NumOfSentence;
			NumOfSentence++;
		}	
	}

	WordCur=0;
	int k=n>5?n:5;
	for(int i=0; i<NumOfSentence; i++)
	{
		for(int j=SentenceList[i].start; j<=SentenceList[i].end; j++)
		{
			if( isalpha(Article[j]) )
			{
				word[WordCur++]=tolower(Article[j]);
			}
			else if(WordCur)
			{
				word[WordCur]='\0';
				SentenceList[i].sum+=Find(word);				
				WordCur=0;
			}
		}
		
		if(i<k)
		{
			HeapInsert(SentenceList[i]);
		}
		else if(SentenceList[i].sum > heap[0].sum)
		{
			heap[0]=SentenceList[i];
			AdjustDown(0);
		}
	}

	HeapSort();


	//qsort(SentenceList, NumOfSentence, sizeof(sentence), cmp);

	for(int i=0; i<5; i++)
	{
		printf("%d ",heap[i].sum);
		
		int j=heap[i].start;
		while( Article[j] == ' ' && j <= heap[i].end )
			j++;
		
		for(; j <= heap[i].end; j++)
		{
			putchar(Article[j]);
		}
		printf("\n");
	}
	
	freopen("results1.txt", "w", stdout);
	for(int i=0; i<n; i++)
	{
		
		printf("%d ",heap[i].sum);
		
		int j=heap[i].start;
		while( Article[j] == ' ' && j <= heap[i].end )
			j++;
		
		for(; j <= heap[i].end; j++)
		{
			putchar(Article[j]);
		}
		printf("\n");		
	}
	fclose(stdout);
	

	//fclose(stdin);
	return 0;
}

