#pragma once
#include<iostream>
#include<vector>

using namespace std;

//哈希桶中每条链上节点的类型
template<class K, class V>
struct Node
{
	K _key;
	V _value;
	Node *_next;//指向下一个节点

	Node(K key, V value)
		:_key(key)
		,_value(value)
	{}
};

//哈希桶的每条链的头部结构体
template<class K, class V>
struct HeadNode
{
	Node<K, V> *_next;
	int _size;//表示该头部上挂载节点的个数
};

//哈希表增容所依据的素数表
static int prime_array[] = {
	17,37,79,163,331,673,1361,2729,5471,10949,21911,43853,87719,175447,
	350899,701819,1403641,2807303,5614657,11229331,22458671,44917381,
	89834777,179669557,359339171,718678369,1437356741,2147483647
};

template<class K, class V>
class HashTableBucket
{
private:
	vector<HeadNode<K, V> *> _tables;
	int _capacity;
public:
	HashTableBucket(int size)
	{
		for(int i=0; i<28; ++i)
		{
			if(prime_array[i] >= size)//在素数表中找到第一个比size大的数，作为哈希桶的容量的建议值
			{
				size = prime_array[i];
				break;
			}
		}
		_tables.reserve(size);
		_capacity = size;
		for(int i=0; i<_capacity; ++i)
		{
			HeadNode<K, V> * head = new HeadNode<K, V>;
			head->_size = 0;//初始化每条链上挂载的节点数为0
			head->_next = NULL;
			_tables.push_back(head);
		}
	}
	HashTableBucket()
	{
		//int num = prime_array[0];  //待解决问题，为什么不可以这样赋值
		HashTableBucket(17);
	}
public:
	//向哈希桶中插入新的键值对
	int Add(const K & key, const V & value)
	{
		int hashcode = _HashCode(key);
		if((_tables[hashcode]->_size+1) >= _capacity)
		{
			_ExpandCapacity();
		}
		Node<K, V> * newNode = new Node<K, V>(key, value);
		Node<K, V> * cur = _tables[hashcode]->_next;
		while(cur)
		{
			if(cur->_key == newNode->_key)
			{
				//若哈希桶中已经存在指定的Key，则只更新Value
				if(cur->_value != newNode->_value)
				{
					cur->_value = newNode->_value;
					return 0;
				}else{
					return -1;
				}
			}
			cur = cur->_next;
		}
		newNode->_next = _tables[hashcode]->_next;//使用头插法插入新的数据项
		_tables[hashcode]->_next = newNode;
		++_tables[hashcode]->_size;//链上的数据个数加一
		return 1;
	}

	//用于删除指定Key对应的存储项
	void Remove(const K &key)
	{
		int hashcode = _HashCode(key);
		Node<K, V> *cur = _tables[hashcode]->_next;
		if(_tables[hashcode]->_size == 1 && cur->_key == key)
		{
			//如果对应的哈希链上只有一条数据，则直接进行删除
			_tables[hashcode]->_size--;
			_tables[hashcode]->_next = NULL;
			delete cur;
		}else{//利用循环定位删除位置，进行删除
			while(cur && cur->_next != NULL)
			{
				if(cur->_next->_key == key)
				{
					Node<K, V> *tmp = cur->_next;
					cur->_next = tmp->_next;
					delete tmp;
					_tables[hashcode]->_size--;
					break;
				}
				cur = cur->_next;
			}
		}
	}

	//用指定Key在哈希桶上查找所对应的Value
	const V& Find(const K& key)
	{
		int hashcode = _HashCode(key);
		Node<K, V> *cur = _tables[hashcode]->_next;
		while(cur)
		{
			if(cur->_key == key)
			{
				return cur->_value;
			}
			cur = cur->_next;
		}
		return V();
	}

	//用于输出当前哈希桶各项使用情况
	void Statistics()
	{
		int noEmpty = 0;//非空链的数目
		int maxLen = 0;//最长一条链的长度
		int total = 0;//节点的总数
		for(int i=0; i<_capacity; ++i)
		{
			if(_tables[i]->_size != 0)
			{
				++noEmpty;
				total += _tables[i]->_size;
				if(_tables[i]->_size > maxLen)
				{
					maxLen = _tables[i]->_size;
				}

			}
		}
		printf("------------------Hash Table Used Info---------------------\n");
		printf("   Empty Link Count: %d\t,  Not Empty Link Count:%d\n",_capacity-noEmpty,noEmpty);
		printf("   Link Max Length:%d\t,  Not Empty Link Average Length:%.2f\n",maxLen, (total+0.0)/noEmpty);
		printf("   Node total is:%d\t,  Table Capacity:%d\n",total,_capacity);
		printf("-----------------------------------------------------------\n");
	}

	//显示哈希桶中的数据
	void Show()
	{
		Node<K, V> *cur = NULL;
		for(int i=0; i<_capacity; ++i)
		{
			cur = _tables[i]->_next;
			cout<<i<<"--->";
			while(cur)
			{
				cout<<"["<<cur->_key<<","<<cur->_value<<"]->";
				cur = cur->_next;
			}
			cout<<"NULL"<<endl;
		}
	}
private:
	//对哈希桶进行扩容
	void _ExpandCapacity()
	{
		int nextIndex = 0;//新容量在素数表中对应的下标
		for(int i=0; i<28; ++i)
		{
			if(_capacity == prime_array[i])
			{
				nextIndex = i+1;//扩容的规则为：当前容量在素数表中对应项的下一个素数
				break;
			}
		}
		int oldCapacity = _capacity;//记录未增容前的容量
		_capacity = prime_array[nextIndex];
		vector<HeadNode<K,V> *> newTables;
		newTables.reserve(prime_array[nextIndex]);
		for(int i=0; i<newTables.capacity(); ++i)//初始化增容后的哈希桶
		{
			HeadNode<K, V> * head = new HeadNode<K, V>;
			head->_size = 0;//初始化每条链上挂载的节点数为0
			head->_next = NULL;
			newTables.push_back(head);
		}
		Node< K, V> *cur = NULL;
		int hashcode = 0;
		for(int i=0; i<oldCapacity && _tables[i]->_size!=0; ++i)
		{
			while (_tables[i]->_next)
			{
				cur = _tables[i]->_next;
				_tables[i]->_next = cur->_next;//先将节点从当前链中摘除
				hashcode = _HashCode(cur->_key);
				cur->_next = newTables[hashcode]->_next;//使用头插法插入新的数据项
				newTables[hashcode]->_next = cur;
				++newTables[hashcode]->_size;//链上的数据个数加一
			}
		}
		_tables.swap(newTables);
	}
	int _HashCode(const K &key)
	{
		return key%_capacity;
	}
};