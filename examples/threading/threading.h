#ifndef THREADING_H
#define THREADING_H

#include <stdbool.h>
#include <pthread.h>

struct thread_data {
    // TODO: Add other values your thread will need to manage into this structure
    // For example:
    pthread_mutex_t* mutex;
    int wait_to_obtain_ms;
    int wait_to_release_ms;
    bool thread_complete_success;
};

bool start_thread_obtaining_mutex(pthread_t* thread, pthread_mutex_t* mutex, int wait_to_obtain_ms, int wait_to_release_ms);

#endif 
