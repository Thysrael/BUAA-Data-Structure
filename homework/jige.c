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

#define N 205
#define MAX 100000
#define INF	65535
#define EPS 1e-6
//script1.exe < input.txt
/*
建立双向链表
0 在左边插入
1 在右边插入 
*/

char s[50]="-1#124";

int main()
{
	int num;
	
	while( (num=atoi(s)) != 0 )
	{
			printf("%d",num);
	}
	
	

	
	
	return 0;
}
