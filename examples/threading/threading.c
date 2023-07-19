#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "threading.h"

void* threadfunc(void* _ptr_)
{
    struct thread_data* param_ptr = (struct thread_data*)_ptr_;

    usleep(param_ptr->wait_to_obtain_ms);

    if (pthread_mutex_lock(param_ptr->mutex) != 0) {
        perror("pthread_mutex_lock");
        param_ptr->thread_complete_success = false;
        return param_ptr;
    }

    usleep(param_ptr->wait_to_release_ms);

    if (pthread_mutex_unlock(param_ptr->mutex) != 0) {
        perror("pthread_mutex_unlock");
        param_ptr->thread_complete_success = false;
        return param_ptr;
    }

    param_ptr->thread_complete_success = true;
    return param_ptr;
}

bool start_thread_obtaining_mutex(pthread_t* thread, pthread_mutex_t* mutex, int wait_to_obtain_ms, int wait_to_release_ms)
{
    struct thread_data* strt_ptr = (struct thread_data*)malloc(sizeof(struct thread_data));

    strt_ptr->mutex = mutex;
    strt_ptr->wait_to_obtain_ms = wait_to_obtain_ms;
    strt_ptr->wait_to_release_ms = wait_to_release_ms;
    strt_ptr->thread_complete_success = false;

    if (pthread_create(thread, NULL, threadfunc, (void*)strt_ptr) !=0) {
        perror("pthread_create");
        free(strt_ptr);
        return false;
    }

    return true;
}
