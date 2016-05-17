#include <iostream>
#include <stack>
#include <cstring>
using namespace std;


//给定入栈序列判断出栈序列是否合法，stkIn表示入栈序列，stkOut表示出栈序列
bool JudgeIsLegal(char *stkIn, char *stkOut)
{
	stack<char> midStk;//判断过程中借助的中间辅助栈

	if(strlen(stkIn) != strlen(stkOut)){//若入栈与出栈的元素个数不同的话，直接返回false
		return false;
	}

	midStk.push(*stkIn++);//入栈序列的第一个元入栈

	while(*stkOut != '\0'){//如果出栈序列没有匹配完

		if(midStk.empty() && *stkIn!='\0')//若辅助栈已空说明目前出栈和入栈序列是匹配的，如果入栈序列不为空，继续入栈  
			midStk.push(*stkIn++);

		//如果辅助栈的栈顶元素和出栈序列第一个元素不一致，那么就将入栈序列继续入栈  
		while(*stkOut != midStk.top() && *stkIn != '\0'){
			midStk.push(*stkIn++);
		}

		//如果栈顶元素和出栈序列第一个元素一致，那么就将栈顶元素出栈，并且匹配出栈序列下一个元素  
		if(*stkOut == midStk.top()){
			stkOut++;
			midStk.pop();
			continue;
		}
		//如果入栈序列已为空，但是栈顶元素和出栈序列第一个元素扔不一致，则说明这2个串不是匹配的。  
		if(*stkIn == '\0' && midStk.top() != *stkOut){
			return false;
		}
	}

	return true;
}

int main()
{
	char *str ="12345";  
	char *str2 = "31524";  

	if (JudgeIsLegal(str,str2))
	{
		cout<<"该出栈序列合法！"<<endl;
	}else{
		cout<<"该出栈序列非法！"<<endl;
	}

	return 0;
}


