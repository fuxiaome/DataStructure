#include"SparseMatrix.hpp"

#define ROW 6
#define COL 5
int main()
{
	int matrix[ROW][COL] = 
	{
		{1, 0, 0 ,0 ,5},
		{0, 0, 2 ,0 ,0},
		{0, 0, 0 ,0 ,0},
		{1, 0, 1 ,0 ,5},
		{0, 0, 0 ,0 ,0},
		{0, 0, 0 ,3 ,0}
	};
	SparseMatrix<int> sm((int *)matrix, ROW, COL, 0);
	sm.Print();
	cout<<"after custom transpose:"<<endl;
	sm.Transpose();
	sm.Print();
	cout<<"after quick transpose:"<<endl;
	sm.Transpose_op();
	sm.Print();
	return 0;
}