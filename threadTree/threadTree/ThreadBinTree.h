
template<class Type>

enum
{
	LINK,THREAD
};

class BinTreeNode
{
private:
	BinTreeNode root;
public:
	void CreateThreadTree();
	BinTreeNode<Type>*First()const
	{
		return First(root);
	}
	BinTreeNode<Type>*Last()const
	{
		return Last(root);
	}
	BinTreeNode<Type>*Next(BinTreeNode<Type> *cur)const
	{
		return Next(root,cur);
	}
	BinTreeNode<Type>*Parent(BinTreeNode<Type> *cur)const
	{
		return Parent(root,cur);
	}
	BinTreeNode<Type>*Find(const Type &key)const
	{
		return Find(root,key);
	}
	void InOrder()
	{
		InOrder(root);
	}
private:
	void CreateThreadTree(BinTreeNode<Type> &p,
						  BinTreeNode<Type> &pre)
	{
		CreateThreadTree(p->lchild,pre);
		if(p->lchild != NULL && p->lchild == NULL)
		{
			p->lchild = pre;
			p->ltag = THREAD;
		}
		if(p->rchild != NULL && p->rchild == NULL)
		{
			p->rchild = pre;
			p->rtag = THREAD;
		}
		p = pre;
		
		CreateThreadTree(p->rchild,pre);
	}
	/*��ǰ�ڵ������߽ڵ�*/
	BinTreeNode<Type>*First(BinTreeNode<Type> *t)
	{
		if(t == NULL)return NULL;
		if(cur->ltag == Thread)
			return cur;
		return First(cur->lchild);
	}
	/*��ǰ�ڵ�����ұ߽ڵ�*/
	BinTreeNode<Type>*Last(BinTreeNode<Type> *t)
	{
		if(t == NULL)return NULL;
		if(cur->rtag == Thread)
			return cur;
		return Last(cur->rchild);
	}
	/*��ǰ���ĺ��*/
	BinTreeNode<Type>*Next(BinTreeNode<Type> *t,
						   BinTreeNode<Type> *cur)
	{
		BinTreeNode<Type> *p;
		if(cur == NULL)return NULL;
		if(cur->rtag == Thread)
			return cur->rchild;
		return First(cur->rchild);
	}
	/*��ǰ���ĸ��ڵ�*/
	BinTreeNode<Type>*Parent(BinTreeNode<Type> *t,
							 BinTreeNode<Type> *cur)const
	{
		BinTreeNode<Type> *temp;
		if(cur == t)return NULL;//��Ϊ���ڵ㷵�ؿ�

		for(temp=First();temp!=NULL;temp=Next(temp))
		{
			if(temp->lchild == cur || temp->rchild == cur)
				return temp;
		}
		return NULL;//�������в����ڸýڵ�
	}
	/*�Խڵ��key�����в��Ҹýڵ�*/
	BinTreeNode<Type>*Find(BinTreeNode<Type> *t,
						   const Type &key)
	{
		BinTreeNode<Type> *p;
		for(p=First();p!=NULL&&p->data!=key;p=Next(p));
		return p;
	}
	/*�������������������*/
	void InOrder(BinTreeNode<Type> *t)
	{
		BinTreeNode<Type> *p;
		for(p=First();p!=NULL;p=Next(p))
		{
			cout<<p->data<<" ";
		}
	}
}