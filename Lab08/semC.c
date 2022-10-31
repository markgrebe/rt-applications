#include <rtthread.h>

void semC (rt_sem_t semId)
    {
    if (rt_sem_take (semId, RT_WAITING_FOREVER) != RT_EOK)
        {
        rt_kprintf ("semTake failed\n");
        return;
        }
    rt_thread_suspend (0);
    rt_sem_release (semId);
    }

CS4000_FUNCTION_EXPORT(semC, semC, Task to take a semaphore)
