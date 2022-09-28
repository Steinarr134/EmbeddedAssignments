#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include "fifo3.h"
#include "increment_fifo.h"
#include "decrement_fifo.h"

pthread_mutex_t sharedVariableMutex;
Fifo fifo;

pthread_t incrementTaskObj;
pthread_t decrementTaskObj;


int main(void)
{
    /* Create the mutex for accessing the shared variable using the
    * default attributes. */
    pthread_mutex_init(&sharedVariableMutex, NULL);
    /* Create the increment and decrement tasks using the default task
    * attributes. Do not pass in any parameters to the tasks. */
    pthread_create(&incrementTaskObj, NULL, incrementTask, NULL);
    pthread_create(&decrementTaskObj, NULL, decrementTask, NULL);
    /* Allow the tasks to run. */
    pthread_join(incrementTaskObj, NULL);
    pthread_join(decrementTaskObj, NULL);
return 0;
}