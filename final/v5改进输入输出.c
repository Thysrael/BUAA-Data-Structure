#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
//Ҫɾ��û�õ�ͷ�ļ��������ٶȻ���� 
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

#define N 1000005

int ch[N][26];
//tim�����ʳ��ֵ�Ƶ�ʣ�no��������ͣ�ô� 
int tim[N], no[N];

int cnt;

//num�ǶԾ��Ӹ����ļ����� 
int n, num;
int val[N];
int rk[N], sa[N];

//��������洢��ƪ���� 
char S[10 * N];
int m;

//�洢���Ǿ��ӿ�ʼ������ 
int st[N];
//ss����¼��ͣ�ô� 
char tt[100], ss[100];

//insӦ���ǲ���insert ��tp�������ǻ��߲���ͣ�ôʣ�0�ǣ�1����
//now������ַ���s��Ӧ����
//cnt�����е�������ǰ׺������ 
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

//���Ӧ���������洢����λ�õ� ���ҵ�now���ҵ����ַ��� 
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

//�����һ����ͨ�Ŀ��� 
void q_sort(int l, int r)
{
	if (l >= r) return;
	
	int le = l, ri = r;
	
	//tmp��l��r��ƽ��ֵ 
	int tmp = sa[(l + r) >> 1];
	
	do
	{
		while (cmp(sa[le], tmp)) ++le;
		while (cmp(tmp, sa[ri])) --ri;
		
		if (le <= ri)
		{
			//������д�� 
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
	
	//nd�ǽ�ֹend����˼ 
	int nd=1;
	int l=0, i=0, j=0;
	
	//������ƪ���� 
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
			//�ѵ���¼��Сд������tt�� 
			tt[++l] = S[i];
			if(tt[l] <= 'Z') tt[l] = tt[l] - 'A' + 'a';
		}
		//˵����ʱ�Ѿ����ʽ����� 
		else if(l)
		{
			//����ʱ¼�õĵ���ch�� 
			ins(tt, 1, l);
			l=0;
		}
		
		
		if(S[i] == '.' || S[i] == '!' || S[i] == '?')
		{
			nd=1;
		}
	}
	fclose(stdin);
	
	//������Ϊ�����һ������ 
	st[num + 1] = 0x3f3f3f3f;
	l = 0;
	
	//���Ƕ����µĵڶ��α��� 
	for (i = 1; i <= num; ++i)
	{
		int l = 0;
		//m����ƪ���µ��ַ��� 
		//¼����һ�������ˣ�׼ȷ��˵��st����һ�����ӵĽ�ֹ�ĺ�һ���ַ�����һ����������ӵĿ�ʼ 
		for (j = st[i]; j <= min(m, st[i + 1] - 1); ++j)
		{
			if ((S[j] >= 'A'&&S[j] <= 'Z') || (S[j] >= 'a'&&S[j] <= 'z')) 
			{
				tt[++l] = S[j];
				if (tt[l] <= 'Z') tt[l] = tt[l] - 'A' + 'a';
			}
			else if (l)
			{
				//��ʱi���Ǿ��ӱ���� 
				val[i] += find(tt, l);
				
				l = 0;
			}
		}
	}
	
	//��ʱΪ�˱�֤��ͬƵ�ʵľ��ӷ��ϱ�� 
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
