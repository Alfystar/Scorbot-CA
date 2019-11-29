#definisco da quali file è composta la libreria
if (NOT TARGET circularBuffer)
    add_library(circularBuffer
            CircularBuffer.h CircularBuffer.cpp
            )

    #aggiunge la libreria/eseguibile in modalità INTERFACE|PUBLIC|PRIVATE alla INCLUDE_DIRECTORIES property
    target_include_directories(circularBuffer PUBLIC "${CMAKE_INCLUDE_CURRENT_DIR}")
    message("La libreria 'circularBuffer' è stata aggiunta")
    if (${UNIX})
        target_compile_definitions(circularBuffer PUBLIC linuxSide=1)
    endif ()
endif ()

