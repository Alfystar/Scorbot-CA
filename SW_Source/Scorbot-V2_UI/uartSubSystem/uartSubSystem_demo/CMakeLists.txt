
set(exeName ${PROJECT_NAME}_uartSubsystemDemo)
message("Executable define: " "${exeName}")
add_executable(${exeName} main.cpp)

#Add used library
#todo: includere le direcotry mediante include dir
target_link_libraries(${exeName} PUBLIC dataTransfert)
target_link_libraries(${exeName} PUBLIC UartSubSystem)
#target_link_libraries(${exeName} PUBLIC uartDriver)
#target_compile_definitions(uartDriver PUBLIC RT_THREAD=1)
#target_compile_definitions(uartSubSystem PUBLIC RT_THREAD=1)

