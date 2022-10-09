#include "monitor_queue.h"
#include "monitor_events.h"

#include <mqueue.h>
#include <stdlib.h>
#include <stdbool.h>

#define MONITOR_QUEUE_NAME "/monitor_queue"

static int monitor_queue = -1;

int 
monitor_queue_init(void)
{
    struct mq_attr attr;

    attr.mq_flags   = 0;
    attr.mq_maxmsg  = 10;
    attr.mq_msgsize = sizeof(monitor_event_t);
    attr.mq_curmsgs = 0;

    monitor_queue = mq_open(MONITOR_QUEUE_NAME,
                            O_CREAT | O_NONBLOCK | O_RDWR,
                            0777,
                            &attr);

    return monitor_queue;
}

void
monitor_queue_unlink(void)
{

    mq_unlink(MONITOR_QUEUE_NAME);
}

void 
monitor_queue_pop(void)
{
    int result;
    unsigned int msg_prio;

    monitor_event_t event;
    int msg_len = sizeof(monitor_event_t);

    result = mq_receive(monitor_queue,
                        (char *)&event,
                        msg_len,
                        &msg_prio);

    if (result > 0) {
        monitor_event_handler(event);
    }
}

int
monitor_queue_get(void)
{
    return monitor_queue;
}

bool
monitor_queue_push_event_check_cpu_temperature(void)
{
    monitor_event_t event = {.ev = MONITOR_EVENT_CHECK_CPU_TEMPERATUE, .args = NULL};

    int result = mq_send(monitor_queue,
                         (char *)&event,
                         sizeof(monitor_event_t),
                         0);

    return result == 0 ? true : false;
}
