#include <rtthread.h>

void demo (int param)
	{
	rt_thread_t id = rt_thread_self();
	rt_kprintf ("Hello from task %#x [%s]. Parameter is %d.\n", 
	            id, id->name, param);
	}

CS4000_FUNCTION_EXPORT(demo, demo, Say hello from a thread)
