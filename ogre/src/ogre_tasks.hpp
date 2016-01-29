enum TaskResult
{
	TR_TASK,
	TR_FRAME,
	TR_APP
};

struct Task : private Uncopyable
{
	virtual TaskResult task(void) = 0;

	virtual ~Task(void)
	{
	}
};

class TaskQueue : private Uncopyable
{
public:
	TaskQueue(void);
	~TaskQueue(void);
	void enqueue(Task* task);
#ifdef USE_TIME
	TaskResult run(unsigned& work);
#else
	TaskResult run(void);
#endif

private:
	Mutex m;
	Semaphore sem;
	typedef std::deque<Task*> Tasks;
	Tasks tasks;
};

extern TaskQueue* ogre_tasks;
