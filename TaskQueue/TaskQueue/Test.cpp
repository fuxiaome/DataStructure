#include"TaskQueue.hpp"

int main()
{
	Queue<string> que;
	que.Push("000");
	que.Push("111");
	que.Push("222");
	que.Push("333");
	cout<<que.IndexOf(0)<<endl;
	cout<<que.IndexOf(1)<<endl;
	cout<<que.IndexOf(2)<<endl;
	return 0;
}	