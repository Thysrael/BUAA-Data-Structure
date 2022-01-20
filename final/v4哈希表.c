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

#define parent(cur) (((cur)-1)/2)
#define lchild(cur) (2*(cur)+1)
//script1.exe < input.txt
/*

*/

typedef struct TrieNode
{
	int count; 
	//有26个孩子，要用指针数组 
	struct TrieNode *child[26];
}node,*tree;

typedef struct word
{
	int count;
	char words[30];
	struct word* next;
}word;

typedef struct sentence
{
    int start;
    int end;
    int sum;
    int order;
}sentence;

char Article[6377010];
char StopWords[6000];
char WordTmp[25];
sentence list[215000];
word** HashLink;

sentence heap[215000];
int HeapCount=0;

int StopLen;

FILE *stop, *in, *out;

int n;


void SetStopWords();
void InsertWord(word* tmp);
unsigned int Hash(char *str);
int FindWord(word* tmp);

int GetSum(int start, int end);
int GetFre(char* word);

void AdjustUp(int cur);
void AdjustDown(int cur);
void HeapInsert(sentence value);
int Cmp(sentence a, sentence b);
void HeapSort();

void Print(); 

int main()
{
	//freopen("input.txt","r",stdin);
	//因为数组开不大，所以只能这么开 
	HashLink=(word**)malloc(2147483648*sizeof(word*));
	
	stop=fopen("stopwords.txt","r");
	in=fopen("article.txt","r");
	out=fopen("results.txt","w");
	
	int ArticleLen;
	//char只有1个字节，要录 6377010 元素个数， 从 in 流中录入 
	ArticleLen=fread(Article, 1, 6377010, in);
	
	StopLen=fread(StopWords, 1, 6500, stop);
	//先把停用词安置好 
	SetStopWords();
	

	//录入部分就应该结束了
	 

	scanf("%d",&n);
	
	
	//遍历文章内容 
	int SentencePos=0, WordPos=0;
	int IsSentneceBegain=1;
	
	word* tmp;

	for(int i=0; i<ArticleLen; i++)
	{
		//应该也是除文章前面的空格的 
		if(IsSentneceBegain == 1 && Article[i] == ' ')continue;
		//这里代表一个文章开始了 
		if(IsSentneceBegain == 1)
		{	
			list[SentencePos].start=i;
			IsSentneceBegain=0;
			
			tmp=(word*)malloc(sizeof(word));
		}
		
		if(isalpha(Article[i]))
		{
			tmp->words[WordPos++]=tolower(Article[i]);
		}
		else
		{
			//还是省去清零的麻烦 
			tmp->words[WordPos]='\0';
			//这个就跟插入停用词的逻辑类似，必须要保证有单词 
			if(WordPos == 0);
			//如果没有找到，那么就只能插入了，这时的插入第一个值是1 
			else if( FindWord(tmp) == 0 )
			{
				tmp->count=1;
				InsertWord(tmp);
			}
			
			WordPos=0;
		}
		
		//处理句子部分的结束
		if(Article[i] == '.' || Article[i] == '?' || Article[i] == '!')
		{
			IsSentneceBegain=1;
			list[SentencePos].end=i;
			list[SentencePos].order=SentencePos;
			SentencePos++;
		}
	}

	int k=(n>5)?n:5;
	for(int i=0; i<SentencePos; i++)
	{
		list[i].sum=GetSum(list[i].start, list[i].end);
		
		if(i<k)
		{
			HeapInsert(list[i]);
		}
		else if( list[i].sum > heap[0].sum )
		{
			heap[0]=list[i];
			AdjustDown(0);
		}
	}

	HeapSort();
	
	Print();
	
	fclose(out);
	fclose(in);
	fclose(stop);

	//fclose(stdin);
	return 0;
}


void SetStopWords()
{
	int cur=0;
	
	word* tmp=(word*)malloc(sizeof(word));
	
	//遍历整个停用词表 
	for(int i=0; i<StopLen; i++)
	{
		if(isalpha(StopWords[i]))
		{
			tmp->words[cur++]=tolower(StopWords[i]);
		}
		
		//这个应该说明录到回车了，可以存单词了 
		else
		{
			if(cur == 0)continue;//对应的应该是第一个字符为空白字符的情况，可以有效除空格
			 
			//加上'\0'，这样就不用每次memset了 
			tmp->words[cur]='\0';
			//停用词都记为-1 
			tmp->count=-1;
			//因为不用查是否存在，都可以直接插 
			InsertWord(tmp);
			//cur指针归位 
			cur=0;
		}
	}
}

void InsertWord(word* tmp)
{
	int index=Hash(tmp->words);
	
	word* pre=HashLink[index];
	
	//用的是头插法 
	tmp->next=HashLink[index]->next;
	HashLink[index]->next=tmp;
}

unsigned int Hash(char *str)
{
	unsigned int hash = 0;
 
	while (*str)
	{
		// equivalent to: hash = 65599*hash + (*str++);
		hash = (*str++) + (hash << 6) + (hash << 16) - hash;
	}
 
	return (hash & 0x7FFFFFFF);
}

//如果是1的话，代表已经找到这个单词了，有两种情况，一种是停用词，那么不做任何操作，另一种是非停用词，那么给count++
//如果是0的话，代表需要插入一个单词了，这个单词一定是一个非停用词，所以count=1 
int FindWord(word* tmp)
{
	int index=Hash(tmp->words);
	word* pre=HashLink[index];
	
	//逻辑应该还能简化 

	while(pre->next != NULL)
	{
		//找到单词了 
		if( strcmp(pre->next->words, tmp->words) == 0)
		{
			//不是停用词 
			if(pre->next->count != -1)
			{
				pre->count++;
			}
			//是不是都要返回1代表找到 ，进而不进行下一步操作 
			return 1;
		}
		
		pre=pre->next; 
	}
	
	return 0;
}

int GetSum(int start, int end)
{
	int sum = 0;
	//这里又用了wordtmp数组存单词了 
	int WordTmpPos=0;
	//memset(WordTmp, '\0', 25);
	fseek(in, start, SEEK_SET);
	
	int len=end-start+1;
	
	for(int i=0; i<len; i++)
	{
		char c=fgetc(in);
		
		if( isalpha(c) )
		{
			WordTmp[WordTmpPos++]=tolower(c);
		}
		else
		{
			//不是字母，说明上一个单词结束了
			if(WordTmpPos == 0)continue;
			//这里加0也是方便比较 
			WordTmp[WordTmpPos]='\0';
			
			sum += GetFre(WordTmp);
			
			WordTmpPos=0;
			//memset(WordTmp, '\0', 25); 
		}
	}
	
	return sum;
}

int GetFre(char* tmp)
{
	//获得临时字符串的哈希值 
	int index=Hash(tmp);
	
	word* cur=HashLink[index]->next;
	
	while(cur != NULL)
	{
		if( strcmp(cur->words, tmp) == 0 && cur->count>0 )
		{
			return cur->count;
		}
		
		cur=cur->next;
	}
	
	return 0;
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

void Print()
{
	for(int i=0; i<5; i++)
	{
		printf("%d ",heap[i].sum);
		fseek(in, heap[i].start, SEEK_SET);
		for(int j=0; j<heap[i].end-heap[i].start+1; j++)
		{
			char c=fgetc(in);
			putchar(c);
		}
		printf("\n");
	}
	

	for(int i=0; i<n; i++)
	{
		fprintf(out, "%d ", heap[i].sum);
		
		char* cur=&(Article[heap[i].start]);
		fwrite(cur, sizeof(char), heap[i].end-heap[i].start+1, out);
		
		fputc('\n', out);
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





