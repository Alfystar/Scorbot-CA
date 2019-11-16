#definisco da quali file è composta la libreria
add_library(uartDriver
        UartDriver.h UartDriver.cpp
        UartException.h
        )

#aggiunge la libreria/eseguibile in modalità INTERFACE|PUBLIC|PRIVATE alla INCLUDE_DIRECTORIES property
target_include_directories(uartDriver PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(uartDriver PUBLIC circularBuffer)
target_link_libraries(uartDriver PUBLIC dataTransfert)

find_package(Threads REQUIRED)
target_link_libraries(uartDriver PUBLIC ${CMAKE_THREAD_LIBS_INIT})
message("CMAKE_THREAD_LIBS_INIT: " ${CMAKE_THREAD_LIBS_INIT})
if (${UNIX})
    target_compile_definitions(uartDriver PUBLIC linuxSide=1)
endif ()