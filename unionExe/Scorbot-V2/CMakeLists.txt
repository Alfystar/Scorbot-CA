cmake_minimum_required(VERSION 3.1)

project(ScorbotTerminal)

add_subdirectory(boardComSrc)
add_subdirectory(ctrlSrc)
add_subdirectory(scorbotMainWindows)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC scorbotMainWindows)




#target_link_libraries(${PROJECT_NAME} PUBLIC )
