cmake_minimum_required(VERSION 3.14)
project(siftSRT)

set(CMAKE_CXX_STANDARD 14)

include_directories(../)

set(SOURCE_FILES main.cpp ../SiftSRT.h)

add_executable(siftSRT ${SOURCE_FILES})