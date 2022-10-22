#include "postman.h"

#include <assert.h>

#include "monitor_queue/monitor_queue.h"

#include "pb_helper/pb_helper.h"

static monitor_MonitorMsg *in_msg = NULL;

int
postman_send_message(uint8_t *msg_buff, size_t msg_buff_size)
{
    assert(msg_buff != NULL);

    in_msg = malloc(sizeof(monitor_MonitorMsg));
    assert(in_msg != NULL);

    memset(in_msg, 0, sizeof(monitor_MonitorMsg));

    int decode_result = pb_helper_decode_msg(msg_buff, msg_buff_size, in_msg);
    assert(decode_result == 0);

    free(msg_buff);

    if (in_msg->which_msg == monitor_MonitorMsg_hello_async_tag) {
        free(in_msg);
        return 1;
    }

    // viewer_queue_push_event_process_in_message(in_msg);

    return 0;
}

size_t
postman_hello_message(uint8_t *proto_buff, const size_t buff_size)
{
    monitor_MonitorMsg *hello_msg = malloc(sizeof(monitor_MonitorMsg));
    assert(hello_msg != NULL);

    memset(hello_msg, 0, sizeof(monitor_MonitorMsg));

    hello_msg->which_msg = monitor_MonitorMsg_hello_async_tag;

    return pb_helper_encode_msg(hello_msg, proto_buff, sizeof(proto_buff));
}