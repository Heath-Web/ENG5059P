cmake_minimum_required(VERSION 3.1.0)

project(ecg_filter)

set (CMAKE_CXX_STANDARD 11)

add_subdirectory(DNF)
add_executable(ecg_filter ecg_filter.cpp parameters.h)
target_link_libraries(ecg_filter CLDL fir)