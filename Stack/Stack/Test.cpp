#include <iostream>
#include <stack>
#include <cstring>
using namespace std;


//������ջ�����жϳ�ջ�����Ƿ�Ϸ���stkIn��ʾ��ջ���У�stkOut��ʾ��ջ����
bool JudgeIsLegal(char *stkIn, char *stkOut)
{
	stack<char> midStk;//�жϹ����н������м丨��ջ

	if(strlen(stkIn) != strlen(stkOut)){//����ջ���ջ��Ԫ�ظ�����ͬ�Ļ���ֱ�ӷ���false
		return false;
	}

	midStk.push(*stkIn++);//��ջ���еĵ�һ��Ԫ��ջ

	while(*stkOut != '\0'){//�����ջ����û��ƥ����

		if(midStk.empty() && *stkIn!='\0')//������ջ�ѿ�˵��Ŀǰ��ջ����ջ������ƥ��ģ������ջ���в�Ϊ�գ�������ջ  
			midStk.push(*stkIn++);

		//�������ջ��ջ��Ԫ�غͳ�ջ���е�һ��Ԫ�ز�һ�£���ô�ͽ���ջ���м�����ջ  
		while(*stkOut != midStk.top() && *stkIn != '\0'){
			midStk.push(*stkIn++);
		}

		//���ջ��Ԫ�غͳ�ջ���е�һ��Ԫ��һ�£���ô�ͽ�ջ��Ԫ�س�ջ������ƥ���ջ������һ��Ԫ��  
		if(*stkOut == midStk.top()){
			stkOut++;
			midStk.pop();
			continue;
		}
		//�����ջ������Ϊ�գ�����ջ��Ԫ�غͳ�ջ���е�һ��Ԫ���Ӳ�һ�£���˵����2��������ƥ��ġ�  
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
		cout<<"�ó�ջ���кϷ���"<<endl;
	}else{
		cout<<"�ó�ջ���зǷ���"<<endl;
	}

	return 0;
}


