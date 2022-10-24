#include <rtthread.h>

int count;
int count1;
int count2;
FINSH_VAR_EXPORT(count, finsh_type_int, Inc count)
FINSH_VAR_EXPORT(count1, finsh_type_int, Inc1 count)
FINSH_VAR_EXPORT(count2, finsh_type_int, Inc2 count)

void inc_thread(void *parameter)
	{
	while(1)
		{
		count++;
		rt_thread_mdelay(1000);
		}
	}
CS4000_FUNCTION_EXPORT(inc_thread, inc_thread, Periodic increment1)

void inc_thread1(void *parameter)
	{
	while(1)
		{
		count1++;
		}
	}
CS4000_FUNCTION_EXPORT(inc_thread1, inc_thread1, Periodic increment1)

void inc_thread2(void *parameter)
	{
	while(1)
		{
		count2++;
		}
	}
CS4000_FUNCTION_EXPORT(inc_thread2, inc_thread2, Periodic increment2)
