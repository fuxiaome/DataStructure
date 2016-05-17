#include <iostream>

using namespace std;

//��ʾ�����Ľ������
enum NodeType
{
	HEAD_TYPE,//ͷ�������
	VALUE_TYPE,//ֵ�������
	SUB_TYPE//�ӱ�����
};

//��ʾ�������Ľṹ��
struct GeneraListNode
{
	NodeType _type;//�������
	GeneraListNode *_next;//��Ž�����һ��Ԫ�صĵ�ַ
	//һ�����Ҫô��ֵ���Ҫô���ӱ���������������Ž�ʡһ���Ŀռ�
	//����ֵ������ŵ���ֵ�����ӱ���Ļ���ŵ����ӱ���ͷ���ĵ�ַ
	union{
		char _value;
		GeneraListNode *_subLink;
	};

	GeneraListNode(NodeType type = HEAD_TYPE, char value = '\0')
		:_type(type)
		,_next(NULL)
	{
		if (type == VALUE_TYPE)
		{
			_value = value;
		}else if(type == SUB_TYPE)
		{
			_subLink = NULL;
		}

	}

};

class GeneraList
{
private:
	GeneraListNode *_link;//������Ź����ͷ����ַ
public:
	GeneraList(const char *str)
		:_link(NULL)
	{
		_CreateGeneraList(_link, str);//����ָ�����д��������
	}

	~GeneraList()
	{}
public:
	void Print();//�����ṩ�Ĵ�ӡ�����Ľӿ�
	int Size();//�������ֵ������Ŀ�Ķ����ȡ�ӿ�
	int Depth();//�����������εĶ����ȡ�ӿ�
private:
	void _CreateGeneraList(GeneraListNode *& link, const char *& str);
	bool _IsValue(const char ch);//�ж�ָ���ַ��Ƿ�Ϊֵ��������������
	int _Size(GeneraListNode *head);//����������ֵ������Ŀ��ʵ��
	int _Depth(GeneraListNode *head);//��������������ε�ʵ��
	void _Print(GeneraListNode *link);//��ӡ�����Ľӿڵĵײ�ʵ��
};

//���������
void GeneraList::_CreateGeneraList(GeneraListNode *& link, const char *& str)
{
	//�������ǰ����һ��ͷ��㣬������¼ʵ�ֹ����������׵�ַ
	//��ÿ�ε��øô��������ĺ������ȴ���һ��ͷ���
	GeneraListNode* head = new GeneraListNode(HEAD_TYPE, NULL);
	head->_next = NULL;
	link = head;
	GeneraListNode* cur = link;//������¼�������������ʱ��ǰ�������Ľ��λ���α�ָ��
	str++;//����������к���,�൱��������'('
	
	while(*str != '\0')
	{
		if(_IsValue(*str)){//�����ǰɨ�赽���ַ���ֵ
			//����һ��ֵ���
			GeneraListNode* newNode = new GeneraListNode(VALUE_TYPE, *str);
			newNode->_next = NULL;
			cur->_next = newNode;//����ֵ�����뵽������
			cur = cur->_next;//�α����
			str++;//����������к���
		}else if(*str == '('){//���ɨ�赽'('�����ӱ���
			GeneraListNode* subLink = new GeneraListNode(SUB_TYPE, NULL);
			subLink->_next = NULL;
			cur->_next = subLink;//���ӱ�����뵽������
			cur = cur->_next;
			_CreateGeneraList(cur->_subLink, str);//�ݹ鴴���ӱ�
		}else if(*str == ')'){
			str++;
			return;//��ɨ�赽')'��ʾ�����������
		}else{
			str++;//�ո��������Ч�ַ�����
		}
	}
}

int GeneraList::Size()
{
	return _Size(_link);
}

//��������ֵ���ĸ���
int GeneraList::_Size(GeneraListNode *head)
{
	int size = 0;
	GeneraListNode *cur = head;
	while(cur != NULL){
		if(cur->_type == VALUE_TYPE){
			++size;//����ֵ�����size��һ
		}else if(cur->_type == SUB_TYPE){
			size += _Size(cur->_subLink);//�����ӱ���еݹ�
		}
		cur = cur->_next;
	}
	return size;
}

int GeneraList::Depth()
{
	return _Depth(_link);
}
int GeneraList::_Depth(GeneraListNode *head)
{
	int depth = 1,maxDepth = 1;//depth��ʾ��ǰ�����ȣ�maxDepth��ʾĿǰ�������
	GeneraListNode *cur = head;
	while(cur != NULL){
		if(cur->_type == SUB_TYPE){
			depth += _Depth(cur->_subLink);
		}
		if(depth > maxDepth){//����������
			maxDepth = depth;
			depth = 1;//����ǰ��ȸ�λ
		}
		cur = cur->_next;
	}
	return maxDepth;
}

void GeneraList::Print()
{
	_Print(_link);
	cout<<endl;
}

//��ӡ�����
void GeneraList::_Print(GeneraListNode *link)
{
	GeneraListNode *cur = link;//�����������α�
	while(cur != NULL){
		if(cur->_type == VALUE_TYPE){
			cout<<cur->_value;
			if(cur->_next != NULL)
			{
				cout<<',';
			}
		}else if(cur->_type == HEAD_TYPE){
			cout<<"(";
		}else if(cur->_type == SUB_TYPE){
			_Print(cur->_subLink);//�����ӱ�ݹ��ӡ
			if(cur->_next != NULL)//�����ӡ���ӱ������δ�������ӡ','
			{
				cout<<",";
			}
		}
		cur = cur->_next;
	}
	cout<<")";
}

bool GeneraList::_IsValue(const char ch)
{
	if(ch >= 'a' && ch <= 'z' ||
	   ch >= 'A' && ch <= 'Z' ||
	   ch >= '0' && ch <= '(')
	{
		return true;
	}
	return false;
}
