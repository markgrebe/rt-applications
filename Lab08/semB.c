#include <rtthread.h>

void semB (rt_sem_t semId)
	{
	rt_thread_t id = rt_thread_self();

	while(1)
		{
		if (rt_sem_take (semId, RT_WAITING_FOREVER) != RT_EOK)
			{
			rt_kprintf ("semTake failed\n");
			return;
			}
		rt_kprintf ("%s task took semaphore\n", id->name);
		}
	}

CS4000_FUNCTION_EXPORT(semB, semB, Task to take a semaphore)
