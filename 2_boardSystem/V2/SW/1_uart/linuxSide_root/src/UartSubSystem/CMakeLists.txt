#definisco da quali file è composta la libreria
add_library(UartSubSystem
        UartSubSystem.h
        ScorInterface.h GetCom_int.h #Interface Class
        InfoExpPack.h InfoExpPack.cpp
        AdapterClasses/SingletonFactoryException.h
        AdapterClasses/ParamSingletonFactory.h AdapterClasses/ParamSingletonFactory.cpp   #Factory per generare Le classi di comunicazione uniche per tipo
        AdapterClasses/ComUartAdapter.h AdapterClasses/ComUartAdapter.cpp
        AdapterFactory.h AdapterFactory.cpp #Factory per generare gli adapter
        )

#aggiunge la libreria/eseguibile in modalità INTERFACE|PUBLIC|PRIVATE alla INCLUDE_DIRECTORIES property
target_include_directories(UartSubSystem PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(UartSubSystem PUBLIC dataTransfert)
target_link_libraries(UartSubSystem PUBLIC uartDriver)

find_package(Threads REQUIRED)
target_link_libraries(UartSubSystem PUBLIC ${CMAKE_THREAD_LIBS_INIT})

if (${UNIX})
    target_compile_definitions(uartDriver PUBLIC linuxSide=1)
endif ()