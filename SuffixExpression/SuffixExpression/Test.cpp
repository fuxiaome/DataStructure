#include"MyStack.hpp"
#include"MyQueue.hpp"
#include"StackTQ.hpp"
#include"MinStack.hpp"
#include"DoubleStack.hpp"
#include<string>

//测试队列的相关方法
void TestQueue()
{
	MyQueue<int> queue;
	queue.Push(1);
	queue.Push(2);
	cout<<" test front:"<<queue.Front()<<endl;
	queue.Print();
	MyQueue<int> queue2;
	queue2 = queue;
	queue2.Print();
	queue2.Pop();
	queue2.Pop();
	queue2.Pop();
	MyQueue<int> queue3;
	queue3 = queue2;
	queue3.Print();

}

//测试栈的相关方法
void TestStack()
{
	MyStack<int> stack1;
	stack1.Push(1);
	stack1.Push(2);
	MyStack<int> stack2;
	stack2 = stack1;
	cout<<stack2.Top()<<endl;	
}

//测试用两个队列实现的栈的相关方法
void TestStackTQ()
{
	StackTQ<string> stack;
	stack.Push("lalala");
	stack.Push("hahaha");
	stack.Push("hehehe");
	cout<<"Front:"<<stack.Top()<<endl;
	stack.Pop();
	cout<<"Front:"<<stack.Top()<<endl;
	StackTQ<string> stack1;
	stack1 = stack;
	cout<<"stack1 Front:"<<stack1.Top()<<endl;
	stack1.Pop();
	cout<<"stack1 Front:"<<stack1.Top()<<endl;
	stack.Pop();
	cout<<"stack Front:"<<stack1.Top()<<endl;
}

//测试Min栈的相关方法
void TestMinStack()
{
	MinStack<int> minStack;
	minStack.Push(3);
	minStack.Push(4);
	minStack.Push(1);
	minStack.Push(2);
	cout<<"min is:"<<minStack.Min()<<endl;
	minStack.Pop();
	minStack.Pop();
	cout<<"min is:"<<minStack.Min()<<endl;
}

//测试DoubleStack的相关方法
void TestDoubleStack()
{
	int* commonArray = NULL;
	DoubleStack<int> s1(commonArray, 0);
	DoubleStack<int> s2(commonArray, 1);
	s1.Push(1);
	s1.Push(2);
	s1.Push(3);
	s2.Push(4);
	s2.Push(5);
	s2.Push(6);
	cout<<s1.Size()<<endl;
	cout<<s2.Size()<<endl;
	cout<<s1.Top()<<endl;
	cout<<s2.Top()<<endl;
	s1.Pop();
	s2.Pop();
	cout<<s1.Top()<<endl;
	cout<<s2.Top()<<endl;
}
int main()
{
	TestMinStack();
	//TestStackTQ();
	//TestQueue();
	//TestStack();
	//TestDoubleStack();
	return 0;
}