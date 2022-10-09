cmake_minimum_required(VERSION 3.0)

project(sensor_monitor
        VERSION 1.0.0
        LANGUAGES C)

add_executable(${CMAKE_PROJECT_NAME} main.c)

target_link_libraries(${CMAKE_PROJECT_NAME} rt)
target_link_libraries(${CMAKE_PROJECT_NAME} pthread)

add_subdirectory(monitor)
target_link_libraries(${CMAKE_PROJECT_NAME} monitor)

add_subdirectory(monitor/monitor_queue)
target_link_libraries(${CMAKE_PROJECT_NAME} monitor_queue)

add_subdirectory(monitor/monitor_events)
target_link_libraries(${CMAKE_PROJECT_NAME} monitor_events)

add_subdirectory(monitor/monitor_timer)
target_link_libraries(${CMAKE_PROJECT_NAME} monitor_timer)


# zmq plugin
add_subdirectory(zmq_plugin)
target_link_libraries(${CMAKE_PROJECT_NAME} zmq_plugin)

add_subdirectory(zmq_plugin/zmq_plugin_socket)
target_link_libraries(${CMAKE_PROJECT_NAME} zmq_plugin_socket)

target_link_libraries(${CMAKE_PROJECT_NAME} czmq)
target_link_libraries(${CMAKE_PROJECT_NAME} zmq)

# testing 
enable_testing()

#testing plugin_socket
add_executable(test_plugin_socket zmq_plugin/zmq_plugin_socket/test/test.c)
target_link_libraries(test_plugin_socket zmq_plugin_socket)
target_link_libraries(test_plugin_socket czmq)
target_link_libraries(test_plugin_socket zmq)
add_test(NAME test_plugin_socket COMMAND test_plugin_socket)

#testing plugin_task
add_executable(test_plugin_task zmq_plugin/test/test.c)
target_link_libraries(test_plugin_task zmq_plugin)
target_link_libraries(test_plugin_task zmq_plugin_socket)
target_link_libraries(test_plugin_task czmq)
target_link_libraries(test_plugin_task zmq)
add_test(NAME test_plugin_task COMMAND test_plugin_task)

#testing monitor
