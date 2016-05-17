#pragma once
#include<iostream>

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
class MyQueue
{
public:
	MyQueue()
		:_front(NULL),
		 _tail(NULL),
		 _size(0)
	{}
	~MyQueue()
	{
		while(_front)
		{
			Pop();
		}
		_size = 0;
	}
	MyQueue<T> &operator=(const MyQueue& queue)
	{
		if(&queue != this)
		{
			this->~MyQueue();
			LinkNode<T>* cur = queue._front;
			while(cur != NULL)
			{
				this->Push(cur->_data);
				cur = cur->_next;
			}
		}
		return *this;
	}
public:
	void Push(const T& data);
	void Pop();
	const T& Front();
	bool Empty();
	int Size();
	void Print();
private:
	LinkNode<T>* _front;//指向队头的指针
	LinkNode<T>* _tail;//指向队尾的指针
	int _size;//队列的元素个数
};

template<class T>
void MyQueue<T>::Push(const T& data)
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
void MyQueue<T>::Pop()
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
const T& MyQueue<T>::Front()
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
bool MyQueue<T>::Empty()
{
	return 0 == _size;
}

template<class T>
int MyQueue<T>::Size()
{
	return _size;
}

template<class T>
void MyQueue<T>::Print()
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

