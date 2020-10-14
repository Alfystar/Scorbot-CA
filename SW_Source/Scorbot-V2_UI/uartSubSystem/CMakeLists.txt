# Le librerie Comuni DEVONO essere PRE-Incluse
get_filename_component(libName ${CMAKE_CURRENT_SOURCE_DIR} NAME)
if (NOT TARGET ${libName})
    add_library(${libName}
            uartSubSystem.h
            ScorInterface.h  #Interface Class

            AdapterClasses/ComUartAdapter.h AdapterClasses/ComUartAdapter.cpp

            #Observer pattern class, to notifySettingBoard data
            AdapterClasses/ObserverScorbot.h AdapterClasses/ObservableScorbot.h
            ConcreteObserver.h ConcreteObserver.cpp
            )

    #aggiunge la libreria/eseguibile in modalità INTERFACE|PUBLIC|PRIVATE alla INCLUDE_DIRECTORIES property
    target_include_directories(${libName} PUBLIC ".")

    target_link_libraries(${libName} PUBLIC dataTransfertPrimitive)
    target_link_libraries(${libName} PUBLIC uartDriver)
    target_link_libraries(${libName} PUBLIC timeOp)

    find_package(Threads REQUIRED)
    target_link_libraries(${libName} PUBLIC ${CMAKE_THREAD_LIBS_INIT})

    message("[${libName}] subsystem included")
    if (${UNIX})
        target_compile_definitions(${libName} PUBLIC linuxSide=1)
        #target_compile_definitions(${libName} PUBLIC RT_THREAD=1)
    endif ()
endif ()
