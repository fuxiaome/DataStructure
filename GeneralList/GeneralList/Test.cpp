#include"GeneraList.hpp"

//≤‚ ‘ø’±Ì
void Test1()
{
	GeneraList genList("()");
	genList.Print();
	cout<<"Size is :"<<genList.Size()<<endl;
	cout<<"Depth is :"<<genList.Depth()<<endl<<endl;
}
//≤‚ ‘µ•≤„±Ì
void Test2()
{
	GeneraList genList("(a,b)");
	genList.Print();
	cout<<"Size is :"<<genList.Size()<<endl;
	cout<<"Depth is :"<<genList.Depth()<<endl<<endl;
}
//≤‚ ‘À´≤„±Ì
void Test3()
{
	GeneraList genList("(a,b,(c,d))");
	genList.Print();
	cout<<"Size is :"<<genList.Size()<<endl;
	cout<<"Depth is :"<<genList.Depth()<<endl<<endl;
}
//≤‚ ‘∂‡≤„±Ì
void Test4()
{
	GeneraList genList("(a,b,(c,d),(e,(f),h))");
	genList.Print();
	cout<<"Size is :"<<genList.Size()<<endl;
	cout<<"Depth is :"<<genList.Depth()<<endl<<endl;
}
//≤‚ ‘∂‡≤„ø’±Ì
void Test5()
{
	GeneraList genList("(((),()),())");
	genList.Print();
	cout<<"Size is :"<<genList.Size()<<endl;
	cout<<"Depth is :"<<genList.Depth()<<endl<<endl;
}

int main()
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	return 0;
}
