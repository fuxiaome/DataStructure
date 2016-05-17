
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
	/*求当前节点的最左边节点*/
	BinTreeNode<Type>*First(BinTreeNode<Type> *t)
	{
		if(t == NULL)return NULL;
		if(cur->ltag == Thread)
			return cur;
		return First(cur->lchild);
	}
	/*求当前节点的最右边节点*/
	BinTreeNode<Type>*Last(BinTreeNode<Type> *t)
	{
		if(t == NULL)return NULL;
		if(cur->rtag == Thread)
			return cur;
		return Last(cur->rchild);
	}
	/*求当前结点的后继*/
	BinTreeNode<Type>*Next(BinTreeNode<Type> *t,
						   BinTreeNode<Type> *cur)
	{
		BinTreeNode<Type> *p;
		if(cur == NULL)return NULL;
		if(cur->rtag == Thread)
			return cur->rchild;
		return First(cur->rchild);
	}
	/*求当前结点的父节点*/
	BinTreeNode<Type>*Parent(BinTreeNode<Type> *t,
							 BinTreeNode<Type> *cur)const
	{
		BinTreeNode<Type> *temp;
		if(cur == t)return NULL;//若为根节点返回空

		for(temp=First();temp!=NULL;temp=Next(temp))
		{
			if(temp->lchild == cur || temp->rchild == cur)
				return temp;
		}
		return NULL;//表明树中不存在该节点
	}
	/*以节点的key在树中查找该节点*/
	BinTreeNode<Type>*Find(BinTreeNode<Type> *t,
						   const Type &key)
	{
		BinTreeNode<Type> *p;
		for(p=First();p!=NULL&&p->data!=key;p=Next(p));
		return p;
	}
	/*中序遍历线索化二叉树*/
	void InOrder(BinTreeNode<Type> *t)
	{
		BinTreeNode<Type> *p;
		for(p=First();p!=NULL;p=Next(p))
		{
			cout<<p->data<<" ";
		}
	}
}