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
	vector<Tuple<T> > _array;//用来存储压缩矩阵
	size_t _matrixRow;//矩阵的行数
	size_t _matrixCol;//矩阵的列数
public:
	void Transpose();//使用遍历的方式进行转置，时间复杂度 O(cols * elements)
	void Transpose_op();//使用快速转置的方法进行转置，时间复杂度O(n)
	void Print();//打印矩阵
};

//普通方式的转置
template<class T>
void SparseMatrix<T>::Transpose()
{
	int index = 0;//用来遍历当前压缩矩阵的索引指针
	vector<Tuple<T> > transArr;//转置后的压缩矩阵

	for(size_t i=0; i<_matrixCol; ++i)
	{
		for(size_t j=0; j<_array.size(); ++j)
		{
			//因为转置后三元组的行列互换，故依照以列遍历的方式依次将当前压缩矩阵的元素放入转置后的压缩矩阵中
			if (_array[j]._col == i)
			{
				transArr.push_back(_array[j]);
			}
		}
	}
	//！转置后将三元组中的行列也要互换
	for (size_t i=0; i<transArr.size(); ++i)
	{
		swap(transArr[i]._row,transArr[i]._col);
	}

	swap(transArr, _array);//将当前压缩矩阵与转置压缩矩阵互换
	swap(_matrixRow,_matrixCol);//矩阵的行列也进行互换
}

//快速转置
template<class T>
void SparseMatrix<T>::Transpose_op()
{
	int *rowCounts = new int[_matrixCol];//统计转置后矩阵每一行的数据个数
	int *rowStart = new int[_matrixCol];//统计转制后的矩阵每行在压缩矩阵中存储的开始位置
	vector<Tuple<T> > transArr(_array.size());
	//对这两个数组进行初始化
	memset(rowCounts, 0, sizeof(int)*_matrixCol);
	memset(rowStart, 0, sizeof(int)*_matrixCol);

	//统计转置后矩阵每一行的数据个数
	for (size_t i=0; i<_array.size(); ++i)
	{
		rowCounts[_array[i]._col]++;
	}
	
	//统计转置后的矩阵每行在压缩矩阵存储的开始位置
	for (size_t i=1; i<_matrixCol; ++i)
	{
		rowStart[i] = rowStart[i-1] + rowCounts[i-1];
	}

	//依照rowStart的指引依次将当前压缩矩阵的元素放入转置矩阵
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
			//错误，忘记加判断条件index<_array.size()，造成打印完最后一个有效元素后，再次进入循环进行判断时造成下标越界
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
