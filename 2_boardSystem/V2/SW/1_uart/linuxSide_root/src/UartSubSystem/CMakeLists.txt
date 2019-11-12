#definisco da quali file è composta la libreria
add_library(UartSubSystem
        ScorInterface.h GetCom_int.h #Interface Class
        InfoExpPack.h InfoExpPack.cpp
        ComUartAdapter.h ComUartAdapter.cpp
        )

#aggiunge la libreria/eseguibile in modalità INTERFACE|PUBLIC|PRIVATE alla INCLUDE_DIRECTORIES property
target_include_directories(UartSubSystem PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(UartSubSystem PUBLIC uartDriver)
target_link_libraries(UartSubSystem PUBLIC dataTransfert)

if (${UNIX})
    target_compile_definitions(uartDriver PUBLIC linuxSide=1)
endif ()