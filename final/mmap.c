#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include <unistd.h>

#define ValueName(name) (#name)
#define e1(name) printf("%s��ֵ��%d\n",ValueName(name),name);
#define e2(name) printf("%s��ֵ��%s\n",ValueName(name),name);
#define e3(name) printf("%s��ֵ��%c\n",ValueName(name),name);
#define e4(name,n) for(int o=0;o<n;o++)printf("%s[%d]��ֵ��%d\n",ValueName(name),o,name[o]);
#define e5(name,n) for(int o=0;o<n;o++)printf("%s[%d]��ֵ��%f\n",ValueName(name),o,name[o]);
#define e7(name,n) for(int o=0;o<n;o++)printf("%s[%d]��ֵ��%c\n",ValueName(name),o,name[o]);
#define e6 printf("alouha\n");
#define e8(name,value) if(name != value)printf("%s��ֵ����%d������%d\n",ValueName(name),value,name);

#define MAX 100000
#define INF	65535
#define EPS 1e-6
/*

*/

int main()
{
	FILE* fp=fopen("article.txt","r");
	char* Article;
	Article=mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	



	return 0;
}


