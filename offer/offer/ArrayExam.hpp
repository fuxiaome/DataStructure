#pragma once
#include<iostream>
#include<assert.h>

using namespace std;

//!!一个数组中有两个数只出现了一次其余的数都出现了两次，找出这两个数
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
	cout<<"两个只出现一次的数分别为："<<x<<","<<y<<endl;
}
/*-----------------------END----------------------*/

//!!找出众数(超过一半的数)
//思路：众数出现的次数大于其他所有数出现次数之和
//每次扔掉两个不同的数，众数不变(1、扔掉一个众数，一个非众数。2、两个非众数)
void FindMaxCount(int *arr, int size)
{
	int x = 0;//X表示最终的众数
	int count = 0;
	for(int i=0; i<size;++i){
		if(count == 0){
			x = arr[i];//动态变化，表示当前进行判断是否相等的数
			count = 1;
		}
		if(x == arr[i]){
			++count;
		}else{
			--count;//扔掉两个不同的数
		}
	}
	cout<<"众数是："<<x<<endl;

}
/*-----------------------END----------------------*/


//!!查找循环移位数组中某个数的位置
//eg: 在{6,7,8,9,0,1,2,3,4,5}中查3的位置，应为7
int Search(int *arr, int size, int key)
{
	assert(arr!=NULL && size>=0);//每次写函数时，不可忽略对参数的检查

	int left = 0, right = size-1;//使用双闭区间表示数组的范围
	int mid = left + (right-left)/2;

	//!注意特殊情况  1,1,1,1,0,1,1,1,1,1
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

		if(arr[left] <= arr[mid]){//表示数组的左半部分为有序部分
			if (arr[left] <= key && key < arr[mid])//判断是否在左边有序部分中
				right = mid - 1;
			else
				left = mid +1;
		}else{//arr[mid]<=arr[right]右半部分为有序部分
			if (arr[mid] < key && key <= arr[right])
				left = mid + 1;
			else
				right = mid - 1;
		}
	}
	return -1;

}

/*-----------------------END----------------------*/


//!!求子数组的最大和（数组）
//输入一个整形数组，数组里有正数也有负数。
//数组中连续的一个或多个整数组成一个子数组，每个子数组都有一个和。
//求所有子数组的和的最大值。要求时间复杂度为 O(n)。
//eg:输入数组为1, -2, 3, 10, -4, 7, 2, -5，和最大子数组为3, 10, -4, 7, 2，
//输出为：18
int MaxSubSum(int *arr, int size)
{
	int curSum = 0, result = 0;
	//其实要处理全是负数的情况,直接给curSum赋初值为："curSum=a[0]"即可  
	//也可以不改，当全是负数的情况，直接返回0，也不见得不行。
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