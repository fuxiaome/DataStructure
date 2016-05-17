#include"LinkedList.hpp"

void Test1()
{
	LinkedList linkedList;
	linkedList.PushFront(11);
	linkedList.PushFront(12);
	linkedList.PushFront(13);
	linkedList.PushFront(14);
	linkedList.PushFront(15);
	linkedList.Print();
	linkedList.Reverse();
	linkedList.Print();
	linkedList.PushBack(16);
	linkedList.Print();	
}

void Test2()
{
	LinkedList list1;
	list1.PushFront(1);
	list1.PushFront(2);
	list1.PushFront(3);
	list1.PushFront(4);
	list1.Print();
	LinkedList list2(list1);//有参构造函数
	list2.Print();
}

void Test3()
{
	LinkedList list1;
	list1.PushFront(3);
	list1.PushFront(8);
	list1.PushFront(1);
	list1.PushFront(2);
	list1.PushFront(6);
	list1.PushFront(9);
	list1.Print();
	list1.QuickSort();
	list1.Print();
}
int main()
{
	Test3();
	return 0;
}