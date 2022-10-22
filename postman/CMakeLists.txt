add_library(postman
            postman.h postman.c)

include_directories ("${PROJECT_SOURCE_DIR}/monitor")

include_directories ("${PROJECT_SOURCE_DIR}/monitor_protos")
include_directories ("${PROJECT_SOURCE_DIR}/monitor_protos/nanopb")
include_directories ("${PROJECT_SOURCE_DIR}/")

target_link_libraries(postman pb_helper)
target_link_libraries(postman monitor)