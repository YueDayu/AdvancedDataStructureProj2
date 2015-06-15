cmake_minimum_required(VERSION 3.1)
project(genfeatures)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package( OpenCV 3.0.0 REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp ColorHistogram.cpp ColorMean.cpp ColorPerspective.cpp CombinedFeature.cpp BOW.cpp)
add_executable(genfeatures ${SOURCE_FILES})

target_link_libraries( genfeatures ${OpenCV_LIBS} )
