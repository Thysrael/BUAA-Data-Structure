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
typedef struct node
{
	char name[100];
	char author[30];
	char press[50];
	char date[20];
}node;

node list[800];
char key[100];

int cmp(node *x, node *y)
{
	return strcmp(x->name,y->name);
}

void sort(int n)
{
	int i,j;
	node tmp;
	
	for(i=1; i<n; i++)
	{
		tmp=list[i];
		for(j=i-1; cmp(&(list[j]),&tmp)>0 && j>=0; j--)
		{
			list[j+1]=list[j];
		}
		list[j+1]=tmp;
	}
}

int main(){
	//freopen("input.txt","r",stdin);
	int i,j,n,order;
	node tmp;
	
	FILE *fp1,*fp2;
	fp1=fopen("books.txt","r");
	fp2=fopen("ordered.txt","w");
	
	for(i=0; fscanf(fp1,"%s%s%s%s",list[i].name,list[i].author,list[i].press,list[i].date) != EOF; i++);
	n=i;

	sort(n);

	while(1)
	{
		scanf("%d",&order);
		
		if(order == 0)
		{
			for(i=0; i<n; i++)
			{
				fprintf(fp2,"%-50s%-20s%-30s%-10s\n", list[i].name, list[i].author, list[i].press, list[i].date);
			}
			break;
		}
			
			
		else if(order == 1)
		{
			scanf("%s %s %s %s", tmp.name, tmp.author, tmp.press, tmp.date);
			
			for(i=n-1; i>=0 && cmp(&(list[i]), &tmp)>0; i--)
			{
				list[i+1]=list[i];
			}
			list[i+1]=tmp;
			
			n++;
			

		}
		
		else if(order == 2)
		{
			scanf("%s",key);
			
			for(i=0; i<n; i++)
			{
				if(strstr(list[i].name, key) != NULL)
				{
					printf("%-50s%-20s%-30s%-10s\n", list[i].name, list[i].author, list[i].press, list[i].date);
				}
			}
		}
		
		else if(order == 3)
		{
			scanf("%s",key);
			
			for(i=0; i<n; i++)
			{
				if(strstr(list[i].name, key) != NULL)
				{
					for(j=i; j<n-1; j++)
					{
						list[j]=list[j+1];
					}
					//这里i--极度重要，因为原来的第i位被删除了，但是下一个检测的是删除后的第i+1位，原来的第i位就被跳过了 
					i--;
					n--;
				}
			}
			
		}
	}

	fclose(fp1);
	fclose(fp2);
	
	return 0;
}

