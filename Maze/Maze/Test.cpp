#include"Maze.hpp"

int main()
{
	char mazeArray[10][10] = 
		{
			'1','1','1','1','1','1','1','1','1','1',
			'0','0','1','1','1','1','1','1','1','1',
			'1','0','1','1','1','1','1','1','1','1',
			'1','0','1','1','1','1','1','1','1','1',
			'1','0','0','0','0','0','0','0','1','1',
			'1','1','1','0','1','1','1','0','1','1',
			'1','1','1','0','1','1','1','0','1','1',
			'1','1','0','0','1','0','0','0','1','1',
			'1','1','0','1','1','0','1','1','1','1',
			'1','1','1','1','1','0','1','1','1','1',
		};
	Maze maze(mazeArray, 1, 0);
	maze.ShowMaze();
}