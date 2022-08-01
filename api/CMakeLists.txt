cmake_minimum_required(VERSION 3.0.0)
project(grayscale-launch VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(~/tapasco/runtime/libtapasco/src)

add_executable(grayscale-launch grayscale-launch.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
