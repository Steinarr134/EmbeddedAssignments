#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

extern pthread_mutex_t sharedVariableMutex;
extern int32_t gSharedVariable;


void *decrementTask(void *param)
{
    while (1)
    {
        /* Delay for 7 seconds. */
        sleep(7);
        /* Wait for the mutex to become available. */
        pthread_mutex_lock(&sharedVariableMutex);
        gSharedVariable--;
        printf("Decrement Task: shared var is %d\n", 
        gSharedVariable);
        /* Release the mutex. */
        pthread_mutex_unlock(&sharedVariableMutex);
    }
}
