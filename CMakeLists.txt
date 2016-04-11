cmake_minimum_required(VERSION 3.5)
project(AstronomyProject)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(AstronomyProject ${SOURCE_FILES})