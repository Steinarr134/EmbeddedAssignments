#include "increment.h"
#include <stdio.h>
#include <unistd.h>
#include "fifo3.h"

extern Fifo fifo;

void *incrementTask(void *param)
{
    int i = 0;
    while (1)
    {
        /* Delay for 3 seconds. */
        sleep(3);
        /* Wait for the mutex to become available. */
        pthread_mutex_lock(&sharedVariableMutex);
        fifo.put(i++);
        printf("Increment Task: I just put %d into fifo\n", 
        i);
        /* Release the mutex for other task to use. */
        pthread_mutex_unlock(&sharedVariableMutex);
    }
}