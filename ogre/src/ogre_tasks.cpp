#include "ogre_int.hpp"

TaskQueue* ogre_tasks;

TaskQueue::TaskQueue(void)
	: sem(0, 1000)
{
}

TaskQueue::~TaskQueue(void)
{
}

void TaskQueue::enqueue(Task* task)
{
	{
		Guard g(m);
		tasks.push_back(task);
	}
	sem.release();
}

#ifdef USE_TIME
TaskResult TaskQueue::run(unsigned& work)
#else
TaskResult TaskQueue::run(void)
#endif
{
#ifdef USE_TIME
	work = 0;
#endif
	for (;;)
	{
		sem.acquire();
		Task* task;
		{
			Guard g(m);
			assert(!tasks.empty());
			task = tasks.front();
			tasks.pop_front();
		}
#ifdef USE_TIME
		DWORD last = GetTickCount();
#endif
		TaskResult r = task->task();
		delete task;
#ifdef USE_TIME
		work += GetTickCount() - last;
#endif
		if (r != TR_TASK)
			return r;
	}
}
