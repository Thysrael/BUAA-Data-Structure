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

typedef struct point
{
	int x;
	int y;
}point;

typedef struct line
{
	point start;
	point end;
	int next;
}line;

line list[MAX];
int n;

status IfEquel(point a, point b)
{
	if(a.x == b.x && a.y == b.y)return 1;
	else return 0;
}

int main(){
	//freopen("input.txt","r",stdin);

	int i,j,max=-1,cnt,cur;
	point MaxPoint;
	
	scanf("%d",&n);
	
	for(i=0; i<n; i++)
	{
		list[i].next=-1;
	}
	
	for(i=0; i<n; i++)
	{
		scanf("%d%d%d%d", &list[i].start.x, &list[i].start.y, &list[i].end.x, &list[i].end.y);
	}
	
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{	
			if(IfEquel(list[i].end, list[j].start))
			{
				list[i].next=j;
			}
		}
	}

	for(i=0; i<n; i++)
	{
		cur=list[i].next;
		cnt=1;
		
		while(cur != -1)
		{
			cur=list[cur].next;
			cnt++;
		}
		
		if(max<cnt)
		{
			max=cnt;
			MaxPoint=list[i].start;
		}
	}
	
	
	
	printf("%d %d %d", max, MaxPoint.x, MaxPoint.y);


	//fclose(stdin);
	return 0;
}

