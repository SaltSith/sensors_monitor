#pragma once

#include <pthread.h>

#define MONITOR_TASK_NAME "monitor_task"

int monitor_init(void);
pthread_t monitor_task_handle_get(void);
void monitor_cleanup_handler(void *arg);
