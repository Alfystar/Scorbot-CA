
set(exeName ${PROJECT_NAME}_uartSubsystemDemo)
message("Executable define: " "${exeName}")
add_executable(${exeName} main.cpp)

#Add used library
target_link_libraries(${exeName} PUBLIC dataTransfert)
#target_link_libraries(${exeName} PUBLIC uartDriver)
target_link_libraries(${exeName} PUBLIC UartSubSystem)

