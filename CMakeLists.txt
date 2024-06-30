cmake_minimum_required(VERSION 2.8)

project(list)
#set(SOURCES main.cpp)
#set(HEADERS listnode.h)
include_directories(.)
add_executable(list main.cpp listnode.h list.h)

