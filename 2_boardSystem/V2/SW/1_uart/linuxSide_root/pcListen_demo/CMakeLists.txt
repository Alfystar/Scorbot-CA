
message("Executable define:")
add_executable(${PROJECT_NAME} main.cpp)

#Add used library
target_link_libraries(${PROJECT_NAME} PUBLIC dataTransfert)
#target_link_libraries(${PROJECT_NAME} PUBLIC circularBuffer)
target_link_libraries(${PROJECT_NAME} PUBLIC uartDriver)

