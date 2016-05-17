#include"BitMap.hpp"

void Test1()
{
	BitSet bs(40);
	bs.Set(2);
	bs.Set(5);
	cout<<bs.Test(2)<<endl;
	cout<<bs.Test(5)<<endl;
	cout<<bs.Test(7)<<endl;
	bs.Reset(2);
	cout<<"after reset 2 :"<<bs.Test(2)<<endl;
	bs.Clear();
}

int main()
{
	Test1();
	return 0;
}