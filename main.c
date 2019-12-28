#include <stdlib.h>
#include <pthread.h>
#include "log.h"

#define ARRAY_SIZE(arr) (sizeof arr)/(sizeof arr[0])

typedef struct thread_data {
    size_t id;
} thread_data_t;

void* thread_fn(void* arg) {
    thread_data_t* data = arg;

    for (unsigned i = 0; i < 10; ++i) {
        log_debug("[Thread=%zu] Debugging a loop at %i", data->id, i);
    }
    return NULL;
}
int main()
{
    log_set(LOG_DEBUG);

	log_info("Hello there!");
	log_warning("This is a warning");
    log_error("An error ocurred...");

    pthread_t threads[8];
    thread_data_t datas[8];

    for (size_t i =0; i < ARRAY_SIZE(threads); ++i) {
        log_info("Initializing thread %zu", i);
        datas[i].id = i;
        pthread_create(&threads[i], NULL, thread_fn, &datas[i]);
    }
    for (size_t i =0; i < ARRAY_SIZE(threads); ++i) {
        log_info("Finalizing thread %zu", i);
        pthread_join(threads[i], NULL);
    }
	return 0;
}
