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

#define MAX 1000
#define INF	65535
#define EPS 1e-6
//script1.exe < input.txt
/*

*/

typedef struct node
{
	int xishu;
	int zhishu;
}node;

node l1[MAX];
int n1;

node l2[MAX];
int n2;

node l3[MAX];
int n3;

int Init(node *l)
{
	int tmp1,tmp2;
	char tmp3;
	int i=0;
	
	while(scanf("%d %d%c", &tmp1, &tmp2, &tmp3) != EOF)
	{
		l[i].xishu=tmp1;
		l[i].zhishu=tmp2;
		i++;
		if(tmp3 == '\n')return i;
	}
}

void Multi()
{
	int i,j;
	
	n3=n1*n2;
	
	for(i=0; i<n1; i++)
	{
		for(j=0; j<n2; j++)
		{
			l3[i*n2+j].zhishu=l1[i].zhishu+l2[j].zhishu;
			l3[i*n2+j].xishu=l1[i].xishu*l2[j].xishu;
		}
	}
}

int Cmp(const void *a, const void *b)
{
	node *x=(node*)a;
	node *y=(node*)b;
	
	return -(x->zhishu-y->zhishu); 
}

void Process()
{
	int pre=0;
	
	for(int i=1; i<n3;)
	{
		if(l3[pre].zhishu == l3[i].zhishu)
		{
			l3[pre].xishu+=l3[i].xishu;
			Delete(i);
		}
		else
		{
			pre++;
			i++;
		}
	}
}

void Delete(int pos)
{
	for(int i=pos; i<n3; i++)
	{
		l3[i]=l3[i+1];
	}
	
	n3--;
}

void Print()
{
	for(int i=0; i<n3; i++)
	{
		printf("%d %d ",l3[i].xishu,l3[i].zhishu);
	}
}

int main(){
	//freopen("input.txt","r",stdin);
	n1=Init(l1);
	n2=Init(l2);
	
	Multi();
	
	qsort(l3,n3,sizeof(node),Cmp);
	
	Process();
	
	Print();
	
	//fclose(stdin);
	return 0;
}

