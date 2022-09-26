#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

extern pthread_mutex_t sharedVariableMutex;
extern int32_t gSharedVariable;


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