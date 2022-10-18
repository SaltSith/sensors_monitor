#include "monitor_events.h"

#include "monitor_commander/monitor_commander.h"
#include "pb_helper/pb_helper.h"

#include <assert.h>
#include <stdio.h>


static int monitor_event_handler_check_cpu_temperature(void * args);


typedef int(*monitor_event_handler_type)(void * args);

static monitor_event_handler_type monitor_event_handlers[MONITOR_EVENT_LAST] = {
        monitor_event_handler_check_cpu_temperature,
};

static int
monitor_event_handler_check_cpu_temperature(void * args)
{
    const float cpu_temperature = 45;
    printf("CPU temp %fstC C\r\n", cpu_temperature);

    monitor_MonitorMsg *message = monitor_commander_temperature_async(cpu_temperature);
    assert(message != NULL);

    uint8_t raw_buff[sizeof(monitor_MonitorMsg)] = { 0 };

    int bytes_written = pb_helper_encode_msg((void *)message, raw_buff, sizeof(monitor_MonitorMsg));

    return 0;
}

int
monitor_event_handler(monitor_event_t event)
{
    return monitor_event_handlers[event.ev](event.args);
}