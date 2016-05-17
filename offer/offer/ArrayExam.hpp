#pragma once
#include<iostream>
#include<assert.h>

using namespace std;

//!!һ����������������ֻ������һ��������������������Σ��ҳ���������
void FindDiff(int *arr, int size)
{
	int xor = 0;
	int mask = 1;
	int x=0,y=0;
	for(int i=0; i<size; ++i)
		xor ^= arr[i];
	for(;((mask & xor) == 0);mask<<=1);
	for(int i=0; i<size; ++i){
		if( arr[i] & mask){
			x ^= arr[i];
		}else{
			y ^= arr[i];
		}
	}
	cout<<"����ֻ����һ�ε����ֱ�Ϊ��"<<x<<","<<y<<endl;
}
/*-----------------------END----------------------*/

//!!�ҳ�����(����һ�����)
//˼·���������ֵĴ��������������������ִ���֮��
//ÿ���ӵ�������ͬ��������������(1���ӵ�һ��������һ����������2������������)
void FindMaxCount(int *arr, int size)
{
	int x = 0;//X��ʾ���յ�����
	int count = 0;
	for(int i=0; i<size;++i){
		if(count == 0){
			x = arr[i];//��̬�仯����ʾ��ǰ�����ж��Ƿ���ȵ���
			count = 1;
		}
		if(x == arr[i]){
			++count;
		}else{
			--count;//�ӵ�������ͬ����
		}
	}
	cout<<"�����ǣ�"<<x<<endl;

}
/*-----------------------END----------------------*/


//!!����ѭ����λ������ĳ������λ��
//eg: ��{6,7,8,9,0,1,2,3,4,5}�в�3��λ�ã�ӦΪ7
int Search(int *arr, int size, int key)
{
	assert(arr!=NULL && size>=0);//ÿ��д����ʱ�����ɺ��ԶԲ����ļ��

	int left = 0, right = size-1;//ʹ��˫�������ʾ����ķ�Χ
	int mid = left + (right-left)/2;

	//!ע���������  1,1,1,1,0,1,1,1,1,1
	if( arr[left] == arr[mid] && arr[mid] == arr[right])
	{
		for(int i=0; i<size; ++i)
		{
			if(arr[i] == key){
				return i;
			}

		}
		return -1;
	}

	while(left <= right)
	{
		mid = left + (right-left)/2;
		if(arr[mid] == key)
			return mid;

		if(arr[left] <= arr[mid]){//��ʾ�������벿��Ϊ���򲿷�
			if (arr[left] <= key && key < arr[mid])//�ж��Ƿ���������򲿷���
				right = mid - 1;
			else
				left = mid +1;
		}else{//arr[mid]<=arr[right]�Ұ벿��Ϊ���򲿷�
			if (arr[mid] < key && key <= arr[right])
				left = mid + 1;
			else
				right = mid - 1;
		}
	}
	return -1;

}

/*-----------------------END----------------------*/


//!!������������ͣ����飩
//����һ���������飬������������Ҳ�и�����
//������������һ�������������һ�������飬ÿ�������鶼��һ���͡�
//������������ĺ͵����ֵ��Ҫ��ʱ�临�Ӷ�Ϊ O(n)��
//eg:��������Ϊ1, -2, 3, 10, -4, 7, 2, -5�������������Ϊ3, 10, -4, 7, 2��
//���Ϊ��18
int MaxSubSum(int *arr, int size)
{
	int curSum = 0, result = 0;
	//��ʵҪ����ȫ�Ǹ��������,ֱ�Ӹ�curSum����ֵΪ��"curSum=a[0]"����  
	//Ҳ���Բ��ģ���ȫ�Ǹ����������ֱ�ӷ���0��Ҳ�����ò��С�
	for(int i=0; i<size; ++i)
	{
		curSum += arr[i];
		if(curSum > result)
			result = curSum;
		if(curSum < 0)
			curSum = 0;
	}
	return result;
}

/*-----------------------END----------------------*/