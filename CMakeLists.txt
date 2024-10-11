cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 20)

project(event-sim)

add_executable(event-sim-test main.cpp)
include_directories(event-sim-test event-sim)

add_subdirectory(event-sim)
target_link_libraries(event-sim-test event-sim)
