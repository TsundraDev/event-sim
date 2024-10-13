cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 20)

project(event-sim)

add_library(event-sim
  src/Agent.cpp
  src/Event.cpp
  src/EventQueue.cpp
)
