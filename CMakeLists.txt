cmake_minimum_required(VERSION 3.3)
project(sobel_cpu)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)

add_executable(sobel_cpu main.cpp sobel.cpp sobel.h grayscale.cpp grayscale.h)
add_executable(sobel_tb testbench.cpp sobel.cpp sobel.h grayscale.cpp grayscale.h)

target_link_libraries(sobel_cpu ${OpenCV_LIBS})