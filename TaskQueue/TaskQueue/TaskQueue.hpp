#include<iostream>
#include<string>

using namespace std;

//��ʾ�����״̬
enum TaskStatus
{
	WAIT,//�����ھ��������еȴ�ִ�е�״̬
	RUN,//����ִ��״̬
	DONE//����ִ�����
};

//��ʾ����ִ�е����ȼ�
enum TaskPriority
{
	HIGH,//��������ִ�е�������е����ȼ�
	LOW//���ڴ�ִ�е�����������ȼ�
};

//����������Ϣ�Ľṹ��
struct Task
{
	string Name;//���������
	int NeedTime;//����ִ�������ʱ��
	int WaitTime;//����ȴ���ʱ��
	TaskPriority Priority;//��������ȼ���Ĭ�ϵ����ȼ�����2���ڸ����ȼ�����
	TaskStatus Status;//����ǰ����״̬
	
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
	Queue<Task> _highQue;//��ʾ���Ƚ��д����������У����ɴ����ٶȿ�Ĵ�����Աִ��
	Queue<Task> _lowQue;//��ʾ��ִ�е�������У�ֻ�е����ȴ�����������Ϊ��ʱ�ٴ����ִ�е��������
public:
	void PushTask(Task task);
	void StartExecute();
private:
	const Task& UpdateProiority();//���µ�ǰ��ִ�ж�������������ȼ������ȴ�ʱ�����30������������ȼ�
}

void TaskQueue::PushTask(const Task& task)
{
	assert(NULL != task);//��֤����Ϊ��

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
