#pragma once

typedef enum {
    MONITOR_EVENT_CHECK_CPU_TEMPERATUE = 0,
    MONITOR_EVENT_LAST    
} monitor_event_type_t;

typedef struct {
    monitor_event_type_t ev;
    void *args;
} monitor_event_t;

int monitor_event_handler(monitor_event_t event);
