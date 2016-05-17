#include<iostream>
#include<string>

using namespace std;

//表示任务的状态
enum TaskStatus
{
	WAIT,//任务在就绪队列中等待执行的状态
	RUN,//处于执行状态
	DONE//任务执行完成
};

//表示任务执行的优先级
enum TaskPriority
{
	HIGH,//处于优先执行的任务队列的优先级
	LOW//处于次执行的任务队列优先级
};

//描述任务信息的结构体
struct Task
{
	string Name;//任务的名称
	int NeedTime;//任务执行所需的时间
	int WaitTime;//任务等待的时间
	TaskPriority Priority;//任务的优先级，默认当优先级大于2处于高优先级队列
	TaskStatus Status;//任务当前所处状态
	
	Task(string name, int needtime, int waittime, TaskPriority priority, TaskStatus status)
		:Name(name),
		 NeedTime(needtime),
		 WaitTime(waittime),
		 Priority(priority),
		 Status(status)
	{}
}

class TaskQueue
{
public:
	TaskQueue()
		:_highQue(NULL),
		 _lowQue(NULL)
	{}
	~TaskQue()
	{}
private:
	Queue<Task> _highQue;//表示优先进行处理的任务队列，交由处理速度快的处理人员执行
	Queue<Task> _lowQue;//表示次执行的任务队列，只有当优先处理的任务队列为空时再处理次执行的任务队列
public:
	void PushTask(Task task);
	void StartExecute();
private:
	const Task& UpdateProiority();//更新当前次执行队列中任务的优先级，若等待时间大于30分钟则提高优先级
}

void TaskQueue::PushTask(const Task& task)
{
	assert(NULL != task);//保证任务不为空

	if(task.Priority == HIGH)
	{
		_highQue.Push(task);
	}else{
		_lowQue.Push(task);
	}
}

void TaskQueue::StartExecute()
{
	while(_highQue.Size() != 0)
	{
		
	}
}
