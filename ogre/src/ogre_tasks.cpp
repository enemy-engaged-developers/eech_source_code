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
TaskResult TaskQueue::run(unsigned& wait)
#else
TaskResult TaskQueue::run(void)
#endif
{
#ifdef USE_TIME
	wait = 0;
#endif
	for (;;)
	{
#ifdef USE_TIME
		DWORD last = GetTickCount();
#endif
		sem.acquire();
		Task* task;
		{
			Guard g(m);
			assert(!tasks.empty());
			task = tasks.front();
			tasks.pop_front();
		}
#ifdef USE_TIME
		wait += GetTickCount() - last;
#endif
		TaskResult r = task->task();
		delete task;
		if (r != TR_TASK)
			return r;
	}
}
