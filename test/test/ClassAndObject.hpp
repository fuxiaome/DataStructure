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
};//�ٴ�ע�⣬�ඨ�����и��ֺ�