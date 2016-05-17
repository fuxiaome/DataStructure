#include<iostream>
#include<errno.h>

using namespace std;

typedef int DataType;

//����������Ľṹ��
struct LinkNode
{
	DataType _data;
	LinkNode* _next;//���󣬴˴�������ΪLinkNode* ������ LinkNode

	LinkNode(DataType data)
		:_data(data)
		 ,_next(NULL)
	{}
};

class LinkedList
{
public :
	LinkedList()//Ĭ���޲ι��캯��
		:_head(NULL),
		 _tail(NULL),
		 _size(NULL)
	{}
	LinkedList(const LinkedList& linkedList)//��������
		:_head(NULL),
		 _tail(NULL)
	{
		if(&linkedList == NULL)
			return;
		LinkNode *cur = linkedList._head;//Ϊʲôͨ�����������Է��ʵ�˽�г�Ա
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

	~LinkedList()//��������
	{
		while(_head)
		{
			this->PopFront();
		}
	}
public :
	LinkNode* getHead();
	void PushBack(const DataType& data);//������β������һ��Ԫ��
	void Popback();//ɾ������β����Ԫ��
	void PushFront(const DataType& data);//������ͷ������һ��Ԫ��
	void PopFront();//ɾ������ͷ����Ԫ��
	void Reverse();//����������
	void QuickSort();//��������п�������
	void Print();//��ӡ�����Ԫ��
private :
	LinkNode* _head;//ָ����ͷ��ָ��
	LinkNode* _tail;//ָ������β��ָ��
	int _size;
private:
	void _QuickSort(LinkNode *head, LinkNode *tail);
};//����������зֺ�

LinkNode* LinkedList::getHead()
{
	return _head;
}

void LinkedList::PushBack(const DataType& data)
{
	//��������Ϊ��ʱ
	if(_head == NULL)
	{
		_head = new LinkNode(data);
		if(_head == NULL)//���ڴ����ʧ������ֹ����
		{
			perror("Memory distribute fail!");
			exit(-1);
		}
		_tail = _head;
		_size = 1;
	}else{//����Ϊ��ʱ���ó�ʼ�������ͷ���
		LinkNode* newNode = new LinkNode(data);
		if(newNode == NULL)//���ڴ����ʧ������ֹ����
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
	if(_tail == NULL)//������Ϊ��ʱ
	{
		printf("LinkedList is empty,don't Pop!\n");
	}else if(_head == _tail){//��������ֻ��һ��Ԫ��
		delete _head;
		_head = NULL;
		_tail = NULL;
		_size = 0;
	}else{//��������һ�����ϵ�Ԫ��ʱ
		LinkNode* cur = _head;//����һ���α�ָ��
		//ʹ��ѭ�������α�ָ��ָ��β����ǰһ�����
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
		LinkNode* prior = _head;//��ʾ���ù����е�����ͷ
		LinkNode* next = _head->_next;//��ʾÿ�ν������õĽڵ�
		LinkNode* temp = NULL;//��¼ÿ�ν������ýڵ����һ��λ�ã���Ϊδ������������ĵ�һ��λ��

		_tail = _head;//�������ú󣬵�ǰ��ͷ��㽫��Ϊβ�ڵ�
		_tail->_next = NULL;//β�ڵ����һ��λ��Ϊ��

		//ʹ��ǰ���˼�����ζԸ����ڵ��������
		while(next != NULL)
		{
			temp = next->_next;
			next->_next = prior;
			prior = next;
			next = temp;
		}
		//���һ������ǰ��Ľڵ�Ϊ���ú������ͷ�ڵ�
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
	_QuickSort(prev->_next, tail);//��������Ӧ�ô�perv->_next��ʼ���ַ�Χ
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
