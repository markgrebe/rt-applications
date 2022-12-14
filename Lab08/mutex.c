#include <rtthread.h>

int v1;
int v2;
int count;

FINSH_VAR_EXPORT(v1, finsh_type_int, Variable 1)
FINSH_VAR_EXPORT(v2, finsh_type_int, Variable 2)
FINSH_VAR_EXPORT(count, finsh_type_int, Count)

void mutex1 (void)
	{
	while(1)
		{
		v1 = count;
		v2 = count;

		count++;
		}
	}

CS4000_FUNCTION_EXPORT(mutex1, mutex1, Task to increment count)

void mutex2 (void)
	{
	int same;

	while(1)
		{
		same = (v1 == v2);

		if (!same)
			rt_kprintf ("v1 = %d, v2 = %d\n", v1, v2);
		
		rt_thread_mdelay (100);
		}
	}

CS4000_FUNCTION_EXPORT(mutex2, mutex2, Task to check count)
