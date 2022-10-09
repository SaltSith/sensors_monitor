#pragma once

#include <stdbool.h>

int monitor_queue_init(void);
void monitor_queue_unlink(void);
void monitor_queue_pop(void);
int monitor_queue_get(void);

bool monitor_queue_push_event_check_cpu_temperature(void);
