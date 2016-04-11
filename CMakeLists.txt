cmake_minimum_required(VERSION 3.5)
project(AstronomyProject)

find_package(OpenCV REQUIRED)

if(${OpenCV_VERSION} VERSION_LESS 2.3.1)
    message (FATAL_ERROR "OpenCV version is not compatible: ${OpenCV_VERSION}")
endif()

include_directories(${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp ImageSet.cpp ImageSet.h)
add_executable(AstronomyProject ${SOURCE_FILES})
target_link_libraries(AstronomyProject ${OpenCV_LIBS})