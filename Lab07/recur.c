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
