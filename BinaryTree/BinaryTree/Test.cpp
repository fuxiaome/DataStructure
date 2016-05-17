#include "BinaryTree.hpp"

int main()
{
	char *str = "124##5##36###";
	BinaryTree<char> binTree(str);
	binTree.PreOrder();
	binTree.InOrder();
	binTree.PostOrder();
	binTree.LevelPrint();
	cout<<endl;
	binTree.PreOrder_NonR();
	binTree.PostOrder_NonR();
	cout<<binTree.Size()<<endl;
	cout<<binTree.Depth()<<endl;
	return 0;
}
