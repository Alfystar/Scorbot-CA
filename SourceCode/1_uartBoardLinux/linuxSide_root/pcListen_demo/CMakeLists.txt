
message("Executable define:" ${PROJECT_NAME})
add_executable(${PROJECT_NAME} main.cpp)

#Add used library
target_link_libraries(${PROJECT_NAME} PUBLIC dataTransfert)
#target_link_libraries(${PROJECT_NAME} PUBLIC circularBuffer)
target_link_libraries(${PROJECT_NAME} PUBLIC uartDriver)
#target_link_libraries(${PROJECT_NAME} PUBLIC UartSubSystem)

