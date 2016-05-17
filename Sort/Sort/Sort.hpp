#include<iostream>

using namespace std;

/*-------------插入排序---------------*/
void InsertSort(int *arr, int size)
{
	int temp = 0;
	int j = 0;
	for(int i=1; i<size; ++i)
	{
		temp = arr[i];
		for (j=i-1; j>=0 && arr[j]>temp; --j)
		{
			arr[j+1] = arr[j];
		}
		arr[j+1] = temp;
	}
}
/*------------------------------------*/

/*-------------希尔排序---------------*/
void ShellSort(int *arr, int size)
{
	int h = 1;
	while(h < size/3) h = h*3+1;//控制比较间隔的粒度

	while(h > 0)
	{
		for(int i=h; i<size; ++i)
		{
			for(int j=i; j>=h && arr[j]<arr[j-h]; j-=h)
			{
				swap(arr[j], arr[j-h]);
			}
		}
		h /= 3;
	}
}

/*------------------------------------*/

/*-------------冒泡排序---------------*/
void BubbleSort(int *arr, int size)
{
	int isSwap = 1;
	for(int i=0; i<size && isSwap; ++i)
	{
		isSwap = 0;
		for(int j=1; j<size-i; ++j)
		{
			if(arr[j-1] > arr[j])
			{
				swap(arr[j-1], arr[j]);
				isSwap = 1;
			}
		}
	}
}
/*------------------------------------*/

/*-------------快速排序---------------*/
static int _Partition(int *arr, int lo, int hi)
{
	int val = arr[lo];
	int i=lo, j=hi+1;

	while(true)
	{
		while(arr[--j]>val);
		while(arr[++i]<val)if(i == hi)break;
		if(i >= j)break;
		swap(arr[i], arr[j]);
	}
	swap(arr[lo], arr[j]);
	return j;
}

static void _QuickSort(int *arr, int lo, int hi)
{
	if(hi <= lo)return;

	int pos = _Partition(arr, lo, hi);
	_QuickSort(arr, lo, pos-1);
	_QuickSort(arr, pos+1, hi);
}

void QuickSort(int *arr, int size)
{
	_QuickSort(arr, 0, size-1);
}
/*------------------------------------*/

/*---------------堆排序---------------*/
void _Sink(int *arr, int index, int size)
{
	int child = index*2+1;
	while(child < size)
	{
		if(child+1<size && arr[child+1]>arr[child])
		{
			++child;//child执行孩子中较大的一个
		}
		if (arr[child] < arr[index])
		{
			break;
		}
		swap(arr[child], arr[index]);
		index = child;
		child = index*2+1;
	}

}
void HeapSort(int *arr, int size)
{
	int N = size;
	//创建堆
	for(int i=size/2+1; i>0; --i)
	{
		_Sink(arr, i, N);	
	}
	//进行堆排序
	N = size;
	while( N>0 )
	{
		swap(arr[0], arr[--N]);
		_Sink(arr, 0, N);
	}
}
/*------------------------------------*/

//打印数组
void Print(int *arr, int size)
{
	for(int i=0; i<size; ++i)
	{
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}