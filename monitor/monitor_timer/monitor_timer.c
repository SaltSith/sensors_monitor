#include "monitor_timer.h"
#include "monitor_queue/monitor_queue.h"

#include <signal.h>
#include <time.h>

#define MONITOR_TIMER_FIRST_DELAY 1
#define MONITOR_TIMER_INTERVAL    1

static timer_t monitor_timer = NULL;
static struct sigevent monitor_timer_signal_event;
static struct itimerspec monitor_timer_trigger;

static void monitor_timer_callback(union sigval sv);

static void
monitor_timer_callback(union sigval sv)
{
    monitor_queue_push_event_check_cpu_temperature();
}

int
monitor_timer_init(void)
{
    monitor_timer_signal_event.sigev_notify = SIGEV_THREAD;
    monitor_timer_signal_event.sigev_notify_function = &monitor_timer_callback;

    monitor_timer_trigger.it_value.tv_sec = MONITOR_TIMER_FIRST_DELAY;
    monitor_timer_trigger.it_interval.tv_sec = MONITOR_TIMER_INTERVAL;

    timer_create(CLOCK_REALTIME,
                 &monitor_timer_signal_event,
                 &monitor_timer);

    timer_settime(monitor_timer,
                  0,
                  &monitor_timer_trigger,
                  NULL);

    return 0;
}