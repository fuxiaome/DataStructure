// cFifty.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "arithmetic.h"


int _tmain(int argc, _TCHAR* argv[])
{
	char str[10] = {"123456789"};
	printf("%s\n",str);
	reverseWord(str,str+5);
	printf("%s\n",str);
	return 0;
}

