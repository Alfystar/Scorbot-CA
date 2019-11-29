cmake_minimum_required(VERSION 3.1)

project(ScorbotTerminal)

add_subdirectory(boardComSrc)
add_subdirectory(ctrlSrc)
add_subdirectory(uiSrc)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC scorbotUi)
target_link_libraries(${PROJECT_NAME} PUBLIC UartSubSystem)
target_link_libraries(${PROJECT_NAME} PUBLIC pidCtrl)



#target_link_libraries(${PROJECT_NAME} PUBLIC )
