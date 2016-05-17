#pragma once
#include<iostream>
#include<string.h>

using namespace std;

//!!大数加法运算
void BigDataAdd(char *_num1, char *_num2)
{
	const int M = 100;
	int num1[M] = {0};
	int num2[M] = {0};
	int len1 = strlen(_num1);
	int len2 = strlen(_num2);
	for(int i=len1-1,j=0; i>=0; --i){
		num1[j++] = _num1[i]-'0';//数组低下标存放数字地位
	}
	for(int i=len2-1,j=0; i>=0; --i){
		num2[j++] = _num2[i]-'0';
	}
	for(int i=0; i<M; ++i){
		num1[i] += num2[i];//将计算结果存入num1数组中
		if(num1[i] >= 10){
			num1[i] -= 10;
			++num1[i+1];//模拟进位
		}
	}
	int i = M-1;
	for(; i>=0 && num1[i]==0; --i);//找到第一个不为0的数
	for(; i>=0; --i){
		printf("%d",num1[i]);
	}
	printf("\n");
}

//!!删除数组中的a,复制数组中的b
void DeleteACopyB(char *str)
{
	 const int M = 200;
	int len = strlen(str);
	char finalStr[M] = {0};
	int k = 0;
	int countB = 0;//统计字符串中b的个数
	//遍历删除字符串中的a，统计b的个数
	//遍历完成后k的值等于删除a后字符串的长度
	for(int i=0; i<len; ++i){
		if(str[i] == 'a'){
			continue;
		}else if(str[i] == 'b'){
			++countB;
		}	
		finalStr[k++] = str[i];
	}
	//cout<<"Test:"<<finalStr<<endl;//删除了a的字符串
	//倒着复制原字符串到新的数组中，完成b的复制
	int newLen = k+countB;
	for(int i=newLen-1,j=k-1; j>=0 && k>=0; --i, --j){
		if(finalStr[j] == 'b'){
			finalStr[i] = finalStr[j];
			finalStr[--i] = 'b';//复制一次b
		}else{
			finalStr[i] = finalStr[j];
		}
	}
	cout<<"删除a,复制b后的字符串为："<<endl;
	cout<<finalStr<<endl;
}

//!!给定一个数字与星号混合的字符串，将所有的星号放置在数组最前面
//eg: input->12*3**45*  output->****1234
/********方法一*******/
//倒着复制,不改变原先数字的顺序
void FrontStar(char *str)
{
	int len = strlen(str);
	int j = len-1;
	for(int i=len-1; i>=0; --i){
		if(str[i]>='0' && str[i]<='9'){//当该字符为数字时才进行复制
			str[j--] = str[i];
		}
	}
	//上面循环结束后，j的值也表示星号的个数
	for(;j>=0; --j){
		str[j] = '*';
	}
	cout<<str<<endl;
}
/********方法二*******/
//利用快排中partition的思想，有可能改变数字顺序
void  FrontStar1(char *str)
{
	int len = strlen(str);
	int i = -1,j = len;
	while(1){
		while(str[--j]!='*')if(j<=i)break;
		while(str[++i]=='*')if(i>=j)break;
		if(j > i){
			swap(str[i],str[j]);
		}else{
			break;
		}
	}
	cout<<str<<endl;
}
/*************************END****************************/

//!!子串变位词
//给定两个串a和b，问b是否是a的字串变位词。例如输入a=hello,b=lel,ello都是true,但是b=elo是false。
//整体采用滑动窗口的思想进行统计，窗口的长度等于字串的长度
bool IsChangePos(char *str, char *substr)
{
	int len = strlen(str);
	int subLen = strlen(substr);
	int letter[26] = {0};//假定输入的全是小写字母，用该数组统计每个字母出现的个数
	int nonZero = 0;//关键变量，用来统计字符的种类数
	//统计字串b的字符种类数，并将每个字母的出现次数统计到letter数组中
	for(int i=0; i<subLen; ++i){
		if(++letter[substr[i]-'a'] == 1)
			++nonZero;
	}
	//统计str第一个窗口的字符
	for(int i=0,num=0; i<subLen; ++i){
		num = --letter[str[i]-'a'];//对该字符进行匹配，匹配后将次数减一
		if(num == 0){//表示该种字母已经完全匹配
			--nonZero;
		}else if(num == -1){
			++nonZero;//没有匹配到，nonZero在这里可以暂时没有匹配完成的字符种类数
		}
	}
	if( nonZero == 0)return true;//表示完全匹配
	//对窗口进行滑动，丢弃str[i-subLen],加入str[i]
	//新窗口str[i-subLen+1...i]、旧窗口str[i-subLen...i-1]
	for(int i=subLen; i<len; ++i){
		//丢弃str[i-subLen]
		int c = str[i-subLen]-'a';
		int num = ++letter[c];
		if(num == 1){
			++nonZero;
		}else if( num == 0){
			--nonZero;
		}
		//加入str[i]
		c = str[i] - 'a';
		num = --letter[c];
		if( num == 0){
			--nonZero;
		}else if(num == -1){
			++nonZero;
		}
		if(nonZero == 0)return true;
	}

	return false;
}
/*-------------------END----------------------*/

//!!单词反转
//eg:将my name is 变为 is name my
void Reverse(char *str, int i, int j)
{
	while( i < j){
		swap(str[i++], str[j--]);
	}
}
void ReverseWord(char *str)
{
	int start = 0;//一个单词的开始位置
	int end = 0;//一个单词的结束位置
	int len = strlen(str);
	Reverse(str, 0, len-1);//先对字符串进行整体反转
	while(end <= len){
		while(str[end] != ' ' && str[end] !='\0'){
			end++;
		}
		Reverse(str, start, end-1);//反转每一个单词
		end++;
		start = end;
	}
}

/*-------------------END----------------------*/