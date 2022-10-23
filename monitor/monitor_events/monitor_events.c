#include "monitor_events.h"

#include "monitor_commander/monitor_commander.h"
#include "pb_helper/pb_helper.h"

#include "zmq_plugin/zmq_plugin_task.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

static uint8_t *send_buff;

static int monitor_event_handler_check_cpu_temperature(void * args);


typedef int(*monitor_event_handler_type)(void * args);

static monitor_event_handler_type monitor_event_handlers[MONITOR_EVENT_LAST] = {
        monitor_event_handler_check_cpu_temperature,
};

static int
monitor_event_handler_check_cpu_temperature(void * args)
{
    const float cpu_temperature = 45;
    const float gpu_temperature = 67.7;

    monitor_MonitorMsg *message = monitor_commander_temperature_async(cpu_temperature, gpu_temperature);
    assert(message != NULL);

    send_buff = malloc(sizeof(monitor_MonitorMsg));
    assert(send_buff != NULL);

    int bytes_written = pb_helper_encode_msg(message, send_buff, sizeof(monitor_MonitorMsg));

    if (bytes_written == -1) {
        free(send_buff);
    	return -1;
    }

    zmq_plugin_task_send_msg(send_buff, bytes_written);

    return 0;
}

int
monitor_event_handler(monitor_event_t event)
{
    return monitor_event_handlers[event.ev](event.args);
}