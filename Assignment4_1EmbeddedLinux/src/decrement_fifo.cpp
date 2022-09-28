#include "decrement.h"
#include "fifo3.h"
#include <stdio.h>
#include <unistd.h>

extern Fifo fifo;

void *decrementTask(void *param)
{
    while (1)
    {
        /* Delay for 3 seconds. */
        sleep(3);
        /* Wait for the mutex to become available. */
        pthread_mutex_lock(&sharedVariableMutex);
        if (!fifo.is_empty())
        {
            int i = fifo.get();
            printf("Decrement Task: I just got %d from fifo\n",  i);
        }
        else{
            printf("Decrement Task: couldn't get, it's empty!");
        }
        /* Release the mutex for other task to use. */
        pthread_mutex_unlock(&sharedVariableMutex);
    }
}