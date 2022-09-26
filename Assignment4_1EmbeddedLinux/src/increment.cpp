#include "increment.h"
#include <stdio.h>
#include <unistd.h>


void *incrementTask(void *param)
{
    while (1)
    {
        /* Delay for 3 seconds. */
        sleep(3);
        /* Wait for the mutex to become available. */
        pthread_mutex_lock(&sharedVariableMutex);
        gSharedVariable++;
        printf("Increment Task: shared var is %d\n", 
        gSharedVariable);
        /* Release the mutex for other task to use. */
        pthread_mutex_unlock(&sharedVariableMutex);
    }
}