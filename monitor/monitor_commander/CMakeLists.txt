add_library(monitor_commander 
            monitor_commander.h monitor_commander.c)

include_directories ("${PROJECT_SOURCE_DIR}/monitor_protos")
include_directories ("${PROJECT_SOURCE_DIR}/monitor_protos/nanopb")