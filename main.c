#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "Stack.h"

void PrintArray(const int *arr,int n)
{
    int i = 0;
    assert(arr);
    for(i=0; i<n; i++)
        printf("%d ",arr[i]);
    printf("\n");
}

static void Swap(int *p1, int *p2)
{
    int tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

//插入排序
void InsertSort(int *arr, int n)
{
    int index = 0;
    assert(arr);
    for(index = 1; index < n; index++)
    {
        //将当前数据往前插入
        int end = index-1;
        int temp = arr[index];
        while(end >= 0 && temp < arr[end])
        {
            arr[end+1] = arr[end];
            --end;
        }
        arr[end+1] = temp;
    }
}

//插入排序
void InsertSort_OP(int *arr, int n)
{
	int index = 0;
	
	for (index = 1; index < n; index++)
	{
		int temp = arr[index];
		//通过二分查找 找出待插入元素的位置
		int left = 0;
		int right = index - 1;
		while (left <= right)
		{
			int mid = left + ((right - left) >> 1);
			if (temp >= arr[mid])
				left = mid + 1;
			else
				right = mid - 1;
		}
		//将当前数据往前插入
		int end = index - 1;
		//搬移元素
		while (end >= left)
		{
			arr[end + 1] = arr[end];
			--end;
		}
		arr[left] = temp;
	}
}

//希尔排序
void ShellSort(int* arr,int len)
{
    int gap = len;
    assert(arr);
    while(gap>1)
    {
        gap = gap/3+1;
        int cur = 0;
        for(cur = gap;cur<len;++cur)
        {
            int end = cur-gap;
            int tmp = arr[cur];
            while(end>=0 && tmp<arr[end])
            {
                arr[end+gap] = arr[end];
                end -= gap;
            }
            arr[end+gap] = tmp;
        }
    }
}

//选择排序
void SelectSort(int *arr, int n)
{
    int index = 0;
    assert(arr);
	for (index = 0; index < n; index++)
	{
		int maxPos = 0;
		int i = 1;
		//找最大元素的位置
		for (i = 1; i < n-index; i++)
		{
			if (arr[i] > arr[maxPos])
				maxPos = i;
		}
		if (maxPos != (n - index - 1))
			Swap(&arr[maxPos], &arr[n-index-1]);
	}
}

//选择排序的优化
void SelectSort_OP(int *arr, int n)
{
    int begin = 0;
    int end = n-1;

    assert(arr);
    while(begin < end)
	{
            int minindex = begin;
            int maxindex = begin;
	    //分别找到最大和最小的下标
	    int i = 0;
	    for(i = begin;i <= end; ++i)
		{
			if(arr[i]>arr[maxindex])
			{
				maxindex = i;
			}
			if(arr[i]<arr[minindex])
			{
				minindex = i;
			}
	    }
	    //把最小的放在前面，最大的放在后面
	    Swap(&arr[begin], &arr[minindex]);
	    if(begin == maxindex)//修正
		    maxindex = minindex;
	    Swap(&arr[end], &arr[maxindex]);
	    ++begin;
	    --end;
    }
}

void HeapAdjust(int *arr,int root,int len)
{
    //child是左孩子的下标
    int child = root*2+1;
    assert(arr);
    while(child<len)
    {
        // 比较左孩子和右孩子,child指向大的孩子
        if(child+1<len && arr[child+1]>arr[child])
        {
            child++;
        }
        // 1.若大的孩子节点大于根节点,则不再需要调整,跳出循环
        // 2.否则,交换孩子节点和根节点,将根节点继续往下调整
		if (arr[child] > arr[root])
		{
			Swap(&arr[child], &arr[root]);
			root = child;
			child = child * 2 + 1;
		}
		else
			return;
    }
}
//堆排序
void HeapSort(int *arr, int len)
{

	int i = (len - 2)>>1;
    assert(arr);
    //建堆
    for( ; i>=0; i--)
    {
        HeapAdjust(arr, i, len);
    }
    //排序
    for(i = len-1;i > 0; i--)
    {
        Swap(&arr[i], &arr[0]);
        HeapAdjust(arr, 0, i);
		//HeapAdjust(arr, i, 0);
    }
}

// 冒泡排序
void BubbleSort(int* arr, int len)
{
    int index = 0;
    int end = 0;
    assert(arr);
    for(end = len-1;end>0;end--)
    {
        int flag = 0;
        for(index=0;index<end;index++)
        {
            if(arr[index]>arr[index+1])
            {
                Swap(&arr[index], &arr[index+1]);
                flag = 1;
            }
        }
        if(flag == 0)
            break;
    }
}


//快速排序
int PartSort(int *a, int left, int right)
{
	int key = a[right];
	int begin = left;
	int end = right - 1;
	while (begin < end)
	{
		//找比基准值大的
		while ((begin < end) && (a[begin] <= key))
			begin++;
		//找比基准值小的
		while ((begin < end) && (a[end] >= key))
			end--;
		if (begin<end)
			Swap(&a[begin], &a[end]);
	}
	//最后别忘记把基准值和相遇点交换
	if (begin != right - 1)
		Swap(&a[begin], &a[right-1]);
	return begin;
}
void QuickSort(int *a, int left, int right)
{
	assert(a);
	if (left >= right)
		return;
	int div = PartSort(a, left, right);
	QuickSort(a, left, div);
	QuickSort(a, div + 1, right);
}
//挖坑法
int PartSort2(int *a, int begin, int end)
{
	int key = a[end];
	while (begin < end)
	{
		while (begin < end && a[begin] <= key)
		{
			++begin;
		}
		a[end] = a[begin];
		while (begin < end && a[end] >= key){
			--end;
		}
		a[begin] = a[end];
	}
	a[begin] = key;
	return begin;
}
void QuickSort2(int *a, int left, int right)
{
	assert(a);
	if (left >= right)
		return;
	int div = PartSort2(a, left, right);
	QuickSort(a, left, div - 1);
	QuickSort(a, div + 1, right);
}

//前后指针法
int PartSort3(int *a, int begin, int end)
{
	int prev = begin - 1;
	int cur = begin;
	int key = a[end];

	while (cur < end)
	{
		if (a[cur] < key && ++prev != cur)
			Swap(&a[cur], &a[prev]);
		++cur;
	}

	Swap(&a[++prev], &a[end]);
	return prev;
}

void QuickSort3(int *a, int left, int right)
{
	assert(a);
	if (left >= right)
		return;

	//小区间优化
	if (right - left + 1 < 10)
	{
		InsertSort(a + left, right - left + 1);
	}
	int div = PartSort3(a, left, right);
	QuickSort(a, left, div - 1);
	QuickSort(a, div + 1, right);
	
}

//三数取中法
int GetMidIndex(int* array, int left, int right)
{
	int mid = ((left + right) >> 2);
	assert(array);
	if (array[left]>array[right])
	{
		if (array[mid]<array[right])
			return mid;
		else
			return array[mid]>array[left] ? left : mid;
	}
	else //array[left] <= array[right]
	{
		if (array[left]>array[mid])
			return left;
		else //array[left] <= array[mid]
			return array[mid]>array[right] ? right : mid;
	}
}

//前后指针法(前面两种也可以三数取中) + 三数取中
int PartSort4(int *a, int begin, int end)
{
	int mid = GetMidIndex(a, begin, end);

	int prev = begin - 1;
	int cur = begin;
	Swap(&a[mid], &a[end]);
	int key = a[end];

	while (cur < end)
	{
		if (a[cur] < key && ++prev != cur)
			Swap(&a[cur], &a[prev]);
		++cur;
	}

	Swap(&a[++prev], &a[end]);
	return prev;
}

void QuickSort4(int *a, int left, int right)
{
	assert(a);
	if (left >= right)
		return;
	int div = PartSort3(a, left, right);
	QuickSort(a, left, div - 1);
	QuickSort(a, div + 1, right);
}

//非递归快速排序
void QuickSortNonR(int *a, int left, int right)
{
	Stack st;
	StackInit(&st);
	StackPush(&st, left);
	StackPush(&st, right);
	while (StackEmpty(&st))
	{
		int end = StackTop(&st);
		StackPop(&st);
		int begin = StackTop(&st);
		StackPop(&st);

		int div = PartSort(a, begin, end);
		if (begin < div - 1)
		{
			StackPush(&st, begin);
			StackPush(&st, div - 1);
		}
		if (div + 1 < end)
		{
			StackPush(&st, div + 1);
			StackPush(&st, end);
		}
	}
}

void Merge(int *a, int begin1, int end1, int begin2, int end2, int *tmp)
{
	int start = begin1;
	int n = end2 - begin1 + 1;
	int index = begin1;
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (a[begin1] < a[begin2])
			tmp[index++] = a[begin1++];
		else
			tmp[index++] = a[begin2++];
	}
	while (begin1 <= end1)
		tmp[index++] = a[begin1++];
	while (begin2 <= end2)
		tmp[index++] = a[begin2++];

	memcpy(a + start, tmp+start, sizeof(int)*n);
}
//归并排序
void _MergeSort(int *a, int begin, int end, int *tmp)
{
	int mid = begin + ((end - begin) >> 1);
	if (begin >= end)
		return;
	//[begin, mid][mid+1, end]
	_MergeSort(a, begin, mid, tmp);
	_MergeSort(a, mid + 1, end, tmp);
	
	Merge(a, begin, mid, mid + 1, end, tmp);

}
void MergeSort(int *a, int n)
{
	assert(a);
	int *tmp = (int*)malloc(sizeof(int)*n);
	_MergeSort(a, 0, n - 1, tmp);
	free(tmp);

}
//稳定排序的理解
int main(int argc, char* argv[]) {
    int array[]={3,5,11,19,4};
    int len = sizeof(array)/sizeof(int);
	int i = 0;
	//clock_t start, finish;
	//int arr[10000] = { 0 };
	//srand((unsigned int)time(NULL));
    PrintArray(array,len);
	//for (i = 0; i < 10000; i++)
	//{
	//	arr[i] = i;
	//}
	//start = clock();
    //InsertSort_OP(array,len);
    //ShellSort(array,len);
    //SelectSort(array,len);
    //SelectSort_OP(array,len);
    //HeapSort(array,len);
    // BubbleSort(array,len);
	QuickSort(array, 0, len);
	//QuickSort4(arr, 0, 10000);
	//QuickSort4(array, 0, len - 1);
	//finish = clock();
	//printf("ret = %f\n",(double)(finish-start));
	//PrintArray(arr, 100000);
	//QuickSortNonR(array, 0, len-1);
	//MergeSort(array, len);
	PrintArray(array, len);

	system("pause");
    return 0;
}
