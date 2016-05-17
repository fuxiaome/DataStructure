#include <iostream>

using namespace std;

//表示广义表的结点类型
enum NodeType
{
	HEAD_TYPE,//头结点类型
	VALUE_TYPE,//值结点类型
	SUB_TYPE//子表类型
};

//表示广义表结点的结构体
struct GeneraListNode
{
	NodeType _type;//结点类型
	GeneraListNode *_next;//存放结点的下一个元素的地址
	//一个结点要么是值结点要么是子表，故用联合体来存放节省一定的空间
	//若是值结点则存放的是值，是子表结点的话存放的是子表结点头结点的地址
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
	GeneraListNode *_link;//用来存放广义表头结点地址
public:
	GeneraList(const char *str)
		:_link(NULL)
	{
		_CreateGeneraList(_link, str);//根据指定序列创建广义表
	}

	~GeneraList()
	{}
public:
	void Print();//对外提供的打印广义表的接口
	int Size();//广义表中值结点的数目的对外获取接口
	int Depth();//广义表的最深层次的对外获取接口
private:
	void _CreateGeneraList(GeneraListNode *& link, const char *& str);
	bool _IsValue(const char ch);//判断指定字符是否为值结点所允许的类型
	int _Size(GeneraListNode *head);//计算广义表中值结点的数目的实现
	int _Depth(GeneraListNode *head);//计算广义表的最深层次的实现
	void _Print(GeneraListNode *link);//打印广义表的接口的底层实现
};

//创建广义表
void GeneraList::_CreateGeneraList(GeneraListNode *& link, const char *& str)
{
	//广义表最前端有一个头结点，用来记录实现广义表链表的首地址
	//故每次调用该创建广义表的函数首先创建一个头结点
	GeneraListNode* head = new GeneraListNode(HEAD_TYPE, NULL);
	head->_next = NULL;
	link = head;
	GeneraListNode* cur = link;//用来记录创建广义表链表时当前创建出的结点位置游标指针
	str++;//将广义表序列后移,相当于跳过了'('
	
	while(*str != '\0')
	{
		if(_IsValue(*str)){//如果当前扫描到的字符是值
			//创建一个值结点
			GeneraListNode* newNode = new GeneraListNode(VALUE_TYPE, *str);
			newNode->_next = NULL;
			cur->_next = newNode;//将该值结点加入到链表中
			cur = cur->_next;//游标后移
			str++;//将广义表序列后移
		}else if(*str == '('){//如果扫描到'('创建子表结点
			GeneraListNode* subLink = new GeneraListNode(SUB_TYPE, NULL);
			subLink->_next = NULL;
			cur->_next = subLink;//将子表结点加入到链表中
			cur = cur->_next;
			_CreateGeneraList(cur->_subLink, str);//递归创建子表
		}else if(*str == ')'){
			str++;
			return;//若扫描到')'表示广义表创建结束
		}else{
			str++;//空格等其他无效字符跳过
		}
	}
}

int GeneraList::Size()
{
	return _Size(_link);
}

//计算广义表值结点的个数
int GeneraList::_Size(GeneraListNode *head)
{
	int size = 0;
	GeneraListNode *cur = head;
	while(cur != NULL){
		if(cur->_type == VALUE_TYPE){
			++size;//遇到值结点则将size加一
		}else if(cur->_type == SUB_TYPE){
			size += _Size(cur->_subLink);//遇到子表进行递归
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
	int depth = 1,maxDepth = 1;//depth表示当前表的深度，maxDepth表示目前最大的深度
	GeneraListNode *cur = head;
	while(cur != NULL){
		if(cur->_type == SUB_TYPE){
			depth += _Depth(cur->_subLink);
		}
		if(depth > maxDepth){//更新最大深度
			maxDepth = depth;
			depth = 1;//将当前深度复位
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

//打印广义表
void GeneraList::_Print(GeneraListNode *link)
{
	GeneraListNode *cur = link;//遍历广义表的游标
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
			_Print(cur->_subLink);//遇到子表递归打印
			if(cur->_next != NULL)//如果打印完子表后广义表未结束则打印','
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
