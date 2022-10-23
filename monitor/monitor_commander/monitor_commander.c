#include "monitor_commander.h"

#include "protos_src/util.pb.h"

#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/time.h>

static monitor_MonitorMsg *monitor_out_msg = NULL;

static void *monitor_commander_prepare_message(const util_MsgStatus msg_status, const uint32_t msg_tag);

static void
*monitor_commander_prepare_message(const util_MsgStatus msg_status, const uint32_t msg_tag)
{
    monitor_out_msg = malloc(sizeof(monitor_MonitorMsg));
    assert(monitor_out_msg != NULL);
    memset(monitor_out_msg, 0 , sizeof(monitor_MonitorMsg));

    monitor_out_msg->has_uid = true;
    monitor_out_msg->uid = rand() % UINT32_MAX;

    struct timeval tv;
    gettimeofday(&tv, NULL);
    monitor_out_msg->timestamp = tv.tv_sec;
    monitor_out_msg->has_timestamp = true;

    monitor_out_msg->msg_status = msg_status;
    monitor_out_msg->has_msg_status = true;

    monitor_out_msg->which_msg = msg_tag;

    return monitor_out_msg;
}

monitor_MonitorMsg
*monitor_commander_hello_async(void)
{
    monitor_MonitorMsg *message = monitor_commander_prepare_message(util_MsgStatus_STATUS_OK, monitor_MonitorMsg_hello_async_tag);
    assert(message != NULL);

    return message;
}

monitor_MonitorMsg
*monitor_commander_temperature_async(const float cpu_temperature, const float gpu_temperature)
{
    monitor_MonitorMsg *message = monitor_commander_prepare_message(util_MsgStatus_STATUS_OK, monitor_MonitorMsg_temperature_async_tag);
    assert(message != NULL);

    message->msg.temperature_async.temperatures_count = 2;

    message->msg.temperature_async.temperatures[0].has_element = true;
    message->msg.temperature_async.temperatures[0].element = monitor_Temperature_Element_CPU;

    message->msg.temperature_async.temperatures[0].has_temp = true;
    message->msg.temperature_async.temperatures[0].temp = cpu_temperature;

    message->msg.temperature_async.temperatures[1].has_element = true;
    message->msg.temperature_async.temperatures[1].element = monitor_Temperature_Element_GPU;

    message->msg.temperature_async.temperatures[1].has_temp = true;
    message->msg.temperature_async.temperatures[1].temp = gpu_temperature;

    return message;
}
