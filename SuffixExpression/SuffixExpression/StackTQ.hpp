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
			this->_queue1 = stack._queue1;//ʹ����MyQueue�����������
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
	MyQueue<T> _queue1;//ʵ��ջ�ĵײ����һ
	MyQueue<T> _queue2;//ʵ��ջ�ĵײ���ж�
	int _size;
};//���󣬲������Ǽ�";"

template<class T>
void StackTQ<T>::Push(const T& data)
{
	if(!_queue1.Empty())//���Ŀǰ������_queue1���򣬰����ݴ���_queue1��
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
		//�����ò����ȷ��emptyQueָ���Ϊ��ǰû�����ݵĶ��У�dataQueָ�������ݵĶ���
		swap(emptyQue,dataQue);
	}
	while(true)
	{
		const T temp = dataQue->Front();
		dataQue->Pop();
		if(dataQue->Empty())//���һ��Ԫ�ز��ٷ�����һ������
		{
			break;
		}
		emptyQue->Push(temp);	
	}
	_size--;//Ԫ�ظ�����һ
}

template<class T>
const T StackTQ<T>::Top()
{
	if(Empty())//��ջΪ��,������ִ��Top()����
	{
		cout<<"The stack is empty!";
		exit(-1);
	}
	MyQueue<T>* emptyQue = &_queue1;
	MyQueue<T>* dataQue = &_queue2;
	if(!_queue1.Empty())
	{
		//�����ò����ȷ��emptyQueָ���Ϊ��ǰû�����ݵĶ��У�dataQueָ�������ݵĶ���
		swap(emptyQue,dataQue);
	}
	while(true)
	{
		const T temp = dataQue->Front();
		dataQue->Pop();
		emptyQue->Push(temp);
		if(dataQue->Empty())
			return temp;//�޷��������ã���Ϊִ��Topʱ�ײ��ǿ������������ؽ���������ɸò��������ò����������ǽ���һ��	 
						//��ʱ������Ϊ��ת�������ܷ�����ʱ������Ӧ�ã��ʺ�������ֵΪtemp������temp������

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

