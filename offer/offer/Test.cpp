#include<iostream>
#include<string.h>
#include"StringExam.hpp"
#include"ArrayExam.hpp"

using namespace std;

/*---------------------------字符串的测试---------------------------*/
//测试大数的加法
void TestBinaryAdd()
{
	char num1[100] = {0};
	char num2[100] = {0};
	cin>>num1;
	cin>>num2;
	BigDataAdd(num1, num2);
}
//测试删除a,复制b
void TestDeleteA()
{
	char str[100] = {0};
	cin>>str;
	DeleteACopyB(str);
}

//测试复制星号到开头
void TestFrontStar()
{
	char str[100] = {0};
	cin>>str;
	FrontStar(str);
}
void TestFrontStar1()
{
	char str[100] = {0};
	cin>>str;
	FrontStar1(str);
}

//测试字串变位词
void TestIsChangePos()
{
	char str[100] = "helloworld";
	char subStr[100];
	while(1){
		memset(subStr, 0, sizeof(subStr));
		cin>>subStr;
		if(IsChangePos(str, subStr)){
			cout<<subStr<<" 是 "<<str<<" 的变位词"<<endl;
		}else{
			cout<<subStr<<" 不是 "<<str<<" 的变位词"<<endl;
		}
	}	
}

//测试单词反转
void TestRverserWord()
{
	char str[100];
	while(1){
		memset(str, 0, sizeof(str));
		gets(str);
		ReverseWord(str);
		cout<<str<<endl;
	}
}
/*------------------------------END-------------------------------*/

/*---------------------------数组的测试---------------------------*/

//找出两个只出现一次的数
void TestFindDiff()
{
	int arr[] = {1,3,1,3,2,4,6,4,2,7,6,5,9,9,10,10,7,11};
	FindDiff(arr, sizeof(arr)/sizeof(arr[0]));
}

//找数组中的众数
void TestFindMaxCount()
{
	int arr[] = {9,11,4,11,22,45,11,11,34,11,11,11,22,11,34,11,11,11,56,56,56};
	FindMaxCount(arr, sizeof(arr)/sizeof(arr[0]));
}

//循环移位数组中查找
void TestSearch()
{
	int arr[] = {6,7,8,9,0,1,2,3,4,5};
	int size = sizeof(arr)/sizeof(arr[0]);
	for(int i=0; i<size; ++i){
		cout<<i<<"在数组中的位置是："<<Search(arr, size, i)<<endl;
	}
}

//最大子数组和
void TestMaxSubSum()
{
	int arr[] = {20, -2, 3, 10, -4, 7, 2, -5};
	//int arr[] = {-1, 2, 3, -8, 5, 6, 7, 8, 9};
	int result = 0;
	result = MaxSubSum(arr, sizeof(arr)/sizeof(arr[0]));
	cout<<"最大子数组和为:"<<result<<endl;
}
/*------------------------------END-------------------------------*/

int main()
{
	//TestBinaryAdd();
	//TestDeleteA();
	//TestFrontStar1();
	//TestIsChangePos();
	//TestRverserWord();

	//TestFindDiff();
	//TestFindMaxCount();
	//TestSearch();
	TestMaxSubSum();
	return 0;
}