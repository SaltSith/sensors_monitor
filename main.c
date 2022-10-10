#include <stdio.h>

#include "monitor/monitor.h"
#include "zmq_plugin/zmq_plugin_task.h"

int 
main(void)
{
    if (monitor_init()) {
        return -1;
    }

    if (zmq_plugin_task_init()) {
        return -1;
    }

    pthread_join(monitor_task_handle_get(), NULL);
    pthread_join(zmq_plugin_task_handle_get(), NULL);

    return 0;
}
