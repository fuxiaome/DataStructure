#include<iostream>
#include<vector>

using namespace std;

template<class T>
class Tuple
{
public:
	int _row;
	int _col;
	T _value;
	Tuple(int row=0, int col=0, T value=T())
	{
		_row = row;
		_col = col;
		_value = value;
	}
};

template<class T>
class SparseMatrix
{
public:
	SparseMatrix(T *matrix, size_t row, size_t col, const T& invalid)
		:_matrixRow(row),
		 _matrixCol(col)
	{
		for(size_t i=0; i<row; ++i)
		{
			for(size_t j=0; j<col; ++j)
			{
				if(matrix[i*col+j] != invalid)
				{
					Tuple<T> temp;
					temp._row = i;
					temp._col = j;
					temp._value = matrix[i*col+j];
					_array.push_back(temp);
				}
			}
		}
	}
	~SparseMatrix()
	{
		_array.clear();
		_matrixRow = 0;
		_matrixCol = 0;
	}
private:
	vector<Tuple<T> > _array;//�����洢ѹ������
	size_t _matrixRow;//���������
	size_t _matrixCol;//���������
public:
	void Transpose();//ʹ�ñ����ķ�ʽ����ת�ã�ʱ�临�Ӷ� O(cols * elements)
	void Transpose_op();//ʹ�ÿ���ת�õķ�������ת�ã�ʱ�临�Ӷ�O(n)
	void Print();//��ӡ����
};

//��ͨ��ʽ��ת��
template<class T>
void SparseMatrix<T>::Transpose()
{
	int index = 0;//����������ǰѹ�����������ָ��
	vector<Tuple<T> > transArr;//ת�ú��ѹ������

	for(size_t i=0; i<_matrixCol; ++i)
	{
		for(size_t j=0; j<_array.size(); ++j)
		{
			//��Ϊת�ú���Ԫ������л��������������б����ķ�ʽ���ν���ǰѹ�������Ԫ�ط���ת�ú��ѹ��������
			if (_array[j]._col == i)
			{
				transArr.push_back(_array[j]);
			}
		}
	}
	//��ת�ú���Ԫ���е�����ҲҪ����
	for (size_t i=0; i<transArr.size(); ++i)
	{
		swap(transArr[i]._row,transArr[i]._col);
	}

	swap(transArr, _array);//����ǰѹ��������ת��ѹ�����󻥻�
	swap(_matrixRow,_matrixCol);//���������Ҳ���л���
}

//����ת��
template<class T>
void SparseMatrix<T>::Transpose_op()
{
	int *rowCounts = new int[_matrixCol];//ͳ��ת�ú����ÿһ�е����ݸ���
	int *rowStart = new int[_matrixCol];//ͳ��ת�ƺ�ľ���ÿ����ѹ�������д洢�Ŀ�ʼλ��
	vector<Tuple<T> > transArr(_array.size());
	//��������������г�ʼ��
	memset(rowCounts, 0, sizeof(int)*_matrixCol);
	memset(rowStart, 0, sizeof(int)*_matrixCol);

	//ͳ��ת�ú����ÿһ�е����ݸ���
	for (size_t i=0; i<_array.size(); ++i)
	{
		rowCounts[_array[i]._col]++;
	}
	
	//ͳ��ת�ú�ľ���ÿ����ѹ������洢�Ŀ�ʼλ��
	for (size_t i=1; i<_matrixCol; ++i)
	{
		rowStart[i] = rowStart[i-1] + rowCounts[i-1];
	}

	//����rowStart��ָ�����ν���ǰѹ�������Ԫ�ط���ת�þ���
	for (size_t i=0; i<_array.size(); ++i)
	{	
		swap(_array[i]._row,_array[i]._col);
		transArr[rowStart[_array[i]._row]] = _array[i];
		rowStart[_array[i]._row]++;
	}
	swap(transArr, _array);
	swap(_matrixRow,_matrixCol);
}

template<class T>
void SparseMatrix<T>::Print()
{
	int index = 0;
	for(size_t i=0; i<_matrixRow; ++i)
	{
		for(size_t j=0; j<_matrixCol; ++j)
		{
			//�������Ǽ��ж�����index<_array.size()����ɴ�ӡ�����һ����ЧԪ�غ��ٴν���ѭ�������ж�ʱ����±�Խ��
			if (index<_array.size() && _array[index]._row == i && _array[index]._col == j)
			{ 
				cout<<_array[index]._value<<" ";
				++index;
			}else{
				cout<<0<<" ";
			}

		}
		cout<<endl;
	}
	cout<<endl;
}
