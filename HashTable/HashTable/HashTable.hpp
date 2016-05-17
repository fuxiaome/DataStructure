#include<iostream>
#include<assert.h>

using namespace std;

enum Status
{
	EMPTY,//��ʾδ���Ԫ�ص�״̬
	USED//��ʾ��λ���Ѿ������Ԫ��
};

template<class T>
class HashTable
{
private:
	int _size;//��ʾ��ǰ��ϣ����Ԫ�صĸ���
	int _capacity;//��ʾ��ϣ�������
	T* _array;//��ϣ���������Ԫ��
	Status* _status;//��ʾ��Ԫ������ÿ��λ�õ�״̬
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
	void Push(const T &data);//���ϣ���в�������
	void Remove(const T &data);//ɾ����ϣ���е�ָ��Ԫ��
	int Size();//���ص�ǰ��ϣ����Ԫ�صĸ���
	void Show();//��ʾ��ǰ��ϣ��Ĵ洢�����0��ʾ��λ��δ��Ԫ�أ�1��ʾ��λ�ô��Ԫ��
public:
	int _HashCode(const T &data);//����ָ��Ԫ�صĹ�ϣ��
	void _ExpandCapacity();//�Թ�ϣ���������
};

//����ָ��Ԫ�صĹ�ϣ��
template<class T>
int HashTable<T>::_HashCode(const T &data)
{
	return data % _capacity;
}

//�Թ�ϣ���������
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
//���ϣ���в�������,ʹ������̽�ⷨ�������ײ��ͻ
template<class T>
void HashTable<T>::Push(const T &data)
{
	assert(data != NULL);
	if (_size/_capacity > 0.75)//���������Ӵ���0.75ʱ�Թ�ϣ���������
	{
		_ExpandCapacity();
	}

	int hashcode = _HashCode(data);

	while(_status[hashcode] != EMPTY)//ʹ������̽�ⷨ�������ײ��ͻ
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

//��ָ����Ԫ�شӹ�ϣ����ɾ��
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

//���ص�ǰ��ϣ����Ԫ�صĸ���
template<class T>
int HashTable<T>::Size()
{
	return _size;
}

//��ʾ��ǰ��ϣ��Ĵ洢�����0��ʾ��λ��δ��Ԫ�أ�1��ʾ��λ�ô��Ԫ��
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