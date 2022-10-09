cmake_minimum_required(VERSION 3.0)

project(sensor_monitor
        VERSION 1.0.0
        LANGUAGES C)

add_executable(${CMAKE_PROJECT_NAME} main.c)


target_link_libraries(${CMAKE_PROJECT_NAME} rt)
target_link_libraries(${CMAKE_PROJECT_NAME} pthread)

add_subdirectory(monitor)
target_link_libraries(${CMAKE_PROJECT_NAME} monitor)