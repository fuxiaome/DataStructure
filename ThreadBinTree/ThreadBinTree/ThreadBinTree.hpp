#include<iostream>

using namespace std;

//��ʾ�ڵ������
enum NodeTag 
{
	LINK,
	THREAD
};

//����ڵ�ṹ������
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
	ThreadBinTreeNode<T> *_root;//�����������ĸ��ڵ�
	int _arrSize;//������������ʱ��������Ĵ�С
	const T &_invalid;//���򴴽�������ʱ��ʾ��Ч�ڵ�ı�־
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
	void PrevOrderThread();//����������������
	void PrevOrderPrint();//�����ӡ������
	void InOrderThread();//����������������
	void InOrderPrint();//�����ӡ������
	void PostOrderThread();//����������������
	void PostOrderPrint();//�����ӡ������
private:
	void _CreateThreadBinTree(const T* array, ThreadBinTreeNode<T> *&root, int &index);//���õݹ����򴴽�������
	void _PrevOrderThread(ThreadBinTreeNode<T> *&cur, ThreadBinTreeNode<T> *&prev);//�ݹ�����������������
	void _InOrderThread(ThreadBinTreeNode<T> *& cur, ThreadBinTreeNode<T> *& prev);//�ݹ�����������������
	void _PostOrderThread(ThreadBinTreeNode<T> *&cur, ThreadBinTreeNode<T> *&prev);//�ݹ����������������
	ThreadBinTreeNode * _Parent(ThreadBinTreeNode<T> * node);//��һ��ָ���ڵ�ĸ��ڵ㣬�������������������ʱʹ��
};

//���õݹ����򴴽���������index��ʾ��ǰ��ȡ�������ڴ����������������Ԫ���±�
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
		if(cur->_lchild == NULL)//������Ϊ�գ������ӽ���������
		{
			cur->_ltag = THREAD;
			cur->_lchild = prev;
		}

		if(prev && prev->_rchild == NULL)//��ǰ���ڵ���Һ���Ϊ�գ���ǰ���ڵ���Һ��ӽ���������
		{
			prev->_rtag = THREAD;
			prev->_rchild = cur;
		}
		prev = cur;
		if (cur->_ltag == LINK)//��ֹ�����Ѿ������������ٴεݹ������ѭ��
		{
			_PrevOrderThread(cur->_lchild, prev);
		}
		if(cur->_rtag == LINK)//��ֹ�Һ����Ѿ������������ٴεݹ������ѭ��
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
		cout<<"��ǰ������Ϊ�գ�"<<endl;
		return;
	}
	ThreadBinTreeNode<T> *cur = _root;
	while(cur)
	{
		cout<<cur->_data<<" ";

		while (cur->_ltag != THREAD)//���η����������ĸ������ڵ㣬ֱ��������Ҷ�ӽڵ�������
		{
			cur = cur->_lchild;
			cout<<cur->_data<<" ";
		}
		//����Ϊ�˽����̽����Һ�����δ��̣������ѭ������ʹ��while������if
		while(cur && cur->_rtag == THREAD)
		{
			cur = cur->_rchild;
			cout<<cur->_data<<" ";
		}
		cur = cur->_rchild;//���ʺ�̵�������
	}
	cout<<endl;
}

template<class T>
void ThreadBinTree<T>::InOrderThread()
{
	ThreadBinTreeNode<T> *prev = NULL;//������¼��һ�����ʹ��Ľڵ�
	_InOrderThread(_root, prev);
}

//���õݹ�Զ�������������������
template<class T>
void ThreadBinTree<T>::_InOrderThread(ThreadBinTreeNode<T> *& cur, ThreadBinTreeNode<T> *& prev)
{
	if(cur)
	{
		_InOrderThread(cur->_lchild, prev);
		if (cur->_lchild == NULL)//������Ϊ�ն����ӽ���������
		{
			cur->_ltag = THREAD;
			cur->_lchild = prev;//������ָ��ǰ���ڵ�
		}
		if (prev && prev->_rchild == NULL)//��ǰ���ڵ���Һ���Ϊ����������������
		{
			prev->_rtag = THREAD;
			prev->_rchild = cur;//��ǰ���ڵ���Һ���ָ�����̣���̼�Ϊ��ǰ�ڵ�
		}
		prev = cur;//����ǰ�ڵ㸳ֵ����һ�����ʵĽڵ�
		_InOrderThread(cur->_rchild, prev);
	}
}

//�����ӡ������������
template<class T>
void ThreadBinTree<T>::InOrderPrint()
{
	if(_root == NULL)
	{
		cout<<"��ǰ������Ϊ�գ�"<<endl;
		return;
	}
	ThreadBinTreeNode<T> *cur = _root;
	while(cur)
	{
		//�ֽ�curָ��ǰ�����������
		while(cur->_ltag != THREAD)
		{
			cur = cur->_lchild;
		}

		cout<<cur->_data<<" ";

		//����Ϊ�˽����̽����Һ�����δ��̣���ʹ��while������if
		while( cur && cur->_rtag == THREAD)
		{
			cur = cur->_rchild;//ָ������
			cout<<cur->_data<<" ";//���ʺ�̵ĸ����
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
	//�Ҹ��ڵ��˼��Ϊ��������������ķ�������������������ÿһ���ڵ㣬���ýڵ�����ӻ����Һ��ӵ���ָ���ڵ�
	//��ýڵ��ΪҪ�ҵĽڵ㣬���䷵��
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

//��������
template<class T>
void ThreadBinTree<T>::PostOrderPrint()
{
	if(_root == NULL)
	{
		cout<<"��ǰ������Ϊ�գ�"<<endl;
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

