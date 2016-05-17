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
	BinaryTree(char *str)//根据先序字符序列创建二叉树
	{
		_CreateBinTree(_root, str);
	}
	BinaryTree(BinaryTree<T> &tree);
	BinaryTree &operator=(BinaryTree<T> &tree);
	~BinaryTree()
	{}
public:
	void PreOrder();//递归先序遍历
	void PreOrder_NonR();//非递归先序遍历
	void InOrder();//递归中序遍历
	void InOrder_NonR();//非递归中序遍历
	void PostOrder();//递归后序遍历
	void PostOrder_NonR();//非递归后序遍历
	void LevelPrint();//按层次打印
	void TreePrint();//按树状打印二叉树
	int Size();//二叉树结点个数
	int Depth();//二叉树深度
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
//使用递归先序创建二叉树
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
//使用递归中序创建二叉树
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
//使用递归后序创建二叉树
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
	queue<BinTreeNode<T> *> q;//借助一个队列实现层次打印
	q.push(root);//将根结点先加入队列中
	while (!q.empty())//队列不为空持续进行打印
	{
		BinTreeNode<T> *front;
		front = q.front();
		cout<<front->_data<<" ";//打印当前的队头元素
		q.pop();//队头元素出队列
		if (front->_lchild != NULL)//有左节点则将左节点加入队列中
		{
			q.push(front->_lchild);
		}
		if(front->_rchild != NULL)//有右节点则将右节点加入队列中
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
	stack<BinTreeNode<T> *> stk;//用栈来实现非递归的先序遍历

	while(!stk.empty() || cur!=NULL)
	{
		while(cur)//找到当前子树的最左边
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

//非递归中序遍历
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
		while(cur->_lchild)//持续将左子树的各个节点依次入栈
		{
			stk.push(cur->_lchild);
			cur = cur->_lchild;
		}

		cur = stk.top();
		cout<<cur->_data<<" ";//取出栈顶元素进行访问
		stk.pop();

		if(cur->_rchild)//存在右孩子则将右孩子入栈
		{
			stk.push(cur->_rchild);
			cur = cur->_rchild;
		}
	}
	cout<<endl;
}

//非递归后序遍历
template<class T>
void BinaryTree<T>::PostOrder_NonR()
{
	if(_root == NULL)
		return;
	stack<BinTreeNode<T> *> stk;
	BinTreeNode<T> *cur = _root;
	BinTreeNode<T> *visited = NULL;//用来记录上一次访问的结点

	while ( cur != NULL || !stk.empty())
	{
		while(cur)
		{
			stk.push(cur);
			cur = cur->_lchild;
		}

		BinTreeNode<T> *top = stk.top();
		cur = top;

		//若右孩子为空,或右子树已经访问过，则访问根节点
		if(cur->_rchild == NULL || cur->_rchild == visited)
		{
			cout<<top->_data<<" ";
			stk.pop();
			visited = top;
			cur = NULL;
		}else{//否则访问右子树
			cur = cur->_rchild;
		}
	}
	cout<<endl;
}

void TreePrint()
{

}

//二叉树节点个数
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

//二叉树最大深度
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
