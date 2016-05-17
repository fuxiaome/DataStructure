#include<iostream>

using namespace std;

//表示节点的类型
enum NodeTag 
{
	LINK,
	THREAD
};

//定义节点结构体类型
template<class T>
struct ThreadBinTreeNode
{
	T _data;
	ThreadBinTreeNode<T> *_lchild;
	ThreadBinTreeNode<T> *_rchild;
	NodeTag _ltag;
	NodeTag _rtag;
	ThreadBinTreeNode(const T &data)
		:_data(data)
		,_lchild(NULL)
		,_rchild(NULL)
		,_ltag(LINK)
		,_rtag(LINK)
	{}
};

template<class T>
class ThreadBinTree
{
private:
	ThreadBinTreeNode<T> *_root;//线索二叉树的根节点
	int _arrSize;//创建二叉树数时传入数组的大小
	const T &_invalid;//先序创建二叉树时表示无效节点的标志
public:
	ThreadBinTree(const T *array, int size, const T &invalid)
		:_arrSize(size)
		,_invalid(invalid)
	{
		int index = 0;
		_CreateThreadBinTree(array, _root, index);
	}
	ThreadBinTree(const ThreadBinTree &t)
	{}
	~ThreadBinTree()
	{}
public:
	void PrevOrderThread();//先序线索化二叉树
	void PrevOrderPrint();//先序打印二叉树
	void InOrderThread();//中序线索化二叉树
	void InOrderPrint();//中序打印二叉树
	void PostOrderThread();//后序线索化二叉树
	void PostOrderPrint();//后序打印二叉树
private:
	void _CreateThreadBinTree(const T* array, ThreadBinTreeNode<T> *&root, int &index);//利用递归先序创建二叉树
	void _PrevOrderThread(ThreadBinTreeNode<T> *&cur, ThreadBinTreeNode<T> *&prev);//递归先序线索化二叉树
	void _InOrderThread(ThreadBinTreeNode<T> *& cur, ThreadBinTreeNode<T> *& prev);//递归中序线索化二叉树
	void _PostOrderThread(ThreadBinTreeNode<T> *&cur, ThreadBinTreeNode<T> *&prev);//递归后序线索化二叉树
	ThreadBinTreeNode * _Parent(ThreadBinTreeNode<T> * node);//求一个指定节点的父节点，后序遍历线索化二叉树时使用
};

//利用递归先序创建二叉树，index表示当前读取到的用于创建二叉树的数组的元素下标
template<class T>
void ThreadBinTree<T>::_CreateThreadBinTree(const T* array, ThreadBinTreeNode<T> *&root, int &index)
{
	if(index < _arrSize && array[index] != _invalid)
	{
		root = new ThreadBinTreeNode<T>(array[index]);
		_CreateThreadBinTree(array, root->_lchild, ++index);
		_CreateThreadBinTree(array, root->_rchild, ++index);
	}
}

template<class T>
void ThreadBinTree<T>::PrevOrderThread()
{
	ThreadBinTreeNode<T> *prev = NULL;
	_PrevOrderThread(_root, prev);
}

template<class T>
void ThreadBinTree<T>::_PrevOrderThread(ThreadBinTreeNode<T> *&cur, ThreadBinTreeNode<T> *&prev)
{
	if(cur){
		if(cur->_lchild == NULL)//若左孩子为空，对左孩子进行线索化
		{
			cur->_ltag = THREAD;
			cur->_lchild = prev;
		}

		if(prev && prev->_rchild == NULL)//若前驱节点的右孩子为空，对前驱节点的右孩子进行线索化
		{
			prev->_rtag = THREAD;
			prev->_rchild = cur;
		}
		prev = cur;
		if (cur->_ltag == LINK)//防止左孩子已经线索化过，再次递归造成死循环
		{
			_PrevOrderThread(cur->_lchild, prev);
		}
		if(cur->_rtag == LINK)//防止右孩子已经线索化过，再次递归造成死循环
		{
			_PrevOrderThread(cur->_rchild, prev);
		}
	}
}

template<class T>
void ThreadBinTree<T>::PrevOrderPrint()
{
	if(_root == NULL)
	{
		cout<<"当前二叉树为空！"<<endl;
		return;
	}
	ThreadBinTreeNode<T> *cur = _root;
	while(cur)
	{
		cout<<cur->_data<<" ";

		while (cur->_ltag != THREAD)//依次访问左子树的各个根节点，直至左子树叶子节点访问完成
		{
			cur = cur->_lchild;
			cout<<cur->_data<<" ";
		}
		//！！为了解决后继结点的右孩子仍未后继，造成死循环，故使用while而不是if
		while(cur && cur->_rtag == THREAD)
		{
			cur = cur->_rchild;
			cout<<cur->_data<<" ";
		}
		cur = cur->_rchild;//访问后继的右子树
	}
	cout<<endl;
}

template<class T>
void ThreadBinTree<T>::InOrderThread()
{
	ThreadBinTreeNode<T> *prev = NULL;//用来记录上一个访问过的节点
	_InOrderThread(_root, prev);
}

//利用递归对二叉树进行中序线索化
template<class T>
void ThreadBinTree<T>::_InOrderThread(ThreadBinTreeNode<T> *& cur, ThreadBinTreeNode<T> *& prev)
{
	if(cur)
	{
		_InOrderThread(cur->_lchild, prev);
		if (cur->_lchild == NULL)//若左孩子为空对左孩子进行线索化
		{
			cur->_ltag = THREAD;
			cur->_lchild = prev;//将左孩子指向前驱节点
		}
		if (prev && prev->_rchild == NULL)//若前驱节点的右孩子为空则对其进行线索化
		{
			prev->_rtag = THREAD;
			prev->_rchild = cur;//将前驱节点的右孩子指向其后继，后继即为当前节点
		}
		prev = cur;//将当前节点赋值给上一个访问的节点
		_InOrderThread(cur->_rchild, prev);
	}
}

//中序打印线索化二叉树
template<class T>
void ThreadBinTree<T>::InOrderPrint()
{
	if(_root == NULL)
	{
		cout<<"当前二叉树为空！"<<endl;
		return;
	}
	ThreadBinTreeNode<T> *cur = _root;
	while(cur)
	{
		//现将cur指向当前子树的最左边
		while(cur->_ltag != THREAD)
		{
			cur = cur->_lchild;
		}

		cout<<cur->_data<<" ";

		//！！为了解决后继结点的右孩子仍未后继，故使用while而不是if
		while( cur && cur->_rtag == THREAD)
		{
			cur = cur->_rchild;//指向其后继
			cout<<cur->_data<<" ";//访问后继的跟结点
		}

		cur = cur->_rchild;
	}
	cout<<endl;
}

template<class T>
void ThreadBinTree<T>::PostOrderThread()
{
	ThreadBinTreeNode<T> *prev = NULL;
	_PostOrderThread(_root, prev);
}

template<class T>
void ThreadBinTree<T>::_PostOrderThread(ThreadBinTreeNode<T> *&cur, ThreadBinTreeNode<T> *&prev)
{
	if (cur)
	{
		_PostOrderThread(cur->_lchild, prev);
		_PostOrderThread(cur->_rchild, prev);

		if(cur->_lchild == NULL)
		{
			cur->_ltag = THREAD;
			cur->_lchild = prev;
		}

		if(prev && prev->_rchild == NULL)
		{
			prev->_rtag = THREAD;
			prev->_rchild = cur;
		}
		prev = cur;
	}
}

template<class T>
ThreadBinTreeNode<T> * ThreadBinTree<T>::_Parent(ThreadBinTreeNode<T> node)
{
	//找父节点的思想为：利用中序遍历的方法访问线索二叉树的每一个节点，若该节点的左孩子或者右孩子等于指定节点
	//则该节点便为要找的节点，将其返回
	if(_root == NULL || _root == node)
	{
		return NULL;
	}

	ThreadBinTreeNode<T> cur = _root;
	while (cur )
	{
		while(cur->_lchildl == LINK){
			cur = cur->lchild;
		}
		
		while( cur && cur->rtag == THREAD )
		{
			cur = cur->rchild;
			if (cur->_lchild == node || cur->_rchild == node)
			{
				return cur;
			}
		}
		cur = cur->rchild;
	}
	return NULL;
}

//存在问题
template<class T>
void ThreadBinTree<T>::PostOrderPrint()
{
	if(_root == NULL)
	{
		cout<<"当前二叉树为空！"<<endl;
		return;
	}
	ThreadBinTreeNode<T> *cur = _root;
	bool onlyFirst = true;
	while(cur && cur != _root || onlyFirst)
	{
		onlyFirst = false;
		ThreadBinTreeNode<T> *root = cur;
		while (cur->_ltag != THREAD)
		{
			cur = cur->_lchild;
		}
		if (cur->_rtag == LINK && cur->_rchild != NULL)
		{
			cur = cur->_rchild;
			continue;
		}

		cout<<cur->_data<<" ";
		while (cur && cur->_rtag == THREAD)
		{
			cur = cur->_rchild;
			cout<<cur->_data<<" ";
		}
		cur = root->_rchild;
	}
	cout<<endl;
}

