#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
//要删减没用的头文件，这样速度会提高 
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

#define N 1000005

int ch[N][26];
//tim代表单词出现的频率，no代表他是停用词 
int tim[N], no[N];

int cnt;

//num是对句子个数的计数量 
int n, num;
int val[N];
int rk[N], sa[N];

//这个用来存储整篇文章 
char S[10 * N];
int m;

//存储的是句子开始的坐标 
int st[N];
//ss用于录入停用词 
char tt[100], ss[100];

//ins应该是插入insert ，tp代表他是或者不是停用词，0是，1不是
//now最后会和字符串s对应起来
//cnt是所有单词所有前缀的数量 
void ins(char *s, int tp, int l)
{
	if ( cnt == 0 ) ++cnt;
	int now = 1, i;
	 
	for (i = 1; i <= l; ++i)
	{
		if ( ch[now][s[i] - 'a'] == 0 )
		{
			ch[now][s[i] - 'a'] = ++cnt;
		}
		
		now = ch[now][s[i] - 'a'];
	}

	if (tp == 0) no[now] = 1;
	else ++tim[now];
}

//这个应该是用来存储单词位置的 ，找到now就找到了字符串 
int find(char *s, int l)
{
	int now = 1, i;
	
	for (i = 1; i <= l; ++i)
	{
		now = ch[now][s[i] - 'a'];
	}

	if (no[now]) return 0;
	return tim[now];
}


int cmp(int x, int y)
{
	return (val[x]>val[y]) || (val[x] == val[y] && x<y);
}

int min(int x, int y)
{
	return x <= y ? x : y;
}

//这就是一个普通的快排 
void q_sort(int l, int r)
{
	if (l >= r) return;
	
	int le = l, ri = r;
	
	//tmp是l和r的平均值 
	int tmp = sa[(l + r) >> 1];
	
	do
	{
		while (cmp(sa[le], tmp)) ++le;
		while (cmp(tmp, sa[ri])) --ri;
		
		if (le <= ri)
		{
			//交换的写法 
			int tmp = sa[le]; 
			sa[le] = sa[ri], 
			sa[ri] = tmp;
			
			++le; 
			--ri;
		}
	}while (le <= ri);
	
	q_sort(l, ri); 
	q_sort(le, r);
}


int main()
{
	scanf("%d", &n);
	
	freopen("stopwords.txt", "r", stdin);
	
	while (scanf("%s", ss + 1) != EOF)
	{
		ins(ss, 0, strlen(ss + 1));
	}
	fclose(stdin);
	
	freopen("article.txt", "r", stdin);
	gets(S+1);
	m = strlen(S + 1);
	
	//nd是截止end的意思 
	int nd=1;
	int l=0, i=0, j=0;
	
	//遍历整篇文章 
	for(i=1;i<= m;++i)
	{
		if(nd)
		{
			++num; 
			st[num] = i;
			nd=0;
		}
		
		if((S[i] >= 'A'&&S[i] <= 'Z') || (S[i] >= 'a'&&S[i] <= 'z'))
		{
			//把单词录成小写，存在tt里 
			tt[++l] = S[i];
			if(tt[l] <= 'Z') tt[l] = tt[l] - 'A' + 'a';
		}
		//说明这时已经单词结束了 
		else if(l)
		{
			//把临时录好的单词ch中 
			ins(tt, 1, l);
			l=0;
		}
		
		
		if(S[i] == '.' || S[i] == '!' || S[i] == '?')
		{
			nd=1;
		}
	}
	fclose(stdin);
	
	//这里是为了最后一个句子 
	st[num + 1] = 0x3f3f3f3f;
	l = 0;
	
	//这是对文章的第二次遍历 
	for (i = 1; i <= num; ++i)
	{
		int l = 0;
		//m是整篇文章的字符数 
		//录到下一个句子了，准确的说，st是上一个句子的截止的后一个字符，不一定是这个句子的开始 
		for (j = st[i]; j <= min(m, st[i + 1] - 1); ++j)
		{
			if ((S[j] >= 'A'&&S[j] <= 'Z') || (S[j] >= 'a'&&S[j] <= 'z')) 
			{
				tt[++l] = S[j];
				if (tt[l] <= 'Z') tt[l] = tt[l] - 'A' + 'a';
			}
			else if (l)
			{
				//此时i就是句子编号了 
				val[i] += find(tt, l);
				
				l = 0;
			}
		}
	}
	
	//这时为了保证相同频率的句子符合编号 
	for (i = 1; i <= num; ++i) sa[i] = i;
	
	q_sort(1, num);
	

	for (i = 1; i <= 5; ++i)
	{
		printf("%d ", val[sa[i]]);
		
		j = st[sa[i]];
		while (S[j] == ' '&&j <= min(m, st[sa[i] + 1] - 1)) ++j;
		
		for (; j <= min(m, st[sa[i] + 1] - 1); ++j)
		{
			putchar(S[j]);
		}
		puts("");
	}
	freopen("results1.txt", "w", stdout);
	
	for (i = 1; i <= n; ++i)
	{
		printf("%d ", val[sa[i]]);
		j = st[sa[i]];
		while (S[j] == ' '&&j <= min(m, st[sa[i] + 1] - 1)) ++j;
		
		for (; j <= min(m, st[sa[i] + 1] - 1); ++j)
		{
			putchar(S[j]);
		}
		puts("");
	}
	fclose(stdout);
	
	return 0;
}
