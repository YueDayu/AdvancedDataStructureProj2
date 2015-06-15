cmake_minimum_required(VERSION 3.1)
project(genfeatures)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wl,--stack -Wl,1073741824")

find_package( OpenCV 3.0.0 REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})

add_library(ImageRetrival_WHP
ImageRetrival_WHP/preprocessing.cpp
ImageRetrival_WHP/hsv.cpp
ImageRetrival_WHP/feature.cpp)

set(SOURCE_FILES main.cpp ColorHistogram.cpp ColorMean.cpp ColorPerspective.cpp CombinedFeature.cpp BOW.cpp)
add_executable(genfeatures ${SOURCE_FILES} BGReplace.h BGReplace.cpp ShapeDescriptor.h ShapeDescriptor.cpp)

target_link_libraries( genfeatures ${OpenCV_LIBS} )
target_link_libraries( genfeatures ImageRetrival_WHP)
