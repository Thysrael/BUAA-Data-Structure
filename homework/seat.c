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
//script1.exe < input.txt
/*

*/

typedef struct student
{
	int order;
	char name[50];
	int seat;
}student;

typedef struct seat
{
	int cnt;
	int pos[2];
}seat;

student table[200];
seat list[200];

int Cmp(const void* a, const void* b)
{
	student* x=(student*)a;
	student* y=(student*)b;
	
	return x->order-y->order;
}

int main()
{
	//freopen("input.txt","r",stdin);
	int n;
	int front=-1,rear=-1;
	
	FILE *in,*out;
	in=fopen("in.txt","r");
	out=fopen("out.txt", "w");
	
	
	scanf("%d",&n);
	
	for(int i=0; i<n; i++)
	{
		fscanf(in,"%d %s %d", &table[i].order, table[i].name, &table[i].seat);
		
		list[table[i].seat].pos[list[table[i].seat].cnt]=i;
		list[table[i].seat].cnt++;
		
		if(rear<table[i].seat)rear=table[i].seat;
	}
	
	/*for(int i=1; i<=rear; i++)
	{
		for(int j=0; j<list[i].cnt; j++)
		{
			printf("%d %s %d\n", table[list[i].pos[j]].order, table[list[i].pos[j]].name, i);
		}
	}*/
	
	/*for(int i=0; i<=rear; i++)
	{
		if(list[i].cnt == 0)
		{
			front=i;
			break;
		}
	}*/
	
	
	int k=rear<n?rear:n;
	front=1;

	while(1)
	{
		for(; front<=k; front++)
		{
			//说明front座位是空的 
			if(list[front].cnt == 0)
			{
				break;
			}
		}

		//此时就遍历完了 
		if(front == k || rear < front)break;
		
		//list[rear].cnt是rear座位上的人数
		//list[rear].pos[ list[rear].cnt-1 ] 是要换座位的人在 table 里的下标 
		table[ list[rear].pos[ list[rear].cnt-1 ] ].seat=front;

		list[front].pos[0]=list[rear].pos[ list[rear].cnt-1 ];
		list[rear].cnt--;
		list[front].cnt++;

		front++;		
		if(list[rear].cnt == 0)
		{
			for(;list[rear].cnt == 0; rear--);
		}
		
	}
	
	
	/*for(int i=1; i<=rear; i++)
	{
		for(int j=0; j<list[i].cnt; j++)
		{
			//list[i].pos[j] 是编号为i的座位上的第j个学生的学号 
			printf("%d %s %d\n", table[list[i].pos[j]].order, table[list[i].pos[j]].name, i);
		}
	}*/
	
	k=1;
	for(int i=1; i<rear; i++)
	{
		if(list[i].cnt == 2)
		{
			list[i].cnt--;
			
			int max=table[list[i].pos[0]].order>table[list[i].pos[1]].order?0:1;
			
			table[list[i].pos[max]].seat=rear+k;
			
			list[rear+k].cnt++;
			list[rear+k].pos[0]=list[i].pos[max];
			k++;
			
			
		}	
	}	

	/*for(int i=1; i<=n; i++)
	{
		for(int j=0; j<list[i].cnt; j++)
		{
			//list[i].pos[j] 是编号为i的座位上的第j个学生的学号 
			printf("%d %s %d\n", table[list[i].pos[j]].order, table[list[i].pos[j]].name, i);
		}
	}*/
	
	qsort(table, n, sizeof(student), Cmp);
	
	for(int i=0; i<n; i++)
	{
		fprintf(out,"%d %s %d\n", table[i].order, table[i].name, table[i].seat);
	}
	



	//fclose(stdin);
	return 0;
}

