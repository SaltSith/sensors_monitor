#include "monitor_events.h"

#include <stdio.h>


static int monitor_event_handler_check_cpu_temperature(void * args);


typedef int(*monitor_event_handler_type)(void * args);

static monitor_event_handler_type monitor_event_handlers[MONITOR_EVENT_LAST] = {
        monitor_event_handler_check_cpu_temperature,
};

static int
monitor_event_handler_check_cpu_temperature(void * args)
{
    printf("CPU temp 45st C\r\n");
    
    return 0;
}

int
monitor_event_handler(monitor_event_t event)
{
    return monitor_event_handlers[event.ev](event.args);
}