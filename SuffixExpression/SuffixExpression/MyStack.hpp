#pragma once
#include<iostream>

using namespace std;

template<class T>
class MyStack
{
public:
	MyStack():_stack(NULL),_capacity(0),_top(0)
	{
	}
	MyStack(int capacity):_stack(NULL),_top(0)
	{
		assert(capacity > 0);//确保指定的栈的初始容量大于零
		_stack = new T[capacity];
	}
	MyStack &operator=(const MyStack& stack)
	{
		cout<<"test:"<<stack._stack[0]<<endl;
		if(&stack != this)
		{
			delete[] _stack;
			_stack = NULL;
			_stack = new T[stack._capacity];//怎样复制这个数组
			memcpy(_stack, stack._stack, stack._capacity*sizeof(T));
			_top = stack._top;
			_capacity = stack._capacity;
		}
		return *this;
	}
	~MyStack()
	{
		delete[] _stack;
		_top = 0;
		_capacity = 0;
	}
public:
	void Push(const T& elem)
	{
		if(_top == _capacity)//若当前栈已满，则进行扩容
		{
			T* temp = new T[_capacity*2+1];
			_capacity = _capacity*2+1;
			memcpy(temp,_stack,sizeof(T)*_top);
			delete[] _stack;//将当前的栈空间释放
			_stack = temp;
		}
		_stack[_top++] = elem;
	}

	void Pop()
	{
		if(Empty())
		{
			cout<<"The stack is empty!"<<endl;
			return;
		}
		
		_stack[--_top] = NULL;
	}

	void Pop(T& elem)
	{
		elem = _stack[--_top];
		stack[_top] = NULL;
	}
 
	const T& Top()
	{
		return _stack[_top - 1];
	}

	bool Empty()
	{
		return _top == 0;
	}

private:
	T* _stack;//定义指向栈数组的指针
	int _capacity;//栈的容量
	int _top;//栈顶的下一个位置处下标
};