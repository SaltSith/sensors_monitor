add_library(monitor monitor.h monitor.c)
target_link_libraries(monitor monitor_queue monitor_timer monitor_events)
