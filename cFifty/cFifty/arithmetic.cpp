#include"arithmetic.h"

void reverseWord(char const *start,char const *end)
{
	char * _sta = start;
	char * _end = end;
	int len = end - start;
	char ch = '\0';

	for(int i=0;i<len/2;++i)
	{
		ch = *(start++);
		*start = *(end--);
		*end = ch;
	}
	return;
}	