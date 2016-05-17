#include<iostream>
using namespace std;

template<class Type>
class MinHeap
{
public:
	MinHeap(int sz=DefaultSize)
	{
		MaxHeapSize = sz > DefaultSize ? sz : DefaultSize;
		heap = new Type[MeaxHeapSize];
		memset(heap,0,sizeof((Type)*MaxHeapSize));
		CurHeapSize = 0;
	}
	MinHeap(Type ar[],int n)
	{
		MaxHeapSize = n > DefaultSize ? n : DefaultSize;
		heap = new Type[MaxHeapSize];
		memset(heap,0,sizeof(Type)*MaxHeapSize);
		CurHeapSize = n;
		for(int i=0; i<n;++i)
		{
			heap[i] = ar[i];
		}
		int pos = n/2 - 1;//找到堆的最后一个分支
		while(pos >= 0)
		{
			SiftDown(pos,n-1);
			--pos;
		}
	}
	void show() const
	{
		for(int i=0;i<CurHeapSize;++i)
		{
			cout<<heap[i]<<" ";
		}
		cout<<endl;
	}
	void sort()
	{
		sort(CurHeapSize-1);
	}
	void insert(Type k)
	{
		//实现堆的自动扩容，每次扩充为最大容量的1.5倍
		if(CurHeapSize >= MaxHeapSize)
		{
			//cout<<"CurSize:"<<CurHeapSize<<endl;
			//cout<<"MaxSize:"<<MaxHeapSize<<endl;
			MaxHeapSize *= 1.5;
			Type *NewHeap = new Type[MaxHeapSize];
			memset(NewHeap,0,sizeof(Type)*MaxHeapSize);
			for(int i=0;i<CurHeapSize;++i)
			{
				NewHeap[i] = heap[i];
			}
			delete[] heap;
			heap = NewHeap;
		}
		int n = CurHeapSize;
		heap[n] = k;
		SiftUp(n,n+1);
		CurHeapSize++;
	}
protected:
	void SiftDown(int pos, int n)
	{
		int i = pos;
		int j = 2*i + 1;//得到该节点的左孩子结点
		while(j <= n)
		{
			if(j+1<=n && heap[j]>heap[j+1])
			{
				j = j+1;
			}
			if(heap[i] > heap[j])
			{
				Type temp = heap[i];
				heap[i] = heap[j];
				heap[j] = temp;
			}
			i = j;
			j = 2*i+1;
		}
	}
	void SiftUp(int pos,int n)
	{
		int i = pos;
		int j = (pos-1)/2;//表示该节点的双亲结点
		while(j>0)
		{
			if(heap[j]>heap[i])
			{
				Type temp = heap[j];
				heap[j] = heap[i];
				heap[i] = temp;
			}
			i = j;
			j = (i-1)/2;
		}
	}
	void sort(int n)//进行堆排序
	{
		while(n>0)
		{
			Type temp = heap[0];
			heap[0] = heap[n];
			heap[n] = temp;
			--n;
			SiftDown(0,n);
		}
	}
private:
	enum{DefaultSize=10};
	Type *heap;
	int MaxHeapSize;
	int CurHeapSize;
};