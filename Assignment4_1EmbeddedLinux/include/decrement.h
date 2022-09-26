#include <pthread.h>
#include <stdint.h>

extern pthread_mutex_t sharedVariableMutex;
extern int32_t gSharedVariable;

void *decrementTask(void *param);