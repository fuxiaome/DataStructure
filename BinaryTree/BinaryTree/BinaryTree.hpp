#pragma once
#include<iostream>
#include <queue>
#include <stack>

using namespace std;

template<class T>
struct BinTreeNode
{
	T _data;
	BinTreeNode* _lchild;
	BinTreeNode* _rchild;

	BinTreeNode(T data)
		:_data(T())
		,_lchild(NULL)
		,_rchild(NULL)
	{
		_data = data;
	}
};

template<class T>
class BinaryTree
{
private:
	BinTreeNode<T> *_root;
public:
	BinaryTree()
		:root(NULL)
	{}
	BinaryTree(char *str)//���������ַ����д���������
	{
		_CreateBinTree(_root, str);
	}
	BinaryTree(BinaryTree<T> &tree);
	BinaryTree &operator=(BinaryTree<T> &tree);
	~BinaryTree()
	{}
public:
	void PreOrder();//�ݹ��������
	void PreOrder_NonR();//�ǵݹ��������
	void InOrder();//�ݹ��������
	void InOrder_NonR();//�ǵݹ��������
	void PostOrder();//�ݹ�������
	void PostOrder_NonR();//�ǵݹ�������
	void LevelPrint();//����δ�ӡ
	void TreePrint();//����״��ӡ������
	int Size();//������������
	int Depth();//���������
private:
	void _CreateBinTree(BinTreeNode<T> *& root, char *& str);
	void _PreOrder(BinTreeNode<T> *root);
	void _InOrder(BinTreeNode<T> *root);
	void _PostOrder(BinTreeNode<T> *root);
	void _LevelPrint(BinTreeNode<T> *root);
	int _Size(BinTreeNode<T> *root);
	int _Depth(BinTreeNode<T> *root);
};

template<class T>
void BinaryTree<T>::_CreateBinTree(BinTreeNode<T> *& root, char *& str)
{
	if(*str != '#' && *str != '\0')
	{
		root = new BinTreeNode<T>(*str);
		_CreateBinTree(root->_lchild, ++str);
		_CreateBinTree(root->_rchild, ++str);
	}
}
//ʹ�õݹ����򴴽�������
template<class T>
void BinaryTree<T>::PreOrder()
{
	_PreOrder(_root);
	cout<<endl;
}

template<class T>
void BinaryTree<T>::_PreOrder(BinTreeNode<T> *root)
{
	if(root != NULL)
	{
		cout<<root->_data<<" ";
		_PreOrder(root->_lchild);
		_PreOrder(root->_rchild);
	}
}
//ʹ�õݹ����򴴽�������
template<class T>
void BinaryTree<T>::InOrder()
{
	_InOrder(_root);
	cout<<endl;
}

template<class T>
void BinaryTree<T>::_InOrder(BinTreeNode<T> *root)
{
	if(root != NULL)
	{
		_InOrder(root->_lchild);
		cout<<root->_data<<" ";
		_InOrder(root->_rchild);
	}
}
//ʹ�õݹ���򴴽�������
template<class T>
void BinaryTree<T>::PostOrder()
{
	_PostOrder(_root);
	cout<<endl;
}

template<class T>
void BinaryTree<T>::_PostOrder(BinTreeNode<T> *root)
{
	if(root != NULL)
	{
		_PostOrder(root->_lchild);
		_PostOrder(root->_rchild);
		cout<<root->_data<<" ";
	}
}

template<class T>
void BinaryTree<T>::LevelPrint()
{
	_LevelPrint(_root);
	cout<<endl;
}

template<class T>
void BinaryTree<T>::_LevelPrint(BinTreeNode<T> *root)
{
	if(root == NULL)
	{
		return;
	}
	queue<BinTreeNode<T> *> q;//����һ������ʵ�ֲ�δ�ӡ
	q.push(root);//��������ȼ��������
	while (!q.empty())//���в�Ϊ�ճ������д�ӡ
	{
		BinTreeNode<T> *front;
		front = q.front();
		cout<<front->_data<<" ";//��ӡ��ǰ�Ķ�ͷԪ��
		q.pop();//��ͷԪ�س�����
		if (front->_lchild != NULL)//����ڵ�����ڵ���������
		{
			q.push(front->_lchild);
		}
		if(front->_rchild != NULL)//���ҽڵ����ҽڵ���������
		{
			q.push(front->_rchild);
		}
	}
}

template<class T>
void BinaryTree<T>::PreOrder_NonR()
{
	if (_root == NULL)
		return;
	BinTreeNode<T> *cur = _root;
	stack<BinTreeNode<T> *> stk;//��ջ��ʵ�ַǵݹ���������

	while(!stk.empty() || cur!=NULL)
	{
		while(cur)//�ҵ���ǰ�����������
		{
			cout<<cur->_data<<" ";
			stk.push(cur);
			cur = cur->_lchild;
		}

		if(!stk.empty())
		{
			cur = stk.top();
			stk.pop();
			cur = cur->_rchild;
		}
	}
	cout<<endl;
}

//�ǵݹ��������
template<class T>
void BinaryTree<T>::InOrder_NonR()
{
	if(_root == NULL)
		return;
	stack<BinTreeNode<T> *> stk;
	BinTreeNode<T> *cur = _root;
	stk.push(cur);

	while(!stk.empty())
	{
		while(cur->_lchild)//�������������ĸ����ڵ�������ջ
		{
			stk.push(cur->_lchild);
			cur = cur->_lchild;
		}

		cur = stk.top();
		cout<<cur->_data<<" ";//ȡ��ջ��Ԫ�ؽ��з���
		stk.pop();

		if(cur->_rchild)//�����Һ������Һ�����ջ
		{
			stk.push(cur->_rchild);
			cur = cur->_rchild;
		}
	}
	cout<<endl;
}

//�ǵݹ�������
template<class T>
void BinaryTree<T>::PostOrder_NonR()
{
	if(_root == NULL)
		return;
	stack<BinTreeNode<T> *> stk;
	BinTreeNode<T> *cur = _root;
	BinTreeNode<T> *visited = NULL;//������¼��һ�η��ʵĽ��

	while ( cur != NULL || !stk.empty())
	{
		while(cur)
		{
			stk.push(cur);
			cur = cur->_lchild;
		}

		BinTreeNode<T> *top = stk.top();
		cur = top;

		//���Һ���Ϊ��,���������Ѿ����ʹ�������ʸ��ڵ�
		if(cur->_rchild == NULL || cur->_rchild == visited)
		{
			cout<<top->_data<<" ";
			stk.pop();
			visited = top;
			cur = NULL;
		}else{//�������������
			cur = cur->_rchild;
		}
	}
	cout<<endl;
}

void TreePrint()
{

}

//�������ڵ����
template<class T>
int BinaryTree<T>::Size()
{
	return _Size(_root);
}

template<class T>
int BinaryTree<T>::_Size(BinTreeNode<T> *root)
{
	if(NULL == root)
		return 0;
	return _Size(root->_lchild)+_Size(root->_rchild)+1;
}

//������������
template<class T>
int BinaryTree<T>::Depth()
{
	return _Depth(_root);
}

template<class T>
int BinaryTree<T>::_Depth(BinTreeNode<T> *root)
{
	if (root == NULL)
		return 0;
	int ld = _Depth(root->_lchild);
	int rd = _Depth(root->_rchild);
	return ld > rd ? ld+1 : rd+1;
}
