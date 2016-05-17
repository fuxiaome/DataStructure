//#include"HashTable.hpp"
#include"HashTableBucket.hpp"

//void Test1()
//{
//	HashTable<int> ht(10);
//
//	ht.Push(1);
//	ht.Push(10);
//	ht.Push(15);
//	ht.Push(20);
//	ht.Push(40);
//	ht.Show();
//	ht.Remove(20);
//	ht.Remove(15);
//	ht.Show();
//}

void Test2()
{
	HashTableBucket<int, int> ht(17);
	ht.Add(1, 1);
	ht.Add(2, 2);
	ht.Add(11, 11);
	ht.Add(11, 22);
	ht.Add(22, 33);
	ht.Add(18, 18);
	ht.Show();
	ht.Statistics();
	for(int i=100; i<400; ++i)
	{
		ht.Add(i, i);
	}
	ht.Remove(22);
	cout<<endl;
	ht.Show();
	cout<<"find 11->"<<ht.Find(11)<<endl;
	cout<<"find 33->"<<ht.Find(33)<<endl;
	ht.Statistics();
}

int main()
{
//	Test1();
	Test2();
	return 0;
}