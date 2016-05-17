#pragma once
#include<iostream>
#include<vector>

using namespace std;

//��ϣͰ��ÿ�����Ͻڵ������
template<class K, class V>
struct Node
{
	K _key;
	V _value;
	Node *_next;//ָ����һ���ڵ�

	Node(K key, V value)
		:_key(key)
		,_value(value)
	{}
};

//��ϣͰ��ÿ������ͷ���ṹ��
template<class K, class V>
struct HeadNode
{
	Node<K, V> *_next;
	int _size;//��ʾ��ͷ���Ϲ��ؽڵ�ĸ���
};

//��ϣ�����������ݵ�������
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
			if(prime_array[i] >= size)//�����������ҵ���һ����size���������Ϊ��ϣͰ�������Ľ���ֵ
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
			head->_size = 0;//��ʼ��ÿ�����Ϲ��صĽڵ���Ϊ0
			head->_next = NULL;
			_tables.push_back(head);
		}
	}
	HashTableBucket()
	{
		//int num = prime_array[0];  //��������⣬Ϊʲô������������ֵ
		HashTableBucket(17);
	}
public:
	//���ϣͰ�в����µļ�ֵ��
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
				//����ϣͰ���Ѿ�����ָ����Key����ֻ����Value
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
		newNode->_next = _tables[hashcode]->_next;//ʹ��ͷ�巨�����µ�������
		_tables[hashcode]->_next = newNode;
		++_tables[hashcode]->_size;//���ϵ����ݸ�����һ
		return 1;
	}

	//����ɾ��ָ��Key��Ӧ�Ĵ洢��
	void Remove(const K &key)
	{
		int hashcode = _HashCode(key);
		Node<K, V> *cur = _tables[hashcode]->_next;
		if(_tables[hashcode]->_size == 1 && cur->_key == key)
		{
			//�����Ӧ�Ĺ�ϣ����ֻ��һ�����ݣ���ֱ�ӽ���ɾ��
			_tables[hashcode]->_size--;
			_tables[hashcode]->_next = NULL;
			delete cur;
		}else{//����ѭ����λɾ��λ�ã�����ɾ��
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

	//��ָ��Key�ڹ�ϣͰ�ϲ�������Ӧ��Value
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

	//���������ǰ��ϣͰ����ʹ�����
	void Statistics()
	{
		int noEmpty = 0;//�ǿ�������Ŀ
		int maxLen = 0;//�һ�����ĳ���
		int total = 0;//�ڵ������
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

	//��ʾ��ϣͰ�е�����
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
	//�Թ�ϣͰ��������
	void _ExpandCapacity()
	{
		int nextIndex = 0;//���������������ж�Ӧ���±�
		for(int i=0; i<28; ++i)
		{
			if(_capacity == prime_array[i])
			{
				nextIndex = i+1;//���ݵĹ���Ϊ����ǰ�������������ж�Ӧ�����һ������
				break;
			}
		}
		int oldCapacity = _capacity;//��¼δ����ǰ������
		_capacity = prime_array[nextIndex];
		vector<HeadNode<K,V> *> newTables;
		newTables.reserve(prime_array[nextIndex]);
		for(int i=0; i<newTables.capacity(); ++i)//��ʼ�����ݺ�Ĺ�ϣͰ
		{
			HeadNode<K, V> * head = new HeadNode<K, V>;
			head->_size = 0;//��ʼ��ÿ�����Ϲ��صĽڵ���Ϊ0
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
				_tables[i]->_next = cur->_next;//�Ƚ��ڵ�ӵ�ǰ����ժ��
				hashcode = _HashCode(cur->_key);
				cur->_next = newTables[hashcode]->_next;//ʹ��ͷ�巨�����µ�������
				newTables[hashcode]->_next = cur;
				++newTables[hashcode]->_size;//���ϵ����ݸ�����һ
			}
		}
		_tables.swap(newTables);
	}
	int _HashCode(const K &key)
	{
		return key%_capacity;
	}
};