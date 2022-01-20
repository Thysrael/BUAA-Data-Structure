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
    char sentence[1500];
    int sum;
}sentence;

char Article[6377010];
char StopWords[6000];
char WordTmp[25];
sentence list[215000];

int StopLen;

node* CreateNode();
void SetStopWords(tree t);
void InsertStopWord(tree t, char* word);
void InsertWord(tree t, char* word);
int FindStopWords(tree t, char* word);
int GetSum(tree t, char* sen);
int GetFre(tree t, char* word);
int cmp(const void*a,const void *b);

int main()
{
	//freopen("input.txt","r",stdin);
	
	tree root=CreateNode();
	
	FILE *stop, *in, *out;
	stop=fopen("stopwords.txt","r");
	in=fopen("article.txt","r");
	
	int ArticleLen;
	//charֻ��1���ֽڣ�Ҫ¼ 6377010 Ԫ�ظ����� �� in ����¼�� 
	ArticleLen=fread(Article, 1, 6377010, in);
	StopLen=fread(StopWords, 1, 6500, stop);
	SetStopWords(root);
	
	fclose(in);
	fclose(stop);
	//¼�벿�־�Ӧ�ý�����
	 
	int n;
	scanf("%d",&n);
	
	for(int i=0; i<25; i++)
	{
		WordTmp[i]='\0';
	}
	//������������ 
	int SentencePos=0, WordTmpPos=0, SingleSentencePos=0;
	for(int i=0; i<ArticleLen; i++)
	{
		//Ӧ��Ҳ�ǳ�����ǰ��Ŀո�� 
		if(SingleSentencePos == 0 && Article[i] == ' ')continue;
		
		list[SentencePos].sentence[SingleSentencePos++]=Article[i];
		
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
			SentencePos++;
			SingleSentencePos = 0;
			//��仰����û�� 
			continue;
		}
	}
	
	for(int i=0; i<SentencePos; i++)
	{
		list[i].sum=GetSum(root, list[i].sentence);
	}
	qsort(list, SentencePos, sizeof(list[1]), cmp);

	for(int i=0; i<5; i++)
	{
		printf("%d %s\n",list[i].sum, list[i].sentence);
	}
	
	out=fopen("results.txt","w");
	for(int i=0; i<n; i++)
	{
		fprintf(out, "%d %s\n",list[i].sum, list[i].sentence);
	}
	
	fclose(out);


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

int GetSum(tree t, char* sen)
{
	int sum = 0;
	
	int WordTmpPos=0;
	memset(WordTmp, '\0', 25);
	
	int len=strlen(sen);
	for(int i=0; i<len; i++)
	{
		if(isalpha(sen[i]))
		{
			WordTmp[WordTmpPos++]=tolower(sen[i]);
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

int cmp(const void*a,const void *b)
{
	//����Ӧ���ǿ��Ը��ĵģ���Ȼ��������̫ɵ�� 
	sentence x = *(sentence*)a;
	sentence y = *(sentence*)b;
	return y.sum-x.sum;
}




