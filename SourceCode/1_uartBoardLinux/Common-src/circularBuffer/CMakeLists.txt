#definisco da quali file è composta la libreria
add_library(circularBuffer
        CircularBuffer.h CircularBuffer.cpp
        )

#aggiunge la libreria/eseguibile in modalità INTERFACE|PUBLIC|PRIVATE alla INCLUDE_DIRECTORIES property
target_include_directories(circularBuffer PUBLIC ".")
message("La libreria 'circularBuffer' è stata aggiunta")
message("CMAKE_CURRENT_SOURCE_DIR:" . ${x86_64})
if (${UNIX})
    target_compile_definitions(circularBuffer PUBLIC linuxSide=1)
endif ()

