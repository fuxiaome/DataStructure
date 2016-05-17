#pragma once
#include<iostream>

using namespace std;

template<class T>
class DoubleStack
{
public:
	DoubleStack(T* commonArray, int flag)
		:_array(commonArray)
	{
		if(commonArray != NULL)
		{
			_capacity = sizeof(commonArray)/sizeof(T);
		}else{
			_array = new T[2];
			_capacity = 2;
		}
		if(flag == 0)//根据标志位判断将数据放入哪个栈
		{
			_topIndex = 0;
		}else{
			_topIndex = 1;
		}
	}
	DoubleStack()
	{}
	~DoubleStack()	
	{}
private:
	T* & _array;
	size_t _capacity;//表示栈的容量
	size_t _topIndex;//表示栈顶元素的下标
public:
	void Push(const T& data);
	void Pop();
	const T& Top();
	size_t Size();
};

template<class T>
void DoubleStack<T>::Push(const T& data)
{
	if(data == NULL)
	{
		cout<<"Data can't is null!"<<endl;
		return;
	}

	if((_topIndex+2) >= _capacity)//若当前栈已满，则进行扩容
	{
		T* temp = new T[_capacity*2+1];
		_capacity = _capacity*2+1;
		memcpy(temp,_array,sizeof(T)*_topIndex);
		delete[] _array;//将当前的栈空间释放
		_array = temp;
	}

	_topIndex += 2;
	_array[_topIndex] = data;
}

template<class T>
void DoubleStack<T>::Pop()
{
	if(_topIndex == 0 || _topIndex == 1)
	{
		cout<<"The stack is empty, don't pop!"<<endl;
		return;
	}

	_array[_topIndex] = T();//把当前栈顶元素置为默认值
	_topIndex -= 2;
}	

template<class T>
const T& DoubleStack<T>::Top()
{
	if(_topIndex == 0 || _topIndex == 1)
	{
		cout<<"The stack is empty, don't get top!"<<endl;
		return T();
	}

	return _array[_topIndex];
}

template<class T>
size_t DoubleStack<T>::Size()
{
	if(_topIndex & 1)//判断_topIndex的奇偶性，进行相应的操作
	{
		return _topIndex==0 ? 1 : _topIndex/2;
	}else{
		return (_topIndex+1)/2;
	}
}