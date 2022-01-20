#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct node
{
	char c;
	int num;
	struct node *child[8];
}	tnode, *tree;
tree stack[100];
int top;
tree solve(tree p, char *c);
void travel1(tree p);
void travel2(tree p);

int main()
{
	char str[50];
	tree root = NULL;
	top = -1;
	
	scanf("%s", str);
	root = solve(root, str);
	
	travel1(root);
	putchar('\n');
	travel2(root);
	
	return 0;
}
tree solve(tree p, char *c)
{
	while(*c != '\0')
	{
		if(p == NULL)
		{
			p = (tree)malloc(sizeof(tnode));
			p->num = 0;
			int i;
			for(i = 0; i < 8; i++)
				p->child[i] = NULL;
		}
		if(isalpha(*c))
		{
			p->c = *c;
		}
		else if(*c == '(')
		{
			stack[++top] = p;
			p = p->child[p->num];
		}
		else if(*c == ',')
		{
			stack[top]->child[stack[top]->num++] = p;
			p = stack[top];
			p = p->child[p->num];
		}
		else if(*c == ')')
		{
			stack[top]->child[stack[top]->num++] = p;
			p = stack[top--];
		}
		c++;
	}
	return p;
}
void travel1(tree p)
{
	int i;
	if(p != NULL)
	{
		printf("%c ", p->c);
		for(i = 0; i < 8; i++)
			travel1(p->child[i]);
	}
}
void travel2(tree p)
{
	int i;
	if(p != NULL)
	{
		for(i = 0; i < 8; i++)
			travel2(p->child[i]);
		printf("%c ", p->c);
	}
}
