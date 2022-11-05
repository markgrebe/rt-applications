#include <rtthread.h>

/* Global Variables for Semaphores */
rt_sem_t sem1;
rt_sem_t sem2;
/* Global Variables for Threads */
rt_thread_t tid1;
rt_thread_t tid2;

void thread1(void *parameter)
    {
    /* Homework 6 - Fill in the body of thread 1 */

    }

void thread2(void *parameter)
    {
    /* Homework 6 - Fill in the body of thread 2 */

    }

int main(void)
{
    rt_kprintf("Hello, RT-Thread!\n");

    /* Create the Semphores */
    /* Homework 6 - Fill in the semaphore creation */

    /* Create and Start the Threads */
    /* Homework 6 - Fill in the thread creation and startup */

}

