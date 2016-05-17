#include<iostream>
#include<assert.h>

using namespace std;

enum Status
{
	EMPTY,//表示未存放元素的状态
	USED//表示该位置已经存放了元素
};

template<class T>
class HashTable
{
private:
	int _size;//表示当前哈希表存放元素的个数
	int _capacity;//表示哈希表的容量
	T* _array;//哈希表存放数组的元素
	Status* _status;//标示存元素数组每个位置的状态
public:
	HashTable(int capacity)
		:_size(0)
		,_capacity(capacity)
	{
		_array = new T[capacity];
		_status = new Status[capacity];
		memset(_array, 0, sizeof(T)*capacity);
		memset(_status, 0, sizeof(Status)*capacity);
	}
	~HashTable()
	{
		delete[] _array;
		delete[] _status;
	}
public:
	void Push(const T &data);//向哈希表中插入数据
	void Remove(const T &data);//删除哈希表中的指定元素
	int Size();//返回当前哈希表存放元素的个数
	void Show();//显示当前哈希表的存储情况，0表示该位置未存元素，1表示该位置存放元素
public:
	int _HashCode(const T &data);//计算指定元素的哈希码
	void _ExpandCapacity();//对哈希表进行扩容
};

//计算指定元素的哈希码
template<class T>
int HashTable<T>::_HashCode(const T &data)
{
	return data % _capacity;
}

//对哈希表进行扩容
template<class T>
void HashTable<T>::_ExpandCapacity()
{
	HashTable<T> newTable(_capacity*2);

	for(int i=0; i<_capacity; ++i)
	{
		if(_status[i] == USED)
		{
			newTable.Push(_array[i]);
		}
	}
	this->~HashTable();
	swap(_array,newTable._array);
	swap(_status, newTable._status);
}
//向哈希表中插入数据,使用线性探测法来解决碰撞冲突
template<class T>
void HashTable<T>::Push(const T &data)
{
	assert(data != NULL);
	if (_size/_capacity > 0.75)//当荷载因子大于0.75时对哈希表进行扩容
	{
		_ExpandCapacity();
	}

	int hashcode = _HashCode(data);

	while(_status[hashcode] != EMPTY)//使用线性探测法来解决碰撞冲突
	{
		hashcode++;
		if (hashcode == _capacity)
		{
			hashcode = 0;
		}
	}
	_array[hashcode] = data;
	_status[hashcode] = USED;
	++_size;
}

//把指定的元素从哈希表中删除
template<class T>
void HashTable<T>::Remove(const T &data)
{
	assert(data != NULL);
	int hashcode = _HashCode(data);

	while(_status[hashcode] != EMPTY && _array[hashcode] != data)
	{
		hashcode++;
		if (hashcode == _capacity)
		{
			hashcode = 0;
		}
	}
	if (_array[hashcode] == data)
	{
		_array[hashcode] = T();
		_status[hashcode] = EMPTY;
		--_size;
	}
}

//返回当前哈希表存放元素的个数
template<class T>
int HashTable<T>::Size()
{
	return _size;
}

//显示当前哈希表的存储情况，0表示该位置未存元素，1表示该位置存放元素
template<class T>
void HashTable<T>::Show()
{
	int count = 1;
	for(int i=0; i<_capacity; ++i)
	{
		if(count++%4 == 0)
		{
			cout<<_array[i]<<"-->"<<_status[i]<<endl;
		}else{
			cout<<_array[i]<<"-->"<<_status[i]<<"   ";
		}
	}
	cout<<endl;
}