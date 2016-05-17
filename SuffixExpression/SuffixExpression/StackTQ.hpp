#pragma once
#include"MyQueue.hpp"

template<class T>
class StackTQ
{
public:
	StackTQ()
		:_size(0)
	{}
	~StackTQ()
	{
		_size = 0;
		_queue1.~MyQueue();
		_queue2.~MyQueue();
	}
	StackTQ &operator=(const StackTQ& stack)
	{
		if(this != &stack)
		{
			this->~StackTQ();
			this->_queue1 = stack._queue1;//使用了MyQueue的运算符重载
			this->_queue2 = stack._queue2;
			this->_size = stack._size;
		}
		return *this;
	}
public:
	void Push(const T& data);
	void Pop();
	const T Top();
	int Size();
	bool Empty();
private:
	MyQueue<T> _queue1;//实现栈的底层队列一
	MyQueue<T> _queue2;//实现栈的底层队列二
	int _size;
};//错误，不能忘记加";"

template<class T>
void StackTQ<T>::Push(const T& data)
{
	if(!_queue1.Empty())//如果目前数据在_queue1中则，把数据存入_queue1中
	{
		_queue1.Push(data);
	}else{
		_queue2.Push(data);
	}
	_size++;
}

template<class T>
void StackTQ<T>::Pop()
{
	if(Empty())
	{
		cout<<"The stack is empty,can't pop!"<<endl;
		return;
	}
	MyQueue<T>* emptyQue = &_queue1;
	MyQueue<T>* dataQue = &_queue2;
	if(!_queue1.Empty())
	{
		//经过该步骤后确保emptyQue指向的为当前没有数据的队列，dataQue指向有数据的队列
		swap(emptyQue,dataQue);
	}
	while(true)
	{
		const T temp = dataQue->Front();
		dataQue->Pop();
		if(dataQue->Empty())//最后一个元素不再放入另一个队列
		{
			break;
		}
		emptyQue->Push(temp);	
	}
	_size--;//元素个数减一
}

template<class T>
const T StackTQ<T>::Top()
{
	if(Empty())//若栈为空,则不允许执行Top()操作
	{
		cout<<"The stack is empty!";
		exit(-1);
	}
	MyQueue<T>* emptyQue = &_queue1;
	MyQueue<T>* dataQue = &_queue2;
	if(!_queue1.Empty())
	{
		//经过该步骤后确保emptyQue指向的为当前没有数据的队列，dataQue指向有数据的队列
		swap(emptyQue,dataQue);
	}
	while(true)
	{
		const T temp = dataQue->Front();
		dataQue->Pop();
		emptyQue->Push(temp);
		if(dataQue->Empty())
			return temp;//无法返回引用，因为执行Top时底层是靠两个队列来回交替数据完成该操作，而该操作过程中是借助一个	 
						//临时变量作为中转，但不能返回临时变量的应用，故函数返回值为temp而不是temp的引用

	}
}

template<class T>
int StackTQ<T>::Size()
{
	return _size;
}

template<class T>
bool StackTQ<T>::Empty()
{
	return _queue1.Empty() && _queue2.Empty();
}

