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
			this->Insert(array[i]);//�������Ԫ�����μ��뵽����
		}
	}
	MaxHeap(vector<T> & array)
	{
		_array = array;
	}
	~MaxHeap()
	{}
public:
	const T& GetHeapTop();//��ȡ��ǰ�Ѷ�Ԫ��
	void RemoveHeapTop();//ɾ���Ѷ�Ԫ��
	void Insert(const T& data);//����в���Ԫ��
	void Sort();//�Զѽ�������
	int Size();//��öѵ�ǰ��Ԫ�ظ���
private:
	void _Sink(int index);//������ָ���±��Ԫ���³�������λ��
	void _Swim(int index);//������ָ���±��Ԫ���ϸ�������λ��
};
	
template<class T>
const T& MaxHeap<T>::GetHeapTop()
{
	return _array.size()==0? T():_array[0];//�����������ݣ����ظ��������͵�Ĭ��ֵ
}


template<class T>
void MaxHeap<T>::RemoveHeapTop()
{
	int size = _array.size();
	if(size == 0)return;
	swap(_array[size-1], _array[0]);//���Ѷ�Ԫ����������һ��Ԫ�ؽ���
	_array.pop_back();//ɾ����βԪ�أ���ԭ�Ѷ�Ԫ��
	_Sink(0);//�³��Ѷ�Ԫ�أ��ָ��ѵ�������
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
			++child;//��childָ�����������нϴ�ĺ��ӵ��±�
		}
		if(_array[child] < _array[index]){//�����ӵ�ֵС�ڵ�ǰ�ڵ��ֵ����˵������������ѭ��
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
		cout<<GetHeapTop()<<" ";//ÿ��ȡ����ǰ���е����Ԫ��
		RemoveHeapTop();//ɾ���Ѷ�Ԫ��
	}
	cout<<endl;
	return;
}