#include<iostream>

using namespace std;

//对INT进行类型重命名
typedef int DataType;

//利用枚举表示出元素的所有可能类型
enum ElemType
{
	ADD,SUB,MUL,DIV,MOD,NUM
};

//定义结构体来描述元素
struct Elem
{
	ElemType _elemType,//表示元素类型
	DataType _data//表示元素数据类型
	Elem(type,data)
		:_elemType = NULL
		 ,_data = NULL
	{
		_elemType = type;
		_data = data;
	}
};

class SuffixExpression
{
public:
	SuffixExpression()
		:_expression(0),
		 _elemCount(0)
	{
	}
	SuffixExpression(const string &exp)
	{
		if(exp == NULL)
		{
			cout<<"参数不能为空！"<<endl;
			return;
		}
		_elemCount = exp.length;
	}
	SuffixExpression(const Elem* &exp)
	{
		if(exp == NULL)
		{
			cout<<"参数不能为空"<<endl;
			return;
		}
		_expression = exp;
		_elemCount = sizeof(_expression)/sizeof(_expression[0]);
	}
private:
	//把字符串形式的中缀表达式进行解析为后缀表达式，且表达式中的每个元素存储在Elem数组中
	Elem* _ChangeExpression(const Elem& exp);
	void _ParseExpression(const string& exp);
	int _OperPriority(char op1,char op2);
private:
	Elem* _expression;
	int _elemCount;
}

void SuffixExpresion::_ParseExpression(const string &exp)
{
	MyStack<char> tempStack;//中缀转后缀过程中借助的中间栈
	tempStack.Push("#");

	for(int i=0; i<string.size();++i)
	{
		if(isdigit(exp[i]))
		{
			string num = exp[i];
			while(isdigit(exp[i+1]))
			{
				num += exp[++i];
			}
			cout<<atoi(num)<<" ";
		}else if(exp[i] == "+")
		{
			if()
		}
	}
}

int SuffixExpression::_OperPriority(char op1,char op2)
{
	int prior = 0;
	if(op1 == "#")
	{
		prior = -1;
	}
	else if((op1=="+" || op1=="-"))
	{
		if(op2=="+" || op2=="-")
			prior = 0;
		else
			prior = -1;
	}
	else
	{
		if(op2=="*" || op2=="/")
			prior = 0;
		else
			prior = -1;
	}
}

