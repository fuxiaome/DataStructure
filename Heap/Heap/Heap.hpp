#pragma once
#include<iostream>
#include<vector>

using namespace std;

template<class T>
class MaxHeap
{
private:
	vector<T> _array;
public:
	MaxHeap()
	{}
	MaxHeap(const T* array, int size)
	{
		for(int i=0; i<size; ++i)
		{
			this->Insert(array[i]);//将数组的元素依次加入到堆中
		}
	}
	MaxHeap(vector<T> & array)
	{
		_array = array;
	}
	~MaxHeap()
	{}
public:
	const T& GetHeapTop();//获取当前堆顶元素
	void RemoveHeapTop();//删除堆顶元素
	void Insert(const T& data);//向堆中插入元素
	void Sort();//对堆进行排序
	int Size();//获得堆当前的元素个数
private:
	void _Sink(int index);//将堆中指定下标的元素下沉到合适位置
	void _Swim(int index);//将堆中指定下标的元素上浮到合适位置
};
	
template<class T>
const T& MaxHeap<T>::GetHeapTop()
{
	return _array.size()==0? T():_array[0];//若堆中无数据，返回该数据类型的默认值
}


template<class T>
void MaxHeap<T>::RemoveHeapTop()
{
	int size = _array.size();
	if(size == 0)return;
	swap(_array[size-1], _array[0]);//将堆顶元素与堆中最后一个元素交换
	_array.pop_back();//删除堆尾元素，即原堆顶元素
	_Sink(0);//下沉堆顶元素，恢复堆的有序性
}

template<class T>
void MaxHeap<T>::Insert(const T& data)
{
	_array.push_back(data);
	_Swim(_array.size()-1);	
}

template<class T>
void MaxHeap<T>::_Swim(int index)
{
	int parent = index;
	while ( parent > 0 )
	{
		parent = (index-1)/2;
		if (_array[parent] > _array[index])
		{
			break;
		}
		swap(_array[parent], _array[index]);
		index = parent;
	}
}

template<class T>
void MaxHeap<T>::_Sink(int index)
{
	int child = index*2+1;
	int size = _array.size();
	while(child < size )
	{
		if(child+1 < size && _array[child+1]>_array[child]){
			++child;//将child指向两个孩子中较大的孩子的下标
		}
		if(_array[child] < _array[index]){//若孩子的值小于当前节点的值，则说明堆有序，跳出循环
			break;
		}
		swap(_array[child],_array[index]);
		index = child;
		child = index*2+1;
	}
}

template<class T>
void MaxHeap<T>::Sort()
{
	while(!_array.empty())
	{
		cout<<GetHeapTop()<<" ";//每次取出当前堆中的最大元素
		RemoveHeapTop();//删除堆顶元素
	}
	cout<<endl;
	return;
}