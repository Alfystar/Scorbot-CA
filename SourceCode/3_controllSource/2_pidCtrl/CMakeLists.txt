cmake_minimum_required(VERSION 3.1)

message("Sono Unix?: ${UNIX}")
message("Sono WIN32?: ${WIN32}")
message("Sono WINDOWS_PHONE?: ${WINDOWS_PHONE}")
message("Sono ANDROID?: ${ANDROID}")
message("Sono APPLE?: ${APPLE}")

project(pidCtrlDemo)
add_subdirectory(src)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC dataTransfert)
target_link_libraries(${PROJECT_NAME} PUBLIC UartSubSystem)
target_link_libraries(${PROJECT_NAME} PUBLIC pidCtrl)

