#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>

#define ValueName(name) (#name)
#define e1(name) printf("%s的值是%d\n",ValueName(name),name);
#define e2(name) printf("%s的值是%s\n",ValueName(name),name);
#define e3(name) printf("%s的值是%c\n",ValueName(name),name);
#define e4(name,n) for(int o=0;o<n;o++)printf("%s[%d]的值是%d\n",ValueName(name),o,name[o]);
#define e5(name,n) for(int o=0;o<n;o++)printf("%s[%d]的值是%f\n",ValueName(name),o,name[o]);
#define e7(name,n) for(int o=0;o<n;o++)printf("%s[%d]的值是%c\n",ValueName(name),o,name[o]);
#define e6 printf("alouha\n");
#define e8(name,value) if(name != value)printf("%s的值不是%d，而是%d\n",ValueName(name),value,name);

#define MAX 100000
#define INF	65535
#define EPS 1e-6

#define LCHILD(x) (2*x+1)
/*
20 5
38 356 98 -102 126 46 65 -9 100 0 21 2 90 8 18 12 78 16 189 23
*/

int base[200];

int cnt;

void SelectSort(int n)
{
	int MinPos,tmp;
	
	for(int i=0; i<n; i++)
	{
		MinPos=i;
		
		for(int j=i; j<n; j++)
		{
			if(base[MinPos]>base[j])MinPos=j;
		}
		
		tmp=base[MinPos];
		base[MinPos]=base[i];
		base[i]=tmp;
	}
	
	cnt=(n*(n-1))/2;
}

void BubbleSort(int n)
{
	int tmp,flag;
	
	for(int i=1; i<n; i++)
	{
		flag=1;
		
		for(int j=0; j<n-i; j++)
		{
			cnt++;
			
			if(base[j]>base[j+1])
			{
				flag=0;
				
				tmp=base[j];
				base[j]=base[j+1];
				base[j+1]=tmp;
			}
		}
		
		if(flag == 1)break;
	}
}

void AdjustDown(int cur, int n)
{
	int child;
	int tmp=base[cur];
	
	for(; LCHILD(cur)<n; cur=child)
	{
		child=LCHILD(cur);
		
		if(child+1<n && base[child+1]>base[child])
			child++;
		
		cnt++;	
		if(tmp<base[child])
			base[cur]=base[child];
		else
			break;
	}
	
	base[cur]=tmp;
}

void HeapSort(int n)
{
	int i,tmp;
	
	for(i=n/2-1; i>=0; i--)
	{
		AdjustDown(i,n);
	}
	
	for(i=n-1; i>=0; i--)
	{
		tmp=base[0];
		base[0]=base[i];
		base[i]=tmp;
		
		AdjustDown(0, i);
	}
}

void Merge(int* base, int* TmpBase, int LeftCur, int RightCur, int RightEnd)
{
	int LeftEnd=RightCur-1;
	int TmpCur=LeftCur;
	int len=RightEnd-LeftCur+1;
	
	while(LeftCur <= LeftEnd && RightCur<=RightEnd)
	{
		cnt++;
		if(base[LeftCur] <= base[RightCur])
		{
			TmpBase[TmpCur]=base[LeftCur++];
		}
		else
		{
			TmpBase[TmpCur]=base[RightCur++];
		}
		TmpCur++;
	}
	
	while(LeftCur <= LeftEnd)
	{
		TmpBase[TmpCur]=base[LeftCur++];
		TmpCur++;
	}
	while(RightCur <= RightEnd)
	{
		TmpBase[TmpCur]=base[RightCur++];
		TmpCur++;
	}
	
	for(int i=0; i<len; i++, RightEnd--)
	{
		base[RightEnd]=TmpBase[RightEnd];
	}
}

void Msort(int* base, int* TmpBase, int left, int right)
{
	int mid=(left+right)>>1;
	
	if(left<right)
	{
		Msort(base, TmpBase, left, mid);
		Msort(base, TmpBase, mid+1, right);
		Merge(base, TmpBase, left, mid+1, right);
	}
}

void MergeSort(int n)
{
	int* TmpBase=(int*)malloc(n*sizeof(int));
	
	Msort(base, TmpBase, 0, n-1);
}

void QSort(int left,int right)
{     
	int tmp;
	
    if(left<right)
	{        
        tmp=base[left];
        base[left]=base[(left+right)/2];
        base[(left+right)/2]=tmp;
		
		int LeftCur=left;
        int RightCur=right+1;
        
        while(1)
        {
        	do
        	{
        		LeftCur++;
        		cnt++;
			}while(base[LeftCur] <= base[left] && LeftCur != right);
			do
			{
				RightCur--;
				cnt++;
			}while(base[RightCur] >= base[left] && RightCur != left);
			
			if(LeftCur < RightCur)
			{
				tmp=base[LeftCur];
				base[LeftCur]=base[RightCur];
				base[RightCur]=tmp;
			}
			else
			{
				break;
			}
        	
		}
		
		tmp=base[RightCur];
		base[RightCur]=base[left];
		base[left]=tmp;

		QSort(left, RightCur-1);
		QSort(RightCur+1,right);
    }
}

void swap(int* a, int* b)
{
	int tmp=(*a);
	*a=*b;
	*b=tmp;
}

void quickSort(int left,int right)
{     

    int i, last;

    if(left<right)
	{
        last=left; 
        
        for(i=left+1;i<=right;i++)
        {
        	cnt++;
			if(base[i] < base[left])
				swap(&base[++last],&base[i]); 
		}
           

        swap(&base[left], &base[last]);
        quickSort(left,last-1); 
        quickSort(last+1,right);   
    }

}

void QuickSort(int n)
{
	quickSort(0, n-1);
}

int main()
{
	int n,order;
	scanf("%d %d", &n, &order);
	
	for(int i=0; i<n; i++)
	{
		scanf("%d",&base[i]);
	}
	
	switch(order)
	{
		case 1:
			SelectSort(n);
			break;
			
		case 2:
			BubbleSort(n);
			break;
			
		case 3:
			HeapSort(n);
			break;
			
		case 4:
			MergeSort(n);
			break;
			
		case 5:
			QuickSort(n);
			break;
	}

	for(int i=0; i<n; i++)
	{
		printf("%d ",base[i]);
	}
	printf("\n%d", cnt);
	
	return 0;
}

