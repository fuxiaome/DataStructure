#pragma once
#include<iostream>
#include"TaskQueue.hpp"

using namespace std;

template<class T>
struct LinkNode
{
	T _data;
	LinkNode* _next;

	LinkNode(T data)
		:_next(NULL)
	{
		_data = data;
	}
};

template<class T>
class Queue
{
public:
	Queue()
		:_front(NULL),
		 _tail(NULL),
		 _size(0)
	{}
	~Queue()
	{
		while(_front)
		{
			Pop();
		}
		_size = 0;
	}
	Queue<T> &operator=(const Queue& queue)
	{
		if(&queue != this)
		{
			this->~Queue();
			LinkNode<T>* cur = queue._front;
			while(cur != NULL)
			{
				this->Push(cur->_data);
				cur = cur->_next;
			}
		}
		return *this;
	}
	friend class TaskQueue;//将任务队列类声明为友元类，可以在TaskQueue中访问Queue的私有成员
public:
	void Push(const T& data);
	void Pop();
	const T& Front();
	T& IndexOf(int index);
	bool Empty();
	int Size();
	void Print();
private:
	LinkNode<T>* _front;//指向队头的指针
	LinkNode<T>* _tail;//指向队尾的指针
	int _size;//队列的元素个数
};

template<class T>
void Queue<T>::Push(const T& data)
{
	if(_size == 0)
	{
		_front = new LinkNode<T>(data);
		_tail = _front;
		_size = 1;
	}else{
		LinkNode<T>* newNode = new LinkNode<T>(data);
		_tail->_next = newNode;
		_tail = newNode;
		_size++;
	}
}

template<class T>
void Queue<T>::Pop()
{
	if(_front == NULL)
	{
		cout<<"Queue is empty,don't pop!"<<endl;
	}else if(_front  == _tail){
		delete _front;
		_front = NULL;//释放空间后最好将指针置空，避免某些已是否为空的条件判断出现隐式的逻辑错误
		_tail = NULL;
		_size = 0;
	}else{
		LinkNode<T>* temp = _front->_next;
		delete _front;
		_front = temp;
		_size--;
	}
}

template<class T>
const T& Queue<T>::Front()
{
	if(_size == 0)
	{
		cout<<"The queue is empty!"<<endl;
		exit(-1);
	}else{
		return _front->_data;
	}
}

template<class T>
T& Queue<T>::IndexOf(int index)
{
	if(index >= _size || index < 0){
		cout<<"The index is invalid!"<<endl;
		return NULL;
	}else{
		LinkNode<T>* cur = _front; 
		for(int i=0; i<index; ++i)
		{
			cur = cur->_next;
		}
		return cur;
	}
}

template<class T>
bool Queue<T>::Empty()
{
	return 0 == _size;
}

template<class T>
int Queue<T>::Size()
{
	return _size;
}

template<class T>
void Queue<T>::Print()
{
	if(_front == NULL)
	{
		cout<<"The queue is empty!"<<endl;
	}else{
		LinkNode<T>* cur = _front;
		while(cur != NULL)
		{
			cout<<cur->_data<<" ";
			cur = cur->_next;
		}
		cout<<endl;
	}
}

