#include <rtthread.h>

int v1;
int v2;
int count;
rt_mutex_t m1;

FINSH_VAR_EXPORT(v1, finsh_type_int, Variable 1)
FINSH_VAR_EXPORT(v2, finsh_type_int, Variable 2)
FINSH_VAR_EXPORT(count, finsh_type_int, Count)

void read_v1_v2()
	{
	rt_mutex_take(m1, RT_WAITING_FOREVER);
	v1 = count;
	v2 = count;
	rt_mutex_release(m1);
	}

int compare_v1_v2()
	{
	int same;
	rt_mutex_take(m1, RT_WAITING_FOREVER);
	same = (v1 == v2);
	rt_mutex_release(m1);
	return(same);
	}

void mutex1 (void)
	{
	m1 = rt_mutex_create("mutex1",RT_IPC_FLAG_PRIO);
	while(1)
		{
		read_v1_v2();

		count++;
		}
	}

CS4000_FUNCTION_EXPORT(mutex1, mutex1, Task to increment count)

void mutex2 (void)
	{
	int same;

	while(1)
		{
		same = compare_v1_v2();

		if (!same)
			rt_kprintf ("v1 = %d, v2 = %d\n", v1, v2);
		
		rt_thread_mdelay (100);
		}
	}

CS4000_FUNCTION_EXPORT(mutex2, mutex2, Task to check count)
