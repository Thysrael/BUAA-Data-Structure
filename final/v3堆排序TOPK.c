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
	//��26�����ӣ�Ҫ��ָ������ 
	struct TrieNode *child[26];
}node,*tree;

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

sentence heap[215000];
int HeapCount=0;

int StopLen;

FILE *stop, *in, *out;

int n;

node* CreateNode();
void SetStopWords(tree t);
void InsertStopWord(tree t, char* word);
void InsertWord(tree t, char* word);
int FindStopWords(tree t, char* word);

int GetSum(tree t, int start, int end);
int GetFre(tree t, char* word);

void AdjustUp(int cur);
void AdjustDown(int cur);
void HeapInsert(sentence value);
int Cmp(sentence a, sentence b);
void HeapSort();

void Print(); 

int main()
{
	//freopen("input.txt","r",stdin);
	
	tree root=CreateNode();
	
	stop=fopen("stopwords.txt","r");
	in=fopen("article.txt","r");
	out=fopen("results.txt","w");
	
	int ArticleLen;
	//charֻ��1���ֽڣ�Ҫ¼ 6377010 Ԫ�ظ����� �� in ����¼�� 
	ArticleLen=fread(Article, 1, 6377010, in);
	
	StopLen=fread(StopWords, 1, 6500, stop);
	SetStopWords(root);
	

	//¼�벿�־�Ӧ�ý�����
	 

	scanf("%d",&n);
	
	memset(WordTmp, 0, 26);
	
	//������������ 
	int SentencePos=0, WordTmpPos=0;
	int IsSentneceBegain=1;
	for(int i=0; i<ArticleLen; i++)
	{
		//Ӧ��Ҳ�ǳ�����ǰ��Ŀո�� 
		if(IsSentneceBegain == 1 && Article[i] == ' ')continue;
		
		if(IsSentneceBegain == 1)
		{	
			list[SentencePos].start=i;
			IsSentneceBegain=0;
		}
		
		if(isalpha(Article[i]))
		{
			WordTmp[WordTmpPos++]=tolower(Article[i]);
		}
		else
		{
			//����͸�����ͣ�ôʵ��߼����� 
			if(WordTmpPos == 0);
			else if( FindStopWords(root, WordTmp) == 0 )
			{
				InsertWord(root, WordTmp);
			}
			
			memset(WordTmp, '\0', WordTmpPos+1);
			WordTmpPos=0;
		}
		
		//������Ӳ��ֵĽ���
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
		list[i].sum=GetSum(root, list[i].start, list[i].end);
		
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

node* CreateNode()
{
	node* tmp=(node*)malloc(sizeof(node));
	
	tmp->count=0;
	//ȥ����NULL��sizeof(tmp->child) 
	memset(tmp->child, 0LL, 208);
	
	return tmp;
}

void SetStopWords(tree t)
{
	int cur=0;
	
	for(int i=0; i<25; i++)
	{
		WordTmp[i]='\0';
	}
	
	for(int i=0; i<StopLen; i++)
	{
		if(isalpha(StopWords[i]))
		{
			WordTmp[cur++]=tolower(StopWords[i]);
		}
		
		//���Ӧ��˵��¼���س��ˣ����Դ浥���� 
		else
		{
			if(cur == 0)continue;//��Ӧ��Ӧ���ǵ�һ���ַ�Ϊ�հ��ַ������
			 
			InsertStopWord(t, WordTmp);
			//��tmp����
			for(int j=0; j<cur; j++)
			{
				WordTmp[j]='\0';	
			} 
			cur=0;
		}
	}
}

void InsertStopWord(tree t, char* word)
{
	node* cur;
	cur=t;
	
	int index;
	
	while(*word)
	{
		index = *word-'a';
		
		//�����Ҷ�ӽڵ��ˣ��ʹ����սڵ�
		if(cur->child[index] == NULL)
		{
			cur->child[index]=CreateNode();
		}
		
		//��Ȼ��˳��������,�ڵ�������ĸ���е��ϣ���е�����·��
		//ǰ׺	
		cur=cur->child[index];
		word++;
	}
	
	cur->count=-1;//Ƶ����������������
}

void InsertWord(tree t, char* word)
{
	node* cur;
	cur=t;
	
	int index;
	
	while(*word)
	{
		index = *word-'a';
		
		if(cur->child[index] == NULL)
		{
			cur->child[index]=CreateNode();
		}
		
		cur=cur->child[index];
		word++;
	}
	cur->count++;//Ƶ��++
}

int FindStopWords(tree t, char* word)
{
	node* cur=t;
	
	while(*word && cur != NULL)
	{
		cur=cur->child[*word-'a'];
		word++;
	}
	
	if(cur != NULL && cur->count == -1)
		return 1;
	else
		return 0;
}

int GetSum(tree t, int start, int end)
{
	int sum = 0;
	
	int WordTmpPos=0;
	memset(WordTmp, '\0', 25);
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
			//������ĸ��˵����һ�����ʽ�����
			if(WordTmpPos == 0)continue;
			
			sum += GetFre(t, WordTmp);
			
			WordTmpPos=0;
			memset(WordTmp, '\0', 25); 
		}
	}
	
	return sum;
}

int GetFre(tree t, char* word)
{
	node* cur=t;
	
	while(*word && cur != NULL)
	{
		cur=cur->child[*word-'a'];
		word++;
	}
	
	if( cur != NULL && cur->count > 0 )
		return cur->count;
	else
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





