cmake_minimum_required(VERSION 3.1)

project(ScorbotTerminal)

add_subdirectory(boardComSrc)
add_subdirectory(ctrlSrc)
add_subdirectory(scorbotMainWindows)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC scorbotMainWindows)
message("Il programma ${PROJECT_NAME}, verrà installato al path: ${CMAKE_INSTALL_PREFIX}")
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME} DESTINATION "${CMAKE_INSTALL_PREFIX}")


#target_link_libraries(${PROJECT_NAME} PUBLIC )
