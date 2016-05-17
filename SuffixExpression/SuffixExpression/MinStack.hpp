#pragma once
#include<iostream>
#include<stack>

using namespace std;

template<class T>
class MinStack
{
public:
	MinStack()
		:_dataStack(),
		 _minStack()
	{}
	~MinStack()
	{}
private:
	stack<T> _dataStack;//����������ݵ�ջ
	stack<T> _minStack;//���������С����ջ
public:
	void Push(const T& data);
	void Pop();
	const T& Min();
};//���󣡣��������зֺ�

template<class T>
void MinStack<T>::Push(const T& data)
{
	if(data == NULL)
	{
		cout<<"Argument can't null!"<<endl;
		return;
	}
	if(_dataStack.size() == 0)
	{
		_dataStack.push(data);
		_minStack.push(data);
	}else{
		//������������С�ڵ�ǰ��Сֵ�������Сֵ
		if(data <= _minStack.top())
		{
			_minStack.push(data);
			_dataStack.push(data);
		}else{
			_minStack.push(_minStack.top());
			_dataStack.push(data);
		}
	}
}

template<class T>
void MinStack<T>::Pop()
{
	if(_dataStack.size() == 0)
	{
		cout<<"Stack is empty,don't pop!"<<endl;
		return;
	}
	_dataStack.pop();
	_minStack.pop();
}

template<class T>
const T& MinStack<T>::Min()
{
	if(_minStack.size() == 0)
	{
		cout<<"Stack is empty,don't get min!"<<endl;
		return T();
	}
	return _minStack.top();
}
