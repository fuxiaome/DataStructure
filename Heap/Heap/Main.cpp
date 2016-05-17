//#include"Heap.h"
//
//void Test()
//{
//	int ar[] = {53,17,78,9,45,65,87};
//	MinHeap<int> mh(ar,sizeof(ar)/sizeof(int));
//	mh.show();
//	cout<<"inserted 23"<<endl;
//	mh.insert(23);
//	mh.show();
//	cout<<"inserted 100 32 67 99 145"<<endl;
//	mh.insert(100);
//	mh.insert(32);
//	mh.insert(67);
//	mh.insert(99);
//
//	mh.insert(145);
//	mh.show();
//	cout<<"sorted"<<endl;
//	mh.sort();
//	mh.show();
//}
#include "Heap.hpp"
#include<string>

void Test1()
{
	int arr[] = {4,1,2,6,9,7,10,5,8,3};
	MaxHeap<int> maxHeap(arr,sizeof(arr)/sizeof(arr[0]));
	cout<<"Top:"<<maxHeap.GetHeapTop()<<endl;
	maxHeap.Insert(22);
	cout<<"Top:"<<maxHeap.GetHeapTop()<<endl;
	maxHeap.RemoveHeapTop();
	maxHeap.Insert(-1);
	maxHeap.Insert(30);
	maxHeap.Sort();
}

class A
{
public:
	void Print()
	{
		cout<<"AAAAA"<<endl;
	}
};

void main()
{
	//A *a = NULL;
	//a->Print();
	Test1();

}