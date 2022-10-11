#include "monitor.h"
#include "monitor_queue/monitor_queue.h"
#include "monitor_timer/monitor_timer.h"

#include <stdlib.h>
#include <stdio.h>

static pthread_t monitor_task_handle = -1;

static void *monitor_task(void *args);


static void 
*monitor_task(void *args)
{
    fd_set rfds;
    FD_ZERO(&rfds);

    int monitor_queue = monitor_queue_get();
    FD_SET(monitor_queue, &rfds);

    pthread_cleanup_push(monitor_cleanup_handler, NULL);

    while (1) {
        int result = select(monitor_queue + 1, &rfds, NULL, NULL, NULL);

        if (result == -1) {
            printf("Error on select.\r\n");
        } else if (result) {
            printf("Data is available on sensors task queue.\r\n");
            monitor_queue_pop();
        } else {
            printf("No data within given timeout.\r\n");
        }
    }

    pthread_cleanup_pop(NULL);

    return NULL;
}

int
monitor_init(void)
{
    int result = monitor_queue_init();
    if (result < 0) {
        return -1;
    }

    result = monitor_timer_init();
    if (result) {
        return -2;
    }

    result = pthread_create(&monitor_task_handle,
                            NULL,
                            monitor_task,
                            MONITOR_TASK_NAME);

    return result;
}

pthread_t 
monitor_task_handle_get(void)
{
    return monitor_task_handle;
}

void 
monitor_cleanup_handler(void *arg)
{
    monitor_queue_unlink();
}