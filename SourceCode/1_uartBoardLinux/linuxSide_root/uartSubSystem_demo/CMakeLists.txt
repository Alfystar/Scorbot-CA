
set(exeName ${PROJECT_NAME}_uartSubsystemDemo)
message("Executable define: " "${exeName}")
add_executable(${exeName} main.cpp)

#Add used library
target_link_libraries(${exeName} PUBLIC dataTransfert)
#target_link_libraries(${exeName} PUBLIC uartDriver)
target_link_libraries(${exeName} PUBLIC UartSubSystem)
#target_compile_definitions(uartDriver PUBLIC RT_THREAD=1)
#target_compile_definitions(UartSubSystem PUBLIC RT_THREAD=1)

