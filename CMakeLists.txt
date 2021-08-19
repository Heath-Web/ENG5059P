cmake_minimum_required(VERSION 3.1.0)

project(ecg_filter_demo)

set (CMAKE_CXX_STANDARD 11)

add_subdirectory(DNF)
add_executable(ecg_filter_demo ecg_filter_demo.cpp ecg_filter.cpp ecg_filter.h parameters.h)

target_link_libraries(ecg_filter_demo CLDL fir)

add_executable(lms_filter_demo lms_filter_demo.cpp parameters.h)
target_link_libraries(lms_filter_demo fir)