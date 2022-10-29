#include <rtthread.h>

int recur_count;
FINSH_VAR_EXPORT(recur_count, finsh_type_int, Recur count)

void recur (int level)
	{
	if (level > 0)
	    {
	    recur_count++;
	    recur (level - 1);
	    }
	}

CS4000_FUNCTION_EXPORT(recur, recur, Call a function recursively)

void recur_thread(void *parameter)
	{
	int cnt = (int) parameter;

	recur(cnt);
	while(1)
		{
		rt_thread_mdelay(1000);
		}
	}

CS4000_FUNCTION_EXPORT(recur_thread, recur_thread, Start a thread to call function recursively)
