#pragma once
#include<iostream>
#include<string.h>

using namespace std;

//!!�����ӷ�����
void BigDataAdd(char *_num1, char *_num2)
{
	const int M = 100;
	int num1[M] = {0};
	int num2[M] = {0};
	int len1 = strlen(_num1);
	int len2 = strlen(_num2);
	for(int i=len1-1,j=0; i>=0; --i){
		num1[j++] = _num1[i]-'0';//������±������ֵ�λ
	}
	for(int i=len2-1,j=0; i>=0; --i){
		num2[j++] = _num2[i]-'0';
	}
	for(int i=0; i<M; ++i){
		num1[i] += num2[i];//������������num1������
		if(num1[i] >= 10){
			num1[i] -= 10;
			++num1[i+1];//ģ���λ
		}
	}
	int i = M-1;
	for(; i>=0 && num1[i]==0; --i);//�ҵ���һ����Ϊ0����
	for(; i>=0; --i){
		printf("%d",num1[i]);
	}
	printf("\n");
}

//!!ɾ�������е�a,���������е�b
void DeleteACopyB(char *str)
{
	 const int M = 200;
	int len = strlen(str);
	char finalStr[M] = {0};
	int k = 0;
	int countB = 0;//ͳ���ַ�����b�ĸ���
	//����ɾ���ַ����е�a��ͳ��b�ĸ���
	//������ɺ�k��ֵ����ɾ��a���ַ����ĳ���
	for(int i=0; i<len; ++i){
		if(str[i] == 'a'){
			continue;
		}else if(str[i] == 'b'){
			++countB;
		}	
		finalStr[k++] = str[i];
	}
	//cout<<"Test:"<<finalStr<<endl;//ɾ����a���ַ���
	//���Ÿ���ԭ�ַ������µ������У����b�ĸ���
	int newLen = k+countB;
	for(int i=newLen-1,j=k-1; j>=0 && k>=0; --i, --j){
		if(finalStr[j] == 'b'){
			finalStr[i] = finalStr[j];
			finalStr[--i] = 'b';//����һ��b
		}else{
			finalStr[i] = finalStr[j];
		}
	}
	cout<<"ɾ��a,����b����ַ���Ϊ��"<<endl;
	cout<<finalStr<<endl;
}

//!!����һ���������ǺŻ�ϵ��ַ����������е��Ǻŷ�����������ǰ��
//eg: input->12*3**45*  output->****1234
/********����һ*******/
//���Ÿ���,���ı�ԭ�����ֵ�˳��
void FrontStar(char *str)
{
	int len = strlen(str);
	int j = len-1;
	for(int i=len-1; i>=0; --i){
		if(str[i]>='0' && str[i]<='9'){//�����ַ�Ϊ����ʱ�Ž��и���
			str[j--] = str[i];
		}
	}
	//����ѭ��������j��ֵҲ��ʾ�Ǻŵĸ���
	for(;j>=0; --j){
		str[j] = '*';
	}
	cout<<str<<endl;
}
/********������*******/
//���ÿ�����partition��˼�룬�п��ܸı�����˳��
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

//!!�Ӵ���λ��
//����������a��b����b�Ƿ���a���ִ���λ�ʡ���������a=hello,b=lel,ello����true,����b=elo��false��
//������û������ڵ�˼�����ͳ�ƣ����ڵĳ��ȵ����ִ��ĳ���
bool IsChangePos(char *str, char *substr)
{
	int len = strlen(str);
	int subLen = strlen(substr);
	int letter[26] = {0};//�ٶ������ȫ��Сд��ĸ���ø�����ͳ��ÿ����ĸ���ֵĸ���
	int nonZero = 0;//�ؼ�����������ͳ���ַ���������
	//ͳ���ִ�b���ַ�������������ÿ����ĸ�ĳ��ִ���ͳ�Ƶ�letter������
	for(int i=0; i<subLen; ++i){
		if(++letter[substr[i]-'a'] == 1)
			++nonZero;
	}
	//ͳ��str��һ�����ڵ��ַ�
	for(int i=0,num=0; i<subLen; ++i){
		num = --letter[str[i]-'a'];//�Ը��ַ�����ƥ�䣬ƥ��󽫴�����һ
		if(num == 0){//��ʾ������ĸ�Ѿ���ȫƥ��
			--nonZero;
		}else if(num == -1){
			++nonZero;//û��ƥ�䵽��nonZero�����������ʱû��ƥ����ɵ��ַ�������
		}
	}
	if( nonZero == 0)return true;//��ʾ��ȫƥ��
	//�Դ��ڽ��л���������str[i-subLen],����str[i]
	//�´���str[i-subLen+1...i]���ɴ���str[i-subLen...i-1]
	for(int i=subLen; i<len; ++i){
		//����str[i-subLen]
		int c = str[i-subLen]-'a';
		int num = ++letter[c];
		if(num == 1){
			++nonZero;
		}else if( num == 0){
			--nonZero;
		}
		//����str[i]
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

//!!���ʷ�ת
//eg:��my name is ��Ϊ is name my
void Reverse(char *str, int i, int j)
{
	while( i < j){
		swap(str[i++], str[j--]);
	}
}
void ReverseWord(char *str)
{
	int start = 0;//һ�����ʵĿ�ʼλ��
	int end = 0;//һ�����ʵĽ���λ��
	int len = strlen(str);
	Reverse(str, 0, len-1);//�ȶ��ַ����������巴ת
	while(end <= len){
		while(str[end] != ' ' && str[end] !='\0'){
			end++;
		}
		Reverse(str, start, end-1);//��תÿһ������
		end++;
		start = end;
	}
}

/*-------------------END----------------------*/