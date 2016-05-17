#include "ThreadBinTree.hpp"

//��������������������
void Test1()
{
	int array[] = {1,2,4,EOF,EOF,5,EOF,EOF,3,6,EOF,EOF,EOF};
	ThreadBinTree<int> thdTree(array, sizeof(array)/sizeof(array[0]),EOF);
	thdTree.InOrderThread();
	thdTree.InOrderPrint();
}
//��������������������
void Test2()
{
	int array[] = {1,2,4,EOF,EOF,5,EOF,EOF,3,6,EOF,EOF,EOF};
	ThreadBinTree<int> thdTree(array, sizeof(array)/sizeof(array[0]),EOF);
	thdTree.PrevOrderThread();
	thdTree.PrevOrderPrint();
}
//���Ժ���������������
void Test3()
{
	int array[] = {1,2,4,EOF,EOF,5,EOF,EOF,3,6,EOF,EOF,EOF};
	ThreadBinTree<int> thdTree(array, sizeof(array)/sizeof(array[0]),EOF);
	thdTree.PostOrderThread();
	thdTree.PostOrderPrint();
	int array1[] = {1,2,EOF,4,5,EOF,EOF,EOF,3,6,7,EOF,EOF,8,EOF,EOF,EOF};
	ThreadBinTree<int> thdTree1(array1, sizeof(array1)/sizeof(array1[0]),EOF);
	thdTree1.PostOrderThread();
	thdTree1.PostOrderPrint();
}

int main()
{
	Test1();
	Test2();
	Test3();
	return 0;
}
