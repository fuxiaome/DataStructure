#include"ClassAndObject.hpp"

void Test1()
{
	A aa;
	int a = 10;
	//aa.print(a);
	//aa.print(&a);
}

char* fun()
{
	char str[2222] = "lalala";
	return str;
}

int main()
{
	char *str;
	str = fun();
	cout<<str<<endl;
	return 0;
}