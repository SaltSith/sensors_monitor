add_library(monitor_events
            monitor_events.h monitor_events.c)

include_directories ("${PROJECT_SOURCE_DIR}/monitor")
include_directories ("${PROJECT_SOURCE_DIR}/monitor_protos")
include_directories ("${PROJECT_SOURCE_DIR}/monitor_protos/nanopb")

