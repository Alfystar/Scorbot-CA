cmake_minimum_required(VERSION 3.1)

project(pcListenUart)

add_executable(${PROJECT_NAME} main.cpp)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)