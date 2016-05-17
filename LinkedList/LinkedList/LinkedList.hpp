#include<iostream>
#include<errno.h>

using namespace std;

typedef int DataType;

//定义链表结点的结构体
struct LinkNode
{
	DataType _data;
	LinkNode* _next;//错误，此处的类型为LinkNode* 而不是 LinkNode

	LinkNode(DataType data)
		:_data(data)
		 ,_next(NULL)
	{}
};

class LinkedList
{
public :
	LinkedList()//默认无参构造函数
		:_head(NULL),
		 _tail(NULL),
		 _size(NULL)
	{}
	LinkedList(const LinkedList& linkedList)//可以允许
		:_head(NULL),
		 _tail(NULL)
	{
		if(&linkedList == NULL)
			return;
		LinkNode *cur = linkedList._head;//为什么通过该类对象可以访问到私有成员
		while(cur!=NULL)
		{
			this->PushBack(cur->_data);
			cur = cur->_next;
		}
		
	}

	LinkedList &operator=(const LinkedList& linkedList)
	{
		if(&linkedList != this)
		{
			this->~LinkedList();
			LinkNode *cur = linkedList._head;
			while(cur!=NULL)
			{
				this->PushBack(cur->_data);
				cur = cur->_next;
			}
		}
		return *this;
	}

	~LinkedList()//析构函数
	{
		while(_head)
		{
			this->PopFront();
		}
	}
public :
	LinkNode* getHead();
	void PushBack(const DataType& data);//向链表尾部插入一个元素
	void Popback();//删除链表尾部的元素
	void PushFront(const DataType& data);//向链表头部插入一个元素
	void PopFront();//删除链表头部的元素
	void Reverse();//将链表逆置
	void QuickSort();//对链表进行快速排序
	void Print();//打印链表的元素
private :
	LinkNode* _head;//指链表头的指针
	LinkNode* _tail;//指向链表尾的指针
	int _size;
private:
	void _QuickSort(LinkNode *head, LinkNode *tail);
};//错误，类结束有分号

LinkNode* LinkedList::getHead()
{
	return _head;
}

void LinkedList::PushBack(const DataType& data)
{
	//当链表中为空时
	if(_head == NULL)
	{
		_head = new LinkNode(data);
		if(_head == NULL)//若内存分配失败则终止程序
		{
			perror("Memory distribute fail!");
			exit(-1);
		}
		_tail = _head;
		_size = 1;
	}else{//链表不为空时不用初始化链表的头结点
		LinkNode* newNode = new LinkNode(data);
		if(newNode == NULL)//若内存分配失败则终止程序
		{
			perror("Memory distribute fail!");
			exit(-1);
		}
		_tail->_next = newNode;
		_tail = _tail->_next;
		_size++;
	}
}

void LinkedList::Popback()
{
	if(_tail == NULL)//当链表为空时
	{
		printf("LinkedList is empty,don't Pop!\n");
	}else if(_head == _tail){//当链表中只有一个元素
		delete _head;
		_head = NULL;
		_tail = NULL;
		_size = 0;
	}else{//当链表有一个以上的元素时
		LinkNode* cur = _head;//定义一个游标指针
		//使用循环将该游标指针指向尾结点的前一个结点
		while(cur->_next != _tail)
		{
			cur = cur->_next;
		}
		cur->_next = NULL;
		delete _tail;
		_tail = cur;
		_size--;
	}
}

void LinkedList::PushFront(const DataType& data)
{
	if(_head == NULL)
	{	
		_head = new LinkNode(data);
		_tail = _head;
		_size = 1;
	}else{
		LinkNode* newNode = new LinkNode(data);
		newNode->_next = _head;
		_head = newNode;
		_size++;
	}
}

void LinkedList::PopFront()
{
	if(_head == NULL)
	{
		cout<<"LinkedList is empty,don't Pop!"<<endl;
	}else if(_head == _tail){
		delete _head;
		_head = NULL;
		_tail = NULL;
		_size = 0;
	}else{
		LinkNode* temp = _head;
		_head = _head->_next;
		_size--;
		delete temp;
		temp = NULL;
	}
}

void LinkedList::Reverse()
{
	if(_head == NULL)
	{
		cout<<"LinkedList is empty, don't reverse!"<<endl;
	}

	if(_size > 1)
	{
		LinkNode* prior = _head;//表示逆置过程中的链表头
		LinkNode* next = _head->_next;//表示每次进行逆置的节点
		LinkNode* temp = NULL;//记录每次进行逆置节点的下一个位置，即为未进行逆置链表的第一个位置

		_tail = _head;//链表逆置后，当前的头结点将变为尾节点
		_tail->_next = NULL;//尾节点的下一个位置为空

		//使用前插的思想依次对各个节点进行逆置
		while(next != NULL)
		{
			temp = next->_next;
			next->_next = prior;
			prior = next;
			next = temp;
		}
		//最后一个进行前插的节点为逆置后链表的头节点
		_head = prior;
	}
}	

void LinkedList::QuickSort()
{
	_QuickSort(_head, _tail);
}

void LinkedList::_QuickSort(LinkNode *head, LinkNode *tail)
{
	if(head == tail || head->_next == tail)
	{
		return;
	}
	LinkNode *val = head;
	LinkNode *prev = head;
	LinkNode *cur = head->_next;

	while(cur != tail)
	{
		if(cur->_data < val->_data)
		{
			prev = prev->_next;
			if(prev != cur )
			{
				swap(prev->_data, cur->_data);
			}
		}
		
		cur = cur->_next;
	}
	swap(val->_data, prev->_data);
	_QuickSort(head, prev);
	_QuickSort(prev->_next, tail);//错误，这里应该从perv->_next开始划分范围
}

void LinkedList::Print()
{
	if(_head == NULL)
	{
		cout<<"LinkedList is empty!"<<endl;
		return;
	}
	LinkNode* cur = _head;
	while(cur != NULL)
	{
		cout<<cur->_data<<" ";
		cur = cur->_next;
	}
	cout<<endl;
}
