#include <rtthread.h>

#define THREAD_PRIORITY         25
#define THREAD_STACK_SIZE       8192
#define THREAD_TIMESLICE        5

// Log Thread Message Queue
rt_mq_t log_msgq;

static rt_thread_t log_tid = RT_NULL;
/* Entry Function for Log Thread*/
static void log_thread_entry(void *parameter)
{
    int status;
    char buffer[80];

    while (1)
    {
        status = rt_mq_recv(log_msgq, buffer, 80, RT_WAITING_FOREVER);
        if (status == RT_EOK)
            {
            rt_kprintf(buffer);
            }
    }
}

static rt_thread_t tid1 = RT_NULL;
/* Entry Function for Thread 1 */
static void thread1_entry(void *parameter)
{
    rt_uint32_t count = 0;
    char buffer[80];

    while (1)
    {
        sprintf(buffer, "%d\n", count ++);
        rt_mq_send(log_msgq, buffer, 80);
        rt_thread_mdelay(500);
    }
}

/* Thread Sample */
int main(void)
{
    // Create the message queue for input messages
    log_msgq = rt_mq_create("logq", 
                            80,
                            10, 
                            RT_IPC_FLAG_FIFO);

    /* Creat log thread, Name is log_thread，Entry is log_entry */
    log_tid = rt_thread_create("log_thread",
                            log_thread_entry, RT_NULL,
                            THREAD_STACK_SIZE,
                            THREAD_PRIORITY + 1, 1);

    /* Start this thread if you get the thread control block */
    if (log_tid != RT_NULL)
        rt_thread_startup(log_tid);

    /* Creat thread 1, Name is thread1，Entry is thread1_entry */
    tid1 = rt_thread_create("thread1",
                            thread1_entry, RT_NULL,
                            THREAD_STACK_SIZE,
                            THREAD_PRIORITY, 1);

    /* Start this thread if you get the thread control block */
    if (tid1 != RT_NULL)
        rt_thread_startup(tid1);

    return 0;
}

