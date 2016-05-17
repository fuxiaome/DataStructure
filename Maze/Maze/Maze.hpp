#include<iostream>
#include<stack>

using namespace std;

const int r=10;

struct Pos
{
	int X;
	int Y;
	Pos(int x,int y)
		:X(x),
		 Y(y)
	{}
	Pos()
		:X(0),Y(0)
	{}
};

class Maze
{
public:

	Maze(char (*maze)[10],int entryX,int entryY)
	{
		_maze = maze;
		_entry.X  = entryX;
		_entry.Y = entryY;
		_col = sizeof(_maze[0])/sizeof(_maze[0][0]);
		_row = _col;
	
	}

	~Maze()
	{}
private:
	char (*_maze)[10];
	stack<Pos> _track;
	Pos _entry;
	size_t _row;
	size_t _col;
	
public:
	bool FindExit();
	void ShowMaze();
};

bool Maze::FindExit()
{
	_trace.push(_entry);
	Pos curPos(_entry.X,_entry.Y);
	
	while(!_track.empty())
	{
		//оРобйтл╫
		Pos nextPos(curPos.X,curPos.Y);
		if(_maze[nextPos.X+1][curPos.Y] == 0)
		{
			
		}
	}
	return false;
}

void Maze::ShowMaze()
{
	for(size_t i=0; i<_row; ++i)
	{
		for(size_t j=0; j<_col; ++j)
		{
			cout<<_maze[i][j]<<" "; 
		}
		cout<<endl;
	}
}