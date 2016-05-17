#include<iostream>

using namespace std;

class BitSet
{
private:
	size_t *_array;
	size_t _size;
public:
	BitSet(size_t size)
	{
		_size = size/32+1;
		_array = new size_t[_size];
		memset(_array, 0, sizeof(size_t)*_size);
	}
	~BitSet()
	{
		delete[] _array;
	}
public:
	void Set(int index);//将位图某一位置设置为1
	void Reset(int index);//将位图某一位置设置为0
	bool Test(int index);//测试位图某一位置的值
	void Clear();//将位图所有的位全部清空
};

void BitSet::Set(int index)
{
	int pos = index%32;
	_array[index/32] |= (1<<32-pos);
}

void BitSet::Reset(int index)
{
	int pos = index%32;
	_array[index/32] &= ~(1<<32-pos);
}

bool BitSet::Test(int index)
{
	int pos = index%32;
	return _array[index/32] & (1<<32-pos);
}

void BitSet::Clear()
{
	memset(_array, 0, sizeof(size_t)*_size);
}