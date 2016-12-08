cmake_minimum_required(VERSION 3.6)
project(2016_10_20_Deque)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_subdirectory(googletest-master)
include_directories(googletest-master/googletest/include)
include_directories(googletest-master/googlemock/include)

set(SOURCE_FILES Tests.cpp deque.h)
add_executable(2016_10_20_Deque ${SOURCE_FILES})

target_link_libraries(2016_10_20_Deque gtest gtest_main)