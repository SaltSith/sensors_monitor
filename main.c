#include <stdio.h>

#include "monitor/monitor.h"

int 
main(void)
{
    if (monitor_init()) {
        return -1;
    }

    pthread_join(monitor_task_handle_get(), NULL);

    return 0;
}
