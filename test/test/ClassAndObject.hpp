#include<iostream>
using namespace std;

class A
{
public :
	void print(int a)
	{
		cout<<"A:"<<a<<endl;
	}

	void print(int &a)
	{
		cout<<"use inference A:"<<a<<endl;
	}
};//再次注意，类定义完有个分号