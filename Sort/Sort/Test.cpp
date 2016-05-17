#include "Sort.hpp"

void TestInsert()
{
	int arr[] = {4,1,9,2,8,7,3,6,5,10};
	int size = sizeof(arr)/sizeof(arr[0]);
	InsertSort(arr, size);
	Print(arr, size);
}

void TestBubble()
{
	int arr[] = {4,1,9,2,8,7,3,6,5,10};
	int size = sizeof(arr)/sizeof(arr[0]);
	BubbleSort(arr, size);
	Print(arr, size);
}

void TestShell()
{
	int arr[] = {4,1,9,2,8,7,3,6,5,10};
	int size = sizeof(arr)/sizeof(arr[0]);
	ShellSort(arr, size);
	Print(arr, size);
}

void TestQuick()
{
	int arr[] = {22,4,1,9,2,8,7,3,6,5,10};
	int size = sizeof(arr)/sizeof(arr[0]);
	QuickSort(arr, size);
	Print(arr, size);
}

void TestHeap()
{
	int arr[] = {22,4,1,9,2,8,7,3,6,5,10};
	int size = sizeof(arr)/sizeof(arr[0]);
	HeapSort(arr, size);
	Print(arr, size);
}


int main()
{
	//TestInsert();
	//TestBubble();
	//TestShell();
	//TestQuick();
	TestHeap();
	return 0;
}
