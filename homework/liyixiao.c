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

#define N 20000
#define MAX 100000
#define INF	65535
#define EPS 1e-6
//script1.exe < input.txt
/*
N M Smax
������� ÿ�����������Ʒ������ ���������� 
*/
int a[N][N];
int main()
{
	//freopen("input.txt","r",stdin);
	int n, m, num, op, topbra = -1, topres = -1;
	int  braket[N], top[N], result[N];
	int i=0, j=0, k=0;
	scanf("%d %d %d", &n, &m, &num);
	getchar();
	
	for(i=1; i<=n; i++)
	{
		for(j=0; j<m; j++)
		{
			scanf("%c", &a[i][j]);
		}
		getchar();
		top[i] = 0;
	}
	

	while(1)
	{
		scanf("%d", &op);
		if(op == -1)
		{
			break;
		}
		else if(op == 0)
		{
			if(topbra == -1)//��� 
			{
				continue;
			}
			else
			{
				result[++topres] = braket[topbra--];
			}
		}
		else
		{
			if(top[op] == m)//����� 
			{
				continue;
			 } 
			else
			{
				if(topbra == num-1)//���� �ӿ���ȡ��һ�� 
				{
					result[++topres] = braket[topbra--];
				}
				braket[++topbra] = a[op][top[op]++];
			}
	
		}

	}
	
	
	for(i=0; i<=topres; i++)
	{
		printf("%c",result[i]);
	}
	
	
	 






	//fclose(stdin);
	return 0;
}
