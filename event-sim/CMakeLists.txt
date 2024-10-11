cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 20)

project(event-sim)

set(EVENT_SIM_SRC
  src/Agent.cpp
  src/Event.cpp
  src/EventQueue.cpp
)

add_library(event-sim ${EVENT_SIM_SRC})
