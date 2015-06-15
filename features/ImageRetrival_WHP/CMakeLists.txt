cmake_minimum_required(VERSION 3.1)
project(ImageRetrival_WHP)

find_package( OpenCV 3.0.0 REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wl,--stack -Wl,1073741824")

set(SOURCE_FILES
    feature.cpp
    feature.h
    hsv.cpp
    hsv.h
    preprocessing.cpp
    preprocessing.h
    test.cpp)

add_executable(ImageRetrival_WHP ${SOURCE_FILES})

target_link_libraries( ImageRetrival_WHP ${OpenCV_LIBS} )
