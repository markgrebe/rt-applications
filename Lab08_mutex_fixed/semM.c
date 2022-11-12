#include <rtthread.h>

void semM (rt_mutex_t semId)
	{
	rt_err_t status;

	if (rt_mutex_take (semId, RT_WAITING_FOREVER) != RT_EOK)
		{
		rt_kprintf ("semTake failed\n");
		return;
		}
	
	// Suspend ourselves. RT-Thread is weird here, you have to call
	// the scheduler after you suspend yourself, not normal.
	rt_thread_suspend (rt_thread_self());
	rt_schedule();

	rt_mutex_release (semId);
	}

CS4000_FUNCTION_EXPORT(semM, semM, Task to take a semaphore)
