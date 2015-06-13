cmake_minimum_required(VERSION 3.1)
project(features)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package( OpenCV 3.0.0 REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp)
add_executable(features ${SOURCE_FILES})

target_link_libraries( features ${OpenCV_LIBS} )
