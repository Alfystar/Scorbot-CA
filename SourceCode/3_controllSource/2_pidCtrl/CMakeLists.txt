cmake_minimum_required(VERSION 3.1)
project(ctrlDemo)


add_subdirectory(pidCtrl)
add_subdirectory(DataTransfertPackge)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} pidCtrl)
target_link_libraries(${PROJECT_NAME} dataTransfert)
