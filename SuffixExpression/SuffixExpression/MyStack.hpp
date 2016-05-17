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
		assert(capacity > 0);//ȷ��ָ����ջ�ĳ�ʼ����������
		_stack = new T[capacity];
	}
	MyStack &operator=(const MyStack& stack)
	{
		cout<<"test:"<<stack._stack[0]<<endl;
		if(&stack != this)
		{
			delete[] _stack;
			_stack = NULL;
			_stack = new T[stack._capacity];//���������������
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
		if(_top == _capacity)//����ǰջ���������������
		{
			T* temp = new T[_capacity*2+1];
			_capacity = _capacity*2+1;
			memcpy(temp,_stack,sizeof(T)*_top);
			delete[] _stack;//����ǰ��ջ�ռ��ͷ�
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
	T* _stack;//����ָ��ջ�����ָ��
	int _capacity;//ջ������
	int _top;//ջ������һ��λ�ô��±�
};