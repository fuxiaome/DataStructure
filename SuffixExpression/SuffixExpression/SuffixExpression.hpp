#include<iostream>

using namespace std;

//��INT��������������
typedef int DataType;

//����ö�ٱ�ʾ��Ԫ�ص����п�������
enum ElemType
{
	ADD,SUB,MUL,DIV,MOD,NUM
};

//����ṹ��������Ԫ��
struct Elem
{
	ElemType _elemType,//��ʾԪ������
	DataType _data//��ʾԪ����������
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
			cout<<"��������Ϊ�գ�"<<endl;
			return;
		}
		_elemCount = exp.length;
	}
	SuffixExpression(const Elem* &exp)
	{
		if(exp == NULL)
		{
			cout<<"��������Ϊ��"<<endl;
			return;
		}
		_expression = exp;
		_elemCount = sizeof(_expression)/sizeof(_expression[0]);
	}
private:
	//���ַ�����ʽ����׺���ʽ���н���Ϊ��׺���ʽ���ұ��ʽ�е�ÿ��Ԫ�ش洢��Elem������
	Elem* _ChangeExpression(const Elem& exp);
	void _ParseExpression(const string& exp);
	int _OperPriority(char op1,char op2);
private:
	Elem* _expression;
	int _elemCount;
}

void SuffixExpresion::_ParseExpression(const string &exp)
{
	MyStack<char> tempStack;//��׺ת��׺�����н������м�ջ
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

