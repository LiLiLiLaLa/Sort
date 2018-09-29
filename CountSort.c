#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

void CountSort(int* a, int n)
{
	assert(a);
	int max = a[0];
	int min = a[0];
	int i = 0;
	int index = 0;
	for (i; i < n; i++)
	{
		if (a[i]>max)
		{
			max = a[i];
		}
		if (a[i] < min)
		{
			min = a[i];
		}
	}
	int range = max = min + 1;
	int* count = (int*)malloc(range*sizeof(int));
	memset(count, 0, sizeof(int)*range);
	for (i = 0; i < n; i++)
	{
		count[a[i] - min]++;
	}
	for (i = 0; i < range; i++)
	{
		while (count[i]--)
		{
			a[index++] = i + min;
		}
	}
}

void PrintArr(int* a, int n)
{
	int i = 0;
	for (i; i < n; i++)
	{
		printf("% d", a[i]);
	}
}

int main(void)
{
	int a[7] = { 20, 23, 22, 21, 25, 31, 19 };
	CountSort(a, sizeof(a) / sizeof(a[0]));
	PrintArr(a, sizeof(a) / sizeof(a[0]));
	system("pause");
	return 0;
}